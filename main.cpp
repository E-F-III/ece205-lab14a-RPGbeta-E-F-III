#include <iostream>
#include <fstream> // needed for file I/O to read the story data
#include <vector>
#include <ctime>
#include "GameLogic/GameData.hpp"
#include "GameLogic/DungeonSystem.hpp"

// Include the third party json parser
#include "json.hpp"

// Include the Manager
#include "BattleManager.hpp"

// Include Character headers
#include "AirBender.hpp"
#include "EarthBender.hpp"
#include "FireBender.hpp"
#include "WaterBender.hpp"
#include "NPCAirBender.hpp"
#include "NPCEarthBender.hpp"
#include "NPCFireBender.hpp"
#include "NPCWaterBender.hpp"

// Include the Utility header for pretty text
#include "util/TextDisplay.hpp"
#include "Characters/PlayerControlled/AirBender.hpp"
#include "Characters/PlayerControlled/EarthBender.hpp"
#include "Characters/PlayerControlled/FireBender.hpp"
#include "Characters/PlayerControlled/WaterBender.hpp"


using namespace std;

// --- Parse the data from the json file ---
nlohmann::json storyData; 

void loadStoryData() {
    ifstream file("util/story_config.json");
    if (file.is_open()) {
        file >> storyData;
        file.close();
    } else {
        cerr << "Error: Could not open story_config.json" << endl;
        exit(1);
    }
}

// --- Helper Functions (Factory Pattern) ---

PlayerCharacter* createPlayer(int i) {
    string name;
    int code;
    util::printColor("\n[ Player Creation " + to_string(i + 1) + " ]\n", util::FG_CYAN);
    cout << "Enter name: ";
    if(i == 0) cin.ignore(1000, '\n'); 
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
    loadStoryData(); // Load the story data from the JSON file at the start of the program

    cout << storyData["regions"] << endl; // Display the intro story text
    // 0. Initial Terminal Prep
    util::clearScreen();
    srand(static_cast<unsigned int>(time(NULL)));


    string jsonFileName = "util/story_config.json";
    GameData gameStorage(jsonFileName);


    util::printColor("=========================================\n", util::FG_MAGENTA);
    util::printColor("           AVATAR: TERMINAL ELEMENTS     \n", util::BOLD);
    util::printColor("=========================================\n", util::FG_MAGENTA);


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


    // Starting in fire_nation for testing
    string activeRegion = "fire_nation"; 
    DungeonSystem dungeon(activeRegion, &gameStorage, party);
    
    util::printColor("\n--- STARTING DUNGEON TRAVERSAL ---\n", util::FG_YELLOW);
    int result = dungeon.runDungeon();


    // Check health properly to avoid the precedence warning
    if (result == 1 && party[0]->getHealth() > 0) {
        util::printColor("\n\n★★★ SUCCESS! Dungeon Cleared! ★★★\n", util::FG_GREEN);
    } 
    else if (party[0]->getHealth() <= 0) {
        util::printColor("\n\n DEFEAT... You succumbed to the forces of the dungeon.\n", util::FG_RED);
    } 
    else {
        util::printColor("\n\n[TEST WARNING] Dungeon run ended. Result: " + to_string(result) + "\n", util::FG_YELLOW);
    }


    for (auto p : party) delete p;
    return 0;
}
