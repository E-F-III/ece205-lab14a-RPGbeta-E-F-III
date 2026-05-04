//  University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    NPCEarthBender.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
/// NPCEarthBender is a derived class of NPCharacter. EarthBenders use earth manipulation to fight enemies and protect allies.
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "GameCharacter.hpp"
#include "NPCharacter.hpp"
#include "NPCEarthBender.hpp"
#include "Earth_Bending.hpp"
#include "util/TextDisplay.hpp"
using namespace std;
/// Constructor: initializes the earth bending system
NPCEarthBender::NPCEarthBender(std::string& characterName, int& raceCode) : NPCharacter(characterName, raceCode) {
    // Initialize earth bending system
    earthBendingSystem = new EarthBending();
}
// Destructor: Cleanup pointer to prevent memory leaks
NPCEarthBender::~NPCEarthBender() {
    delete earthBendingSystem;
    // Free memory allocated in constructor
}
/// use bending system to perform an earth bending action
void NPCEarthBender::performAction(FighterCharacter& target) {
    util::printColor("\n[AI] " + name + " performs an Earth Bending action!\n", util::FG_CYAN);
    
    // for now, randomize the action selection for NPCs
    int choice = rand() % 3; // Randomly select an action (0, 1, or 2)
    switch (choice) {
        case 0:
            cout << "\n--- Action Selected: Earth Spike ---\n" << endl;
            earthBendingSystem->earthSpike(*this, target);
            break;
        case 1:
            cout << "\n--- Action Selected: Rock Throw ---\n" << endl;
            earthBendingSystem->rockThrow(*this, target);
            break;
        case 2:
            cout << "\n--- Action Selected: Seismic Slam ---\n" << endl;
            earthBendingSystem->seismicSlam(*this, target);
            break;
        // case 1:
        //     cout << "\n--- Action Selected: Rock Shield ---\n" << endl;
        //     earthBendingSystem->rockShield(*this, target);
        //     break;
        // case 2:
        //     cout << "\n--- Action Selected: Seismic Slam ---\n" << endl;
        //     earthBendingSystem->seismicSlam(*this, target);
        //     break;
    }
}
/// Print EarthBender-specific stats in addition to base stats
void NPCEarthBender::printStats() {
    NPCharacter::printStats();
    util::printColor("Profession: EarthBender\n", util::FG_MAGENTA);
    cout << "------------------------------------" << endl;
}
/// EarthBender-specific greeting
void NPCEarthBender::greet() const {
    util::printColor(name + " the EarthBender: ", util::FG_MAGENTA);
    util::printType("Greetings! I am " + name + ". The earth is at my command, and I will use it to protect my allies\n", 30);
}
