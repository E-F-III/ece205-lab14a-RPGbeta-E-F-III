///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 11a - Game Character Class Part II - ECE 205 - Spring 2025
//
/// @file    Bending_System.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Bending_System.hpp"
#include "PlayerCharacter.hpp"
#include "util/TextDisplay.hpp"

using namespace std;

/// Constructor: initializes the bending system
BendingSystem::BendingSystem() {
    // Initialize any common bending system attributes if needed
}

/// Display available bending actions for a given character
std::vector<std::string> BendingSystem::getAvailableBendingActions(FighterCharacter& character) {
    util::printColor("\n[SYSTEM] Available bending actions for " + character.getName() + ":\n", util::FG_CYAN);
    std::vector<std::string> dummy_actions;
    cout << "  (System Menu Logic Placeholder)\n"; 
    return dummy_actions; // Placeholder return, replace with actual available actions (fixes warning)
}
