//  University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    NPCWaterBender.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
/// NPCWaterBender is a derived class of NPCharacter. WaterBenders use water manipulation to fight enemies and protect allies.
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "GameCharacter.hpp"
#include "NPCharacter.hpp"
#include "NPCWaterBender.hpp"
#include "Water_Bending.hpp"
#include "util/TextDisplay.hpp"
using namespace std;
/// Constructor: initializes the water bending system
NPCWaterBender::NPCWaterBender(std::string& characterName, int& raceCode) : NPCharacter(characterName, raceCode) {
    // Initialize water bending system
    waterBendingSystem = new WaterBending();
}
// Destructor: Cleanup pointer to prevent memory leaks
NPCWaterBender::~NPCWaterBender() {
    delete waterBendingSystem;
    // Free memory allocated in constructor
}
/// use bending system to perform a water bending action
void NPCWaterBender::performAction(FighterCharacter& target) {
    util::printColor("\n[AI] " + name + " performs a Water Bending action!\n", util::FG_CYAN);
    
    // for now, randomize the action selection for NPCs
    int choice = rand() % 3; // Randomly select an action (0, 1, or 2)
    switch (choice) {
        case 0:
            cout << "\n--- Action Selected: Healing Waters ---\n" << endl;
            waterBendingSystem->healingWaters(*this, target);
            break;
        case 1: 
            cout << "\n--- Action Selected: Water Whip ---\n" << endl;
            waterBendingSystem->waterWhip(*this, target);
            break;
        case 2:
            cout << "\n--- Action Selected: Water Vortex ---\n" << endl;
            waterBendingSystem->waterVortex(*this, target);
            break;
        // case 1:
        //     cout << "\n--- Action Selected: Water Whip ---\n" << endl;
        //     waterBendingSystem->waterWhip(*this, target);
        //     break;
        // case 2:
        //     cout << "\n--- Action Selected: Ice Barrier ---\n" << endl;
        //     waterBendingSystem->iceBarrier(*this, target);
        //     break;
    }
}
/// Print WaterBender-specific stats in addition to base stats
void NPCWaterBender::printStats() {
    NPCharacter::printStats();
    util::printColor("Profession: WaterBender\n", util::FG_CYAN);
    cout << "------------------------------------" << endl;
}
/// WaterBender-specific greeting
void NPCWaterBender::greet() const {
    util::printColor(name + " the WaterBender: ", util::FG_CYAN);
    util::printType("Greetings! I am " + name + ". The water is at my command, and I will use it to protect my allies\n", 30);
}
