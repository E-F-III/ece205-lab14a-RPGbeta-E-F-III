///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 11a - Game Character Class Part II - ECE 205 - Spring 2025
//
/// @file    main.cpp
/// @author  Steven Daniel Javier <sdjavier@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

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

using namespace std;

// --- Helper Functions (Factory Pattern) ---

PlayerCharacter* createPlayer(int i) {
    string name;
    int code;
    cout << "\nEnter name for Player " << (i + 1) << ": ";
    cin.ignore(1000, '\n'); 
    getline(cin, name);

    cout << "Bending (0:Air, 1:Earth, 2:Fire, 3:Water): ";
    while (!(cin >> code) || code < 0 || code > 3) {
        cout << "Invalid. Enter 0-3: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    switch (code) {
        case 0: return new AirBender(name, code);
        case 1: return new EarthBender(name, code);
        case 2: return new FireBender(name, code);
        case 3: return new WaterBender(name, code);
        default: return nullptr;
    }
}

NPCharacter* createNPC(int i) {
    int code = rand() % 4;
    string name = "Enemy " + to_string(i + 1);
    switch (code) {
        case 0: return new NPCAirBender(name, code);
        case 1: return new NPCEarthBender(name, code);
        case 2: return new NPCFireBender(name, code);
        case 3: return new NPCWaterBender(name, code);
        default: return nullptr;
    }
}

// --- Main Execution ---

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

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
    // We pass the vectors to the manager. It will handle the loop AND the deletion.
    BattleManager battle(players, enemies);
    
    cout << "\n--- THE BATTLE BEGINS ---" << endl;
    battle.runBattle();

    return 0; 
}