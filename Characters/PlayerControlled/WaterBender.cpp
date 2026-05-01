///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    WaterBender.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
/// WaterBender is a derived class of PlayerCharacter.
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "PlayerCharacter.hpp"
#include "WaterBender.hpp"
#include "Water_Bending.hpp"
#include "util/TextDisplay.hpp"

using namespace std;

/// Constructor: initializes the water bending system
WaterBender::WaterBender(std::string& characterName, int& raceCode) : PlayerCharacter(characterName, raceCode) {
    // Initialize water bending system
    waterBendingSystem = new WaterBending();
}

// Destructor: Cleanup pointer to prevent memory leaks
WaterBender::~WaterBender() {
    delete waterBendingSystem;
    // Free memory allocated in constructor
}

/// use bending system to perform a water bending action
void WaterBender::performAction(FighterCharacter& target) {
    int choice = -1;
    // Initialize choice variable for loop validation
    util::printColor("\nGame Master: What would you like " + name + " to do?" << endl, util::FG_CYAN);
    
    waterBendingSystem->getAvailableBendingActions(*this); // Display available actions
    
    // Loop ensures the options 0-2 are selected (Validation)
    while (choice < 0 || choice > 2) {
        cout << "Enter the number corresponding to your choice (0=Healing, 1=Whip, 2=Barrier): ";
        cin >> choice;
        if (choice < 0 || choice > 2) {
            util::printColor("Invalid input! Please enter a number between 0 and 2.\n", util::FG_RED);
            cout << endl;
        }
    }
    
    // Call the appropriate function in waterBendingSystem based on user selection.
    switch (choice) {
        case 0:
            util::printColor("\n--- Action Selected: Healing Waters ---\n", util::FG_CYAN);
            waterBendingSystem->healingWaters(*this, target);
            break;
        case 1:
            util::printColor("\n--- Action Selected: Water Whip ---\n", util::FG_CYAN);
            waterBendingSystem->waterWhip(*this, target);
            break;
        case 2:
            util::printColor("\n--- Action Selected: Ice Barrier ---\n", util::FG_CYAN);
            waterBendingSystem->iceBarrier(*this, target);
            break;
    }
}

/// Print WaterBender-specific stats in addition to base stats
void WaterBender::printStats() {
    PlayerCharacter::printStats();
    util::printColor("Profession: WaterBender\n", util::FG_CYAN);
    cout << "------------------------------------" << endl;
}

/// WaterBender-specific greeting
void WaterBender::greet() const {
    util::printColor(name + " the WaterBender: ", util::FG_CYAN);
    util::printType("Greetings! I am " + name + ". The water is at my command, and I will use it to protect my allies\n", 30);
}
