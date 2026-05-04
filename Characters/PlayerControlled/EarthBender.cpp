//  University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    EarthBender.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "PlayerCharacter.hpp"
#include "EarthBender.hpp"
#include "Earth_Bending.hpp"
#include "util/TextDisplay.hpp"
using namespace std;
/// Constructor: initializes the earth bending system
EarthBender::EarthBender(std::string& characterName, int& raceCode) : PlayerCharacter(characterName, raceCode) {
    // Initialize earth bending system
    earthBendingSystem = new EarthBending();
}
// Destructor: Cleanup pointer to prevent memory leaks
EarthBender::~EarthBender() {
    delete earthBendingSystem;
    // Free memory allocated in constructor
}
/// use bending system to perform an earth bending action
void EarthBender::performAction(FighterCharacter& target) {
    int choice = -1;
    // Initialize choice variable for loop validation
    util::printColor("\nGame Master: What would you like " + name + " to do?\n", util::FG_CYAN);
    
    earthBendingSystem->getAvailableBendingActions(*this); // Display available actions
    
    // Loop ensures the options 0-2 are selected (Validation)
    while (choice < 0 || choice > 2) {
        cout << "Enter the number corresponding to your choice (0=Spike, 1=Shield, 2=Slam): ";
        cin >> choice;
        if (choice < 0 || choice > 2) {
            util::printColor("Invalid input! Please enter a number between 0 and 2.\n", util::FG_RED);
            cout << endl;
        }
    }
    
    // Call the appropriate function in earthBendingSystem based on user selection.
    switch (choice) {
        case 0:
            util::printColor("\n--- Action Selected: Earth Spike ---\n", util::FG_MAGENTA);
            earthBendingSystem->earthSpike(*this, target);
            break;
        case 1:
            util::printColor("\n--- Action Selected: Rock Throw ---\n", util::FG_MAGENTA);
            earthBendingSystem->rockThrow(*this, target);
            break;
        case 2:
            util::printColor("\n--- Action Selected: Seismic Slam ---\n", util::FG_MAGENTA);
            earthBendingSystem->seismicSlam(*this, target);
            break;
        // case 1:
        //     util::printColor("\n--- Action Selected: Rock Shield ---\n", util::FG_WHITE);
        //     earthBendingSystem->rockShield(*this, target);
        //     break;
        // case 2:
        //     util::printColor("\n--- Action Selected: Seismic Slam ---\n", util::FG_MAGENTA);
        //     earthBendingSystem->seismicSlam(*this, target);
        //     break;
    }
}
/// Print EarthBender-specific stats in addition to base stats
void EarthBender::printStats() {
    PlayerCharacter::printStats();
    util::printColor("Profession: EarthBender\n", util::FG_MAGENTA);
    cout << "------------------------------------" << endl;
}
/// EarthBender-specific greeting
void EarthBender::greet() const {
    util::printColor(name + " the EarthBender: ", util::FG_MAGENTA);
    util::printType("Greetings! I am " + name + ". The earth is at my command, and I will use it to protect my allies\n", 30);
}
