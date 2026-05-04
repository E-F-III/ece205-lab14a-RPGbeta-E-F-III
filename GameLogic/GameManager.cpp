///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 14a - Avatar: Terminal Elements - ECE 205 - Spring 2026
//
/// @file   GameManager.cpp
/// @author Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "GameManager.hpp"
#include "TextDisplay.hpp"

#include "AirBender.hpp"
#include "EarthBender.hpp"
#include "FireBender.hpp"
#include "WaterBender.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
using json = nlohmann::json;


// Constructor
GameManager::GameManager() {
    srand(static_cast<unsigned int>(time(NULL)));

    gameData = new GameData("util/story_config.json");

    ifstream file("util/story_config.json");
    if (!file.is_open()) {
        cerr << "ERROR: Could not open util/story_config.json\n";
        exit(1);
    }
    file >> storyData;
    file.close();
}

// Destructor
GameManager::~GameManager() {
    delete gameData;
    for (auto* p : players) delete p;
}


// Public entry point
void GameManager::run() {
    util::clearScreen();

    util::printColor("=========================================\n", util::FG_MAGENTA);
    util::printColor("      AVATAR: TERMINAL ELEMENTS          \n", util::BOLD);
    util::printColor("=========================================\n", util::FG_MAGENTA);
    cout << "\n";

    setupPlayers();
    selectRegionAndRunDungeon();
}

// Player setup
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
            case 0: p = new AirBender  (name, code); break;
            case 1: p = new EarthBender(name, code); break;
            case 2: p = new FireBender (name, code); break;
            case 3: p = new WaterBender(name, code); break;
        }
        if (p) {
            p->greet();
            players.push_back(p);
        }
    }
}


// Region select → DungeonSystem // for now. will implement proper world map later
void GameManager::selectRegionAndRunDungeon() {
    const vector<GameData::RegionData>& regions = gameData->getRegions();

    util::printColor("\n=== CHOOSE A REGION ===\n", util::FG_YELLOW);
    for (int i = 0; i < (int)regions.size(); i++) {
        cout << "  " << i << ": " << regions[i].name << "\n";
    }

    int choice = util::promptInt("Enter choice: ", 0, (int)regions.size() - 1);

    const GameData::RegionData& region = regions[choice];
    util::printColor("\nHeading to " + region.name + "...\n", util::FG_CYAN);
    util::showLoadingSpinner("Entering region...", 1500);

    // Hand off to DungeonSystem
    DungeonSystem dungeon(&region, gameData, players);
    int result = dungeon.runDungeon();

    if (result == 1) {
        util::printColor("\n★ " + region.name + " has been saved! Balance is restored.\n",
                         util::FG_GREEN);
    } else {
        util::printColor("\n☠ The party has fallen. " + region.name + " remains in chaos.\n",
                         util::FG_RED);
    }
}

