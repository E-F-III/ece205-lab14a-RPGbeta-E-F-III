#include <iostream>
#include <vector>
#include <ctime>
#include "GameLogic/GameData.hpp"
#include "GameLogic/DungeonSystem.hpp"
#include "util/TextDisplay.hpp"
#include "Characters/PlayerControlled/AirBender.hpp"
#include "Characters/PlayerControlled/EarthBender.hpp"
#include "Characters/PlayerControlled/FireBender.hpp"
#include "Characters/PlayerControlled/WaterBender.hpp"
#include "Characters/NPC/NPCAirBender.hpp"
#include "Characters/NPC/NPCEarthBender.hpp"
#include "Characters/NPC/NPCFireBender.hpp"
#include "Characters/NPC/NPCWaterBender.hpp"
#include "BattleManager/BattleManager.hpp"

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
    
    if (newPlayer) newPlayer->greet();
    return newPlayer;
}

int main() {
    // 0. Initial Terminal Prep
    util::clearScreen();
    srand(static_cast<unsigned int>(time(NULL)));

    // 1. Load Data Layer
    string jsonFileName = "util/story_config.json";
    GameData gameStorage(jsonFileName);

    util::printColor("=========================================\n", util::FG_MAGENTA);
    util::printType("      Dungeon Chronicle Beta Test Run      \n", 30);
    util::printColor("=========================================\n", util::FG_MAGENTA);

    // 2. Setup Party
    vector<FighterCharacter*> party;
    cout << "\nHow many players? (1-4): ";
    int numPlayers = 0;
    while (!(cin >> numPlayers) || numPlayers < 1 || numPlayers > 4) {
        cin.clear(); 
        cin.ignore(1000, '\n');
        cout << "Invalid. Try 1-4: ";
    }

    for (int i = 0; i < numPlayers; i++) {
        party.push_back(createPlayer(i));
    }

    // 3. CORE IMPLEMENTATION
    string activeRegion = "fire_nation"; 
    DungeonSystem dungeon(activeRegion, &gameStorage, party);
    
    util::printColor("\n--- STARTING DUNGEON TRAVERSAL ---\n", util::FG_YELLOW);
    int result = dungeon.runDungeon();

    // 4. Handle Ending
    // Success condition: runDungeon returned 1 and party is alive
    if (result == 1 && party[0]->getHealth() > 0) {
        util::printColor("\n\n★★★ SUCCESS! Dungeon Cleared! ★★★\n", util::FG_GREEN);
    } 
    // Failure condition: Party health dropped to 0 or below
    else if (party[0]->getHealth() <= 0) {
        util::printColor("\n\n DEFEAT... You succumbed to the forces of the dungeon.\n", util::FG_RED);
    } 
    else {
        util::printColor("\n\n[TEST WARNING] Dungeon run completed but final status is ambiguous.\n", util::FG_YELLOW);
    }

    // Cleanup
    for (auto p : party) delete p;
    return 0;
}
