///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    Air_Bending.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Air_Bending.hpp"
#include "util/TextDisplay.hpp"

using namespace std;

/// Constructor: initializes the air bending system
AirBending::AirBending() {
    // Initialize any air bending specific attributes if needed
}

// Air Slice: a quick, slicing gust of wind that can cut through enemies
void AirBending::airSlice(FighterCharacter& character, FighterCharacter& target) {
    cout << character.getName() << " is gathering wind... ";
    util::showLoadingSpinner("", 1000); // Visual "charging" effect
    
    util::printColor("\nAir Slice hits! A sharp gust of wind cuts through the enemy.\n", util::FG_YELLOW);
    
    int targetHealth = target.getHealth();
    int damage = FighterCharacter::rollDice(5, 10);
    target.setHealth(targetHealth - damage);

    cout << "Air Slice deals " << damage << " damage to " << target.getName() << endl;
}

// Air Shield: creates a swirling barrier of wind that protects and deflects attacks
void AirBending::airShield(FighterCharacter& character, FighterCharacter& target) {
    cout << character.getName() << " creates an Air Shield! ";
    util::showLoadingSpinner("", 500);
    util::printColor("\nA swirling barrier of wind protects them from incoming attacks.\n", util::FG_YELLOW);
    cout << "Shield logic not fully implemented yet." << endl;
}

// Flight: allows the character to take to the skies, increasing mobility and evasion
void AirBending::flight(FighterCharacter& character) {
    util::printColor(character.getName() + " takes to the skies with Flight!\n", util::FG_YELLOW);
}

std::vector<std::string> AirBending::getAvailableBendingActions(FighterCharacter& character) {
    vector<std::string> actions = {"Air Slice", "Air Shield", "Flight"};
    util::printColor("Available Air Bending Actions for " + character.getName() + ":\n", util::FG_YELLOW);
    for (size_t i = 0; i < actions.size(); ++i) {
        cout << i << ": " << actions[i] << endl;
    }
    return actions;
}
