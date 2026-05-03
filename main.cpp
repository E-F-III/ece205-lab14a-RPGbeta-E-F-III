// University of Hawaii, College of Engineering
// Lab 14a - RPG Beta - Dungeon Test Runner
//
/// @file    main.cpp
/// @author  Menden Cannistra <mendenc@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include "GameData.hpp" 
#include "DungeonSystem.hpp" 
#include "util/TextDisplay.hpp"

// Include necessary character headers (Keep these!)
#include "AirBender.hpp"
#include "EarthBender.hpp"
#include "FireBender.hpp"
#include "WaterBender.hpp"
#include "NPCAirBender.hpp"
#include "NPCEarthBender.hpp"
#include "NPCFireBender.hpp"
#include "NPCWaterBender.hpp"

// Include the Manager
#include "BattleManager.hpp"

using namespace std;

// --- Helper Functions (Factory Pattern) ---

PlayerCharacter* createPlayer(int i) {
    string name;
    int code;

    util::printColor("\n[ Player Creation " + to_string(i + 1) + " ]\n", util::FG_CYAN);
    cout << "Enter name: ";
    cin.ignore(1000, '\n');
    getline(cin, name);

    cout << "Bending (0:Air, 1:Earth, 2:Fire, 3:Water): ";
    while (!(cin >> code) || code < 0 || code > 3) {
        cout << "Invalid. Enter 0-3: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    PlayerCharacter* newPlayer = nullptr;
    switch (code) {
        case 0: newPlayer = new AirBender(name, code); break;
        case 1: newPlayer = new EarthBender(name, code); break;
        case 2: newPlayer = new FireBender(name, code); break;
        case 3: newPlayer = new WaterBender(name, code); break;
    }

    if (newPlayer) {
        newPlayer->greet(); 
    }
    return newPlayer;
}

NPCharacter* createNPC(int i) {
    int code = rand() % 4;
    string name = "Enemy " + to_string(i + 1);
    NPCharacter* newEnemy = nullptr;

    switch (code) {
        case 0: newEnemy = new NPCAirBender(name, code); break;
        case 1: newEnemy = new NPCEarthBender(name, code); break;
        case 2: newEnemy = new NPCFireBender(name, code); break;
        case 3: newEnemy = new NPCWaterBender(name, code); break;
    }

    return newEnemy;
}


int main() {
    // 0. Initial Terminal Prep
    util::clearScreen();
    srand(static_cast<unsigned int>(time(NULL)));

    // 1. Load Data Layer (Uses the JSON key "config")
    string jsonFileName = "util/story_config.json"; 
    GameData gameStorage(jsonFileName); 
    
    util::printColor("=========================================\n", util::FG_MAGENTA);
    util::printType("  Dungeon Chronicle Beta Test Run   \n", 30);
    util::printColor("=========================================\n", util::FG_MAGENTA);

    // 2. Setup Party (Example: Player Character)
    vector<FighterCharacter*> party;
    
    cout << "\nHow many players? (1-4): ";
    int numPlayers = 0;
    while (!(cin >> numPlayers) || numPlayers < 1 || numPlayers > 4) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Invalid. Try 1-4: ";
    }
    
    for (int i = 0; i < numPlayers; i++) {
        party.push_back(createPlayer(i)); 
    }

    // --- CORE IMPLEMENTATION START ---
    
    // Determine which region we are testing based on JSON (e.g., Fire Nation)
    string activeRegion = "fire_nation"; 

    // Initialize the Dungeon System, passing the party pointer to track state
    DungeonSystem dungeon(activeRegion, &gameStorage, party);
    
    util::printColor("\n--- STARTING DUNGEON TRAVERSAL ---\n", util::FG_YELLOW);
    int result = dungeon.runDungeon();

    // 4. Handle Ending (Using JSON config keys: win/lose)
    if (result == 1 && party[0]->getHealth() > 0) {
        util::printColor("\n\n★★★ SUCCESS! Dungeon Cleared! ★★★", util::FG_GREEN);
    } else if (!party[0]->getHealth() > 0) {
        util::printColor("\n\n☠ DEFEAT... You succumbed to the forces of the dungeon. ☠", util::FG_RED);
    } else {
        util::printColor("\n\n[TEST WARNING] Dungeon run completed but final status is ambiguous.", util::FG_YELLOW);
    }

    // Cleanup: Crucial to prevent memory leaks!
    for (auto p : party) delete p; 
    return 0;
}
