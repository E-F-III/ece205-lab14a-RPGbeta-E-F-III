///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 14a - Avatar: Terminal Elements - ECE 205 - Spring 2026
//
/// @file   GameManager.cpp
/// @author Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "GameManager.hpp"
#include "BattleManager.hpp"
#include "TextDisplay.hpp"

#include "AirBender.hpp"
#include "EarthBender.hpp"
#include "FireBender.hpp"
#include "WaterBender.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using json = nlohmann::json;

// Constructor / Destructor

GameManager::GameManager() {
    srand(static_cast<unsigned int>(time(NULL)));
    gameData = new GameData("util/story_config.json");
    gold     = gameData->getStartingGold();
}

GameManager::~GameManager() {
    delete gameData;
    for (auto* p : players) delete p;
}


// run — top-level scene state machine
void GameManager::run() {
    util::clearScreen();
    util::printColor("=========================================\n", util::FG_MAGENTA);
    util::printColor("      AVATAR: TERMINAL ELEMENTS          \n", util::BOLD);
    util::printColor("=========================================\n", util::FG_MAGENTA);
    cout << "\n";

    // ── Demo Mode prompt ──────────────────────────────────────────────────────
    cout << "\n";
    util::printColor("Enable DEMO MODE? (players deal 3x damage) [y/n]: ", util::FG_YELLOW);
    char demoChoice;
    cin >> demoChoice;
    cin.ignore(1000, '\n');
    demoMode = (demoChoice == 'y' || demoChoice == 'Y');
    if (demoMode)
        util::printColor("[DEMO MODE ACTIVATED] Battles will be quick!\n", util::FG_YELLOW);
    // ─────────────────────────────────────────────────────────────────────────
    
    setupPlayers();

    // Restore all players to starting health
    int startHp = gameData->getStartingHealth();
    for (auto* p : players) p->setHealth(startHp);

    // Begin the scene state machine at the JSON-configured starting scene
    string currentKey = gameData->getStartingScene();

    while (!currentKey.empty()) {
        util::clearScreen(); // clear screen in between scenes

        const json& scene = gameData->getScene(currentKey);


        if (scene.is_null()) {
            cerr << "WARNING: scene key \"" << currentKey << "\" not found\n";
            break;
        }

        string type = scene["type"].get<string>();

        // ── Terminal: endings
        if (type == "ending") {
            string text   = scene.value("text", "");
            string result = scene.value("result", "");
            auto   color  = (result == "good") ? util::FG_GREEN : util::FG_RED;
            util::printColor("\n" + text + "\n", color);
            util::waitEnter();
            break;
        }

        // ── Terminal: death/restart — reset state and restart
        if (type == "death") {
            string text = scene.value("text", "You were defeated.");
            util::printColor("\n" + text + "\n", util::FG_RED);
            util::waitEnter();

            // Reset: clear resolved regions, restore health, restart
            resolvedRegions.clear();
            int startHp = gameData->getStartingHealth();
            for (auto* p : players) p->setHealth(startHp);
            currentKey = gameData->getStartingScene();
            continue;
        }

        // ── Scene dispatch 
        if      (type == "world_select")   currentKey = handleWorldSelect (scene);
        else if (type == "dialogue")       currentKey = handleDialogue    (scene);
        else if (type == "region_select")  currentKey = handleRegionSelect(scene);
        else if (type == "condition")      currentKey = handleCondition   (scene);
        else if (type == "prompt")         currentKey = handlePrompt      (scene);
        else if (type == "final_battle")   currentKey = handleFinalBattle (scene);
        else {
            cerr << "WARNING: unhandled overworld scene type \"" << type
                 << "\" at \"" << currentKey << "\"\n";
            break;
        }
    }
}


// handleWorldSelect — choose home region (or any world select screen)
string GameManager::handleWorldSelect(const json& scene) {
    string text = scene.value("text", "Choose your world.");
    util::printColor("\n" + text + "\n", util::FG_CYAN);

    const auto& options = scene["options"];
    for (int i = 0; i < (int)options.size(); i++) {
        cout << "  " << i + 1 << ". " << options[i]["label"].get<string>() << "\n";
    }

    int choice = util::promptInt("Enter choice: ", 1, (int)options.size()) - 1;
    return options[choice]["next"].get<string>();
}


// handleDialogue — display text and auto-advance
string GameManager::handleDialogue(const json& scene) {
    string text = scene.value("text", "");
    util::printType(text + "\n", 30);
    util::waitEnter();
    return scene.value("next", "");
}


