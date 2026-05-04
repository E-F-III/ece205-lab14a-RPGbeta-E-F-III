///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 14a - Avatar: Terminal Elements - ECE 205 - Spring 2026
//
/// @file   DungeonSystem.cpp
/// @author Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "DungeonSystem.hpp"
#include "../util/TextDisplay.hpp"
#include "../BattleManager/BattleManager.hpp"

#include <iostream>

using namespace std;
using json = nlohmann::json;

// Constructor
DungeonSystem::DungeonSystem(const GameData::RegionData* region,
                             GameData*                   data,
                             vector<FighterCharacter*>&  party)
    : regionInfo(region), gameData(data), playerParty(party)
{}

// runDungeon — scene state machine
int DungeonSystem::runDungeon() {
    util::printColor("\n╔══════════════════════════════════╗\n", util::FG_YELLOW);
    util::printColor("  Entering: " + regionInfo->dungeon_name + "\n", util::FG_YELLOW);
    util::printColor("╚══════════════════════════════════╝\n", util::FG_YELLOW);
    util::showLoadingSpinner("Descending into the dungeon...", 1200);

    // Start from the "dungeon" location scene key stored in the region
    string currentKey = regionInfo->locations.at("dungeon");

    while (!currentKey.empty()) {
        const json& scene = gameData->getScene(currentKey);

        if (scene.is_null()) {
            cerr << "WARNING: scene key \"" << currentKey << "\" not found in JSON\n";
            break;
        }

        string type = scene["type"].get<string>();

        // ── Terminal scenes
        if (type == "dialogue" && scene.contains("set_flag")) {
            // win_dialogue: print text, mark region resolved, return win
            string text = scene.value("text", "");
            util::printColor("\n" + text + "\n", util::FG_GREEN);
            util::waitEnter();
            return 1;
        }

        if (type == "death") {
            string text = scene.value("text", "You have been defeated...");
            util::printColor("\n" + text + "\n", util::FG_RED);
            util::waitEnter();
            return 0;
        }

        if (type == "ending") {
            string text = scene.value("text", "");
            string result = scene.value("result", "");
            auto color = (result == "good") ? util::FG_GREEN : util::FG_RED;
            util::printColor("\n" + text + "\n", color);
            util::waitEnter();
            return (result == "good") ? 1 : 0;
        }

        if (type == "dungeon_room") {currentKey = handleDungeonRoom(scene);}
        else if (type == "dungeon_choice") {currentKey = handleChoice(scene);}
        else if (type == "dialogue") {currentKey = handleDialogue(scene);}
        else if (type == "rest") {currentKey = handleRest(scene);}
        else if (type == "battle") {currentKey = handleBattle(scene);}
        else if (type == "boss_battle") {currentKey = handleBossBattle(scene);}
        else {
            // Unknown type — skip with a warning and stop
            cerr << "WARNING: unhandled scene type \"" << type
                 << "\" at key \"" << currentKey << "\"\n";
            break;
        }
    }

    // Fell out of the loop without a clean terminal — treat as loss
    return 0;
}


// handleDungeonRoom — entrance/flavour room with a single "continue" option
string DungeonSystem::handleDungeonRoom(const json& scene) {
    string text = scene.value("text", "");
    util::printColor("\n" + text + "\n", util::FG_CYAN);

    // Show options if present, otherwise just wait for Enter
    if (scene.contains("options") && !scene["options"].empty()) {
        const auto& options = scene["options"];
        for (int i = 0; i < (int)options.size(); i++) {
            cout << "  " << i + 1 << ". " << options[i]["label"].get<string>() << "\n";
        }
        int choice = util::promptInt("Choose: ", 1, (int)options.size()) - 1;
        return options[choice]["next"].get<string>();
    }

    util::waitEnter();
    return scene.value("next", "");
}


