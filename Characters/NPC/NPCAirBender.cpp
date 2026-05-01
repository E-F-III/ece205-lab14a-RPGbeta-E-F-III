///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    NPCAirBender.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
/// NPCAirBender is a derived class of NPCharacter. AirBenders use air manipulation to fight enemies and protect allies.
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "GameCharacter.hpp"
#include "NPCharacter.hpp"
#include "NPCAirBender.hpp"
#include "Air_Bending.hpp"
#include "util/TextDisplay.hpp"

using namespace std;

// --- Constructor and Destructor --- 
/// Constructor: initializes the air bending system
NPCAirBender::NPCAirBender(std::string& characterName, int& raceCode) : NPCharacter(characterName, raceCode) {
    airBendingSystem = new AirBending();
    // Initialize the air bending system pointer
}

// Destructor: This MUST be defined to clean up memory allocated in the constructor.
NPCAirBender::~NPCAirBender() {
    delete airBendingSystem; 
}

/// use bending system to perform an air bending action (This function contains the menu logic)
void NPCAirBender::performAction(FighterCharacter& target) {
    util::printColor("\n[AI] " + name + " performs an Air Bending action!\n", util::FG_CYAN);
    
    // for now, randomize the action selection for NPCs
    int choice = rand() % 3; // Randomly select an action (0, 1, or 2)
    switch (choice) {
        case 0:
            cout << "\n--- Action Selected: Air Slice ---\n" << endl;
            airBendingSystem->airSlice(*this, target);
            break;
        case 1:
            cout << "\n--- Action Selected: Air Shield ---\n" << endl;
            airBendingSystem->airShield(*this, target);
            break;
        case 2:
            cout << "\n--- Action Selected: Air Gust ---\n" << endl;
            airBendingSystem->flight(*this);
            break;
    }
}

/// Print AirBender-specific stats in addition to base stats
void NPCAirBender::printStats() {
    NPCharacter::printStats();
    util::printColor("Profession: AirBender\n", util::FG_YELLOW);
    cout << "------------------------------------" << endl;
}

/// AirBender-specific greeting
void NPCAirBender::greet() const {
    util::printColor(name + " the AirBender: ", util::FG_YELLOW);
    util::printType("Greetings! I am " + name + ". The wind is at my command, and I will use it to protect my allies\n", 30);
}
