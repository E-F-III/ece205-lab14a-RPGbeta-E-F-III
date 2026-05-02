///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 11a - Game Character Class Part II - ECE 205 - Spring 2025
//
///
/// @file    NPC_Character.cpp
/// @author  Edward Felipe III <sdjavier@hawaii.edu>
/// NPCharacter is a derived class of GameCharacter. NPCharacters are non-player characters that can be either allies or enemies in the game.
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <random>
#include "GameCharacter.hpp"
#include "NPCharacter.hpp"
#include "util/TextDisplay.hpp"

using namespace std;

/// constructor declaration for "PlayerCharacter"
/// takes in address of name from user and int corresponding to race
/// inherited from GameCharacter, note only the setName() member is used,
// (since no race member)
NPCharacter::NPCharacter(string& characterName, int& bendingStyleCode) 
    : FighterCharacter(characterName, bendingStyleCode) 
{
    // No extra logic for now, but you could add NPC-specific initialization here if needed
}

///greeting using the name of PlayerCharacter
void NPCharacter::greet() const {
    util::printColor("[" + name + "]: ", util::FG_WHITE);
    cout << "Hello, my name is " << name << ". How can I help with your quest?" << endl;
}

void NPCharacter::performAction(FighterCharacter& target) {
    util::printColor("NPC [" + name + "] performs action on " + target.getName() + "!\n", util::FG_WHITE);
    cout << "I am performing an action on " << target.getName() << "!" << endl;
}
