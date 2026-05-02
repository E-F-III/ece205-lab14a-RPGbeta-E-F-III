//  University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    FireBender.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
/// FireBender is a derived class of PlayerCharacter.
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "PlayerCharacter.hpp"
#include "FireBender.hpp"
#include "Fire_Bending.hpp"
#include "util/TextDisplay.hpp"
using namespace std;
/// Constructor: initializes the fire bending system
FireBender::FireBender(std::string& characterName, int& raceCode) : PlayerCharacter(characterName, raceCode) {
    // Initialize fire bending system
    fireBendingSystem = new FireBending();
}
// Destructor: Cleanup pointer to prevent memory leaks
FireBender::~FireBender() {
    delete fireBendingSystem;
    // Free memory allocated in constructor
}
/// use bending system to perform a fire bending action
void FireBender::performAction(FighterCharacter& target) {
    int choice = -1;
    // Initialize choice variable for loop validation
    util::printColor("\nGame Master: What would you like " + name + " to do?\n", util::FG_CYAN);
    
    fireBendingSystem->getAvailableBendingActions(*this); // Display available actions
    
    // Loop ensures the options 0-2 are selected (Validation)
    while (choice < 0 || choice > 2) {
        cout << "Enter the number corresponding to your choice (0=Blast, 1=Breath, 2=Lightning): ";
        cin >> choice;
        if (choice < 0 || choice > 2) {
            util::printColor("Invalid input! Please enter a number between 0 and 2.\n", util::FG_RED);
            cout << endl;
        }
    }
    
    // Call the appropriate function in fireBendingSystem based on user selection.
    switch (choice) {
        case 0:
            util::printColor("\n--- Action Selected: Fire Blast ---\n", util::FG_RED);
            fireBendingSystem->fireBlast(*this, target);
            break;
        case 1:
            util::printColor("\n--- Action Selected: Fire Breath ---\n", util::FG_RED);
            fireBendingSystem->fireBreath(*this, target);
            break;
        case 2:
            util::printColor("\n--- Action Selected: Lightning Strike ---\n", util::FG_RED);
            fireBendingSystem->lightningStrike(*this, target);
            break;
    }
}
/// Print FireBender-specific stats in addition to base stats
void FireBender::printStats() {
    PlayerCharacter::printStats();
    util::printColor("Profession: FireBender\n", util::FG_RED);
    cout << "------------------------------------" << endl;
}
/// FireBender-specific greeting
void FireBender::greet() const {
    util::printColor(name + " the FireBender: ", util::FG_RED);
    util::printType("Greetings! I am " + name + ". The flames are at my command, and I will use them to protect my allies\n", 30);
}
