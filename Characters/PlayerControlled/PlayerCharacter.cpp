///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    PlayerCharacter.cpp
/// @author  Steven Daniel Javier <sdjavier@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include "GameCharacter.hpp"
#include "PlayerCharacter.hpp"
#include "util/TextDisplay.hpp"

using namespace std;

/// constructor declaration for "PlayerCharacter"
/// takes in address of name from user and int corresponding to race
/// inherited from GameCharacter, note only the setName() member is used,
// (since no race member)
PlayerCharacter::PlayerCharacter(std::string& characterName, int& bendingStyleCode)
    : FighterCharacter(characterName, bendingStyleCode) 
{
    // No extra logic for now, but you could add player-specific initialization here if needed
}

///greeting using the name of PlayerCharacter
void PlayerCharacter::greet() const {
    util::printColor(name + ": ", util::FG_WHITE);
    cout << "Hello, my name is " << name << ". How can I help with your quest?" << endl;
}

void PlayerCharacter::performAction(FighterCharacter& target) {
    util::printColor("[" + name + "] performing action on " + target.getName() + "!\n", util::FG_CYAN);
    cout << "I am performing an action  on " << target.getName() << "!" << endl;
}