// handleChoice — dungeon fork with multiple path options
string DungeonSystem::handleChoice(const json& scene) {
    string text = scene.value("text", "");
    util::printColor("\n" + text + "\n", util::FG_YELLOW);

    const auto& options = scene["options"];
    for (int i = 0; i < (int)options.size(); i++) {
        cout << "  " << i + 1 << ". " << options[i]["label"].get<string>() << "\n";
    }

    int choice = util::promptInt("Choose a path: ", 1, (int)options.size()) - 1;
    return options[choice]["next"].get<string>();
}


// handleDialogue — narrative text, then auto-advance
string DungeonSystem::handleDialogue(const json& scene) {
    string text = scene.value("text", "");
    util::printType(text + "\n", 30);
    util::waitEnter();
    return scene.value("next", "");
}


// handleRest — restores party HP, then advances
string DungeonSystem::handleRest(const json& scene) {
    string text = scene.value("text", "You rest and recover.");
    util::printColor("\n" + text + "\n", util::FG_GREEN);

    if (scene.contains("effect")) {
        const auto& effect = scene["effect"];
        if (effect.contains("restore_health")) {
            // Value can be a number or the string "max_health"
            int amount = gameData->getMaxHealth(); // default: full restore
            if (effect["restore_health"].is_number()) {
                amount = effect["restore_health"].get<int>();
            }
            restorePartyHealth(amount);
            util::printColor("The party restored up to " + to_string(amount) + " HP.\n",
                             util::FG_GREEN);
        }
    }

    util::waitEnter();
    return scene.value("next", "");
}


// handleBattle — spawns enemies from scene["enemies"] array
string DungeonSystem::handleBattle(const json& scene) {
    util::printColor("\n[ Enemy Encounter! ]\n", util::FG_RED);

    vector<FighterCharacter*> enemies;
    for (const auto& enemyId : scene["enemies"]) {
        FighterCharacter* e = gameData->createEnemyById(enemyId.get<string>());
        if (e) {
            util::printColor("  " + e->getName() + " appears!\n", util::FG_RED);
            enemies.push_back(e);
        }
    }

    if (enemies.empty()) {
        cerr << "WARNING: no enemies spawned for battle scene\n";
        return scene.value("on_win", "");
    }

    util::waitEnter();
    BattleManager bm(playerParty, enemies);
    bm.runBattle();

    // Clean up enemy heap allocations
    for (auto* e : enemies) delete e;

    if (anyPlayerAlive()) {
        util::printColor("\nVictory!\n", util::FG_GREEN);
        return scene.value("on_win", "");
    } else {
        util::printColor("\nThe party has been defeated...\n", util::FG_RED);
        return scene.value("on_lose", "");
    }
}


// handleBossBattle — spawns the boss from scene["enemy"]
string DungeonSystem::handleBossBattle(const json& scene) {
    string bossId = scene["enemy"].get<string>();

    util::printColor("\n[ BOSS BATTLE ]\n", util::BOLD);
    util::printColor("A powerful presence fills the room...\n", util::FG_MAGENTA);

    FighterCharacter* boss = gameData->createEnemyById(bossId);
    if (!boss) {
        cerr << "WARNING: createEnemyById(\"" << bossId << "\") returned nullptr\n";
        return scene.value("on_win", "");
    }

    util::printColor("BOSS: " + boss->getName() + " appears!\n", util::FG_MAGENTA);
    util::waitEnter();
    vector<FighterCharacter*> enemies = { boss };
    BattleManager bm(playerParty, enemies);
    bm.runBattle();

    delete boss;

    if (anyPlayerAlive()) {
        util::printColor("\nThe boss has been defeated!\n", util::FG_GREEN);
        return scene.value("on_win", "");
    } else {
        util::printColor("\nThe party has fallen to the boss...\n", util::FG_RED);
        return scene.value("on_lose", "");
    }
}


// Helpers
bool DungeonSystem::anyPlayerAlive() const {
    for (auto* p : playerParty) {
        if (p->getHealth() > 0) return true;
    }
    return false;
}

void DungeonSystem::restorePartyHealth(int amount) {
    int maxHp = gameData->getMaxHealth();
    for (auto* p : playerParty) {
        int restored = min(p->getHealth() + amount, maxHp);
        p->setHealth(restored);
    }
}
