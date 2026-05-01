///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    Earth_Bending.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Earth_Bending.hpp"
#include "util/TextDisplay.hpp"

using namespace std;

/// Constructor: initializes the earth bending system
EarthBending::EarthBending() {
    // No specific initialization required
}

// Earth Spike: a sharp spike of earth that can impale enemies
void EarthBending::earthSpike(FighterCharacter& character, FighterCharacter& target) {
    util::printColor(character.getName() + " uses Earth Spike on " + target.getName() + "!\n", util::FG_MAGENTA);
    
    cout << "\nEarth Spike hits!" << endl;
    
    int targetHealth = target.getHealth();
    
    // Calculate damage: Diceroll between 5 and 10 for spike attack
    int damage = FighterCharacter::rollDice(5, 10); 
    
    // Update health via getter/setter to ensure specific instance update
    target.setHealth(targetHealth - damage); 
    
    util::printColor("Earth Spike deals " + std::to_string(damage) + " damage to " + target.getName() + "\n", util::FG_MAGENTA); 
}

// Rock Shield: creates a sturdy shield of rock that can block attacks
void EarthBending::rockShield(FighterCharacter& character, FighterCharacter& target) {
    util::printColor(character.getName() + " uses Rock Shield to protect " + target.getName() + "!\n", util::FG_MAGENTA);
    
    cout << "\nRock Shield activates!" << endl;
    cout << "Shield logic not fully implemented yet, but it will block the next incoming attack." << endl;
    // In this simple game, shielding prevents immediate damage
    target.setHealth(target.getHealth()); 
}

// Seismic Slam: slams the ground to create a shockwave that damages and knocks back enemies
void EarthBending::seismicSlam(FighterCharacter& character, FighterCharacter& target) {
    util::printColor(character.getName() + " uses Seismic Slam on " + target.getName() + "!\n", util::FG_MAGENTA);
    
    cout << "\nSeismic Slam hits!" << endl;

    int targetHealth = target.getHealth();
    
    // Calculate damage: Higher range for slam attack
    int damage = FighterCharacter::rollDice(8, 15); 
    
    // Update health via getter/setter to ensure specific instance update
    target.setHealth(targetHealth - damage); 
    
    util::printColor("Seismic Slam deals " + std::to_string(damage) + " damage to " + target.getName() + "\n", util::FG_MAGENTA); 
}

std::vector<std::string> EarthBending::getAvailableBendingActions(FighterCharacter& character) {
    vector<std::string> actions = {"Earth Spike", "Rock Shield", "Seismic Slam"};
    
    cout << "Available Earth Bending Actions for " + character.getName() + ":\n";
    for (size_t i = 0; i < actions.size(); ++i) {
        cout << i << ": " << actions[i] << endl;
    }
    return actions;
}
