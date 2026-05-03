///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 11a - Game Character Class Part II - ECE 205 - Spring 2025
//
/// @file    main.cpp
/// @author  Menden Cannistra <mendenc@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream> // needed for file I/O to read the story data
#include <vector>
#include <string>
#include <ctime>

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
        newPlayer->greet(); // Triggers the typing animation intro
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

// --- Main Execution ---

int main() {
    loadStoryData(); // Load the story data from the JSON file at the start of the program

    cout << storyData["regions"] << endl; // Display the intro story text
    // 0. Initial Terminal Prep
    util::clearScreen();
    srand(static_cast<unsigned int>(time(NULL)));

    util::printColor("=========================================\n", util::FG_MAGENTA);
    util::printColor("           AVATAR: TERMINAL ELEMENTS     \n", util::BOLD);
    util::printColor("=========================================\n", util::FG_MAGENTA);

    int numPlayers, numEnemies;
    vector<FighterCharacter*> players;
    vector<FighterCharacter*> enemies;

    // 1. Setup Players
    cout << "How many players? (1-4): ";
    while (!(cin >> numPlayers) || numPlayers < 1 || numPlayers > 4) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Invalid. Try 1-4: ";
    }
    for (int i = 0; i < numPlayers; i++) {
        players.push_back(createPlayer(i));
    }

    // 2. Setup Enemies
    cout << "\nHow many enemies? (1-4): ";
    while (!(cin >> numEnemies) || numEnemies < 1 || numEnemies > 4) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Invalid. Try 1-4: ";
    }
    for (int i = 0; i < numEnemies; i++) {
        enemies.push_back(createNPC(i));
    }

    // 3. Hand over control to the BattleManager
    BattleManager battle(players, enemies);
    
    util::printColor("\n--- THE BATTLE BEGINS ---\n", util::FG_YELLOW);
    util::showLoadingSpinner("Loading Arena... ", 1500); // Visual flair before starting
    
    battle.runBattle();

    return 0; 
}