// handleRegionSelect — show available regions, run DungeonSystem for chosen one
// at the moment, scene is passed for future implementation of region-specific dialogue or conditions, but currently unused
string GameManager::handleRegionSelect(const json& scene) {
    const vector<GameData::RegionData>& regions = gameData->getRegions();

    util::printColor("\n=== CHOOSE A REGION ===\n", util::FG_YELLOW);
    util::printColor("Cleared: " + to_string(resolvedRegions.size()) + " / "
                     + to_string(regions.size()) + "\n", util::FG_WHITE);

    // Build list of available (unresolved) regions
    vector<const GameData::RegionData*> available;
    for (const auto& r : regions) {
        if (resolvedRegions.count(r.id) == 0) {
            available.push_back(&r);
        }
    }

    if (available.empty()) {
        util::printColor("All regions cleared!\n", util::FG_GREEN);
        return "scene_check_conflicts";
    }

    for (int i = 0; i < (int)available.size(); i++) {
        cout << "  " << i + 1 << ". " << available[i]->name
             << "  (" << available[i]->disturbance << ")\n";
    }

    int choice = util::promptInt("Enter choice: ", 1, (int)available.size()) - 1;
    const GameData::RegionData* region = available[choice];

    util::printColor("\nHeading to " + region->name + "...\n", util::FG_CYAN);
    util::showLoadingSpinner("Entering region...", 1500);

    // Run the dungeon for this region
    DungeonSystem dungeon(region, gameData, players);
    int result = dungeon.runDungeon();

    if (result == 1) {
        resolvedRegions.insert(region->id);
        util::printColor("\n★ " + region->name + " has been saved!\n", util::FG_GREEN);
    } else {
        util::printColor("\n☠ The party has fallen.\n", util::FG_RED);
        return "scene_die_restart";
    }

    // After clearing a region, check if all are done
    return "scene_check_conflicts";
}


// handleCondition — evaluates the scene's condition
string GameManager::handleCondition(const json& scene) {
    string condition = scene.value("condition", "");

    // "resolved_regions.length == 4"
    if (condition.find("resolved_regions.length") != string::npos) {
        size_t eqPos = condition.find("==");
        if (eqPos != string::npos) {
            int required = stoi(condition.substr(eqPos + 2));
            bool met = ((int)resolvedRegions.size() >= required);
            return met ? scene.value("true_next", "")
                       : scene.value("false_next", "");
        }
    }

    cerr << "WARNING: unhandled condition \"" << condition << "\"\n";
    return scene.value("false_next", "");
}

// handlePrompt — a choice screen with multiple labelled options
string GameManager::handlePrompt(const json& scene) {
    string text = scene.value("text", "");
    util::printType(text + "\n", 30);

    const auto& options = scene["options"];
    for (int i = 0; i < (int)options.size(); i++) {
        cout << "  " << i + 1 << ". " << options[i]["label"].get<string>() << "\n";
    }

    int choice = util::promptInt("Choose: ", 1, (int)options.size()) - 1;
    return options[choice]["next"].get<string>();
}


// handleFinalBattle — spirit realm final boss
string GameManager::handleFinalBattle(const json& scene) {
    string text   = scene.value("text", "");
    string bossId = scene["enemy"].get<string>();

    util::printColor("\n" + text + "\n", util::FG_MAGENTA);
    util::showLoadingSpinner("Entering the spirit realm...", 1500);

    // Build a one-room "dungeon" for the final boss using DungeonSystem's
    // enemy factory directly through GameData
    FighterCharacter* boss = gameData->createEnemyById(bossId);
    if (!boss) {
        cerr << "WARNING: final boss \"" << bossId << "\" not found\n";
        return scene.value("on_win", "");
    }

    util::printColor("\nFINAL BOSS: " + boss->getName() + " stands before you!\n",
                     util::BOLD);

    vector<FighterCharacter*> enemies = { boss };
    BattleManager bm(players, enemies);
    bm.runBattle();

    delete boss;

    bool won = false;
    for (auto* p : players) {
        if (p->getHealth() > 0) { won = true; break; }
    }

    return won ? scene.value("on_win", "") : scene.value("on_lose", "");
}

// setupPlayers
void GameManager::setupPlayers() {
    int n = util::promptInt("How many players? (1-4): ", 1, 4);

    for (int i = 0; i < n; i++) {
        util::printColor("\n[ Player Creation " + to_string(i + 1) + " ]\n", util::FG_CYAN);

        string name;
        cout << "Enter name: ";
        cin.ignore(1000, '\n');
        getline(cin, name);

        int code = util::promptInt("Bending (0:Air  1:Earth  2:Fire  3:Water): ", 0, 3);

        PlayerCharacter* p = nullptr;
        switch (code) {
            case 0: p = new AirBender  (name, code, demoMode); break;
            case 1: p = new EarthBender(name, code, demoMode); break;
            case 2: p = new FireBender (name, code, demoMode); break;
            case 3: p = new WaterBender(name, code, demoMode); break;
        }
        if (p) {
            p->greet();
            players.push_back(p);
        }
    }
}
