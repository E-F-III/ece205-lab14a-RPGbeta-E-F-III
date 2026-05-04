//  University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    AirBender.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "PlayerCharacter.hpp"
#include "AirBender.hpp"
#include "Air_Bending.hpp"
#include "util/TextDisplay.hpp"
using namespace std;
// --- Constructor and Destructor ---
/// Constructor: initializes the air bending system
AirBender::AirBender(std::string& characterName, int& raceCode, bool demoMode) : PlayerCharacter(characterName, raceCode, demoMode) {
    airBendingSystem = new AirBending();
    // Initialize the air bending system pointer
}
// Destructor: This MUST be defined to clean up memory allocated in the constructor.
AirBender::~AirBender() {
    delete airBendingSystem;
}
/// use bending system to perform an air bending action (This function contains the menu logic)
void AirBender::performAction(FighterCharacter& target) {
    int choice = -1;
    // Initialize choice variable for loop validation
    util::printColor("\nGame Master: What would you like " + name + " to do?\n", util::FG_CYAN);
    airBendingSystem->getAvailableBendingActions(*this); // Display available options
    // Loop ensured the options 0-2 are selected (Input Validation)
    while (choice < 0 || choice > 2) {
        cout << "Enter the number corresponding to your choice (0=Slice, 1=Shield, 2=Flight): ";
        cin >> choice;
        if (choice < 0 || choice > 2) {
            cout << "Invalid input! Please enter a number between 0 and 2." << endl;
        }
    }
    // Call the appropriate function in airBendingSystem based on user selection.
    switch (choice) {
        case 0:
            util::printColor("\n--- Action Selected: Air Slice ---\n", util::FG_YELLOW);
            airBendingSystem->airSlice(*this,target);
            break;
        case 1:
            util::printColor("\n--- Action Selected: Air Blast ---\n", util::FG_YELLOW);
            airBendingSystem->airBlast(*this, target);
            break;
        case 2:
            util::printColor("\n--- Action Selected: Tornado ---\n", util::FG_YELLOW);
            airBendingSystem->tornado(*this, target);
            break;
        // case 1:
        //     util::printColor("\n--- Action Selected: Air Shield ---\n", util::FG_YELLOW);
        //     airBendingSystem->airShield(*this, target); 
        //     break;
        // case 2:
        //     util::printColor("\n--- Action Selected: Flight ---\n", util::FG_YELLOW);
        //     airBendingSystem->flight(*this);
        //     break;
    }
}
/// Print AirBender-specific stats in addition to base stats
void AirBender::printStats() {
    PlayerCharacter::printStats();
    util::printColor("Profession: AirBender\n", util::FG_YELLOW);
    cout << "------------------------------------" << endl;
}
/// AirBender-specific greeting
void AirBender::greet() const {
    util::printColor(name + " the AirBender: ", util::FG_YELLOW);
    util::printType("Greetings! I am " + name + ". The wind is at my command, and I will use it to protect my allies\n", 30);
}
