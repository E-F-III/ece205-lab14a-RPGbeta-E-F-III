//  University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    Fire_Bending.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Fire_Bending.hpp"
#include "util/TextDisplay.hpp"
using namespace std;
/// Constructor: initializes the fire bending system
FireBending::FireBending() {
    // No specific initialization required
}
// Fire Blast: a powerful blast of fire that can burn enemies
void FireBending::fireBlast(FighterCharacter& character, FighterCharacter& target) {
    
    util::printColor(character.getName() + " uses Fire Blast on " + target.getName() + "!\n", util::FG_RED);
    
    cout << "\nFire Blast hits!" << endl;
    // Calculate damage: Medium range for fire blast
    int damage = FighterCharacter::rollDice(7, 12); 
    
    // Update health via getter/setter to ensure specific instance update
    target.setHealth(target.getHealth() - damage); 
    
    util::printColor("Fire Blast deals " + std::to_string(damage) + " damage to " + target.getName() + "\n", util::FG_RED); 
}
// Fire Breath: the character exhales a cone of fire that can damage multiple enemies
void FireBending::fireBreath(FighterCharacter& character, FighterCharacter& target) {
    // Area damage logic here (applied to current target for simplicity in this game)
    cout << character.getName() + " uses Fire Breath on " + target.getName() + "!" << endl;
    cout << "\nFire Breath activates!" << endl;
    
    // Calculate area damage: Cone of fire deals moderate damage
    int damage = FighterCharacter::rollDice(6, 11); 
    
    target.setHealth(target.getHealth() - damage);
    util::printColor("Fire Breath deals " + std::to_string(damage) + " damage to " + target.getName() + "\n", util::FG_RED); 
}
// Lightning Strike: the character generates a bolt of lightning that can strike a single enemy with high damage
void FireBending::lightningStrike(FighterCharacter& character, FighterCharacter& target) {
    // High damage logic here (modified to interact with passed player ref)
    util::printColor(character.getName() + " uses Lightning Strike on " + target.getName() + "!\n", util::FG_RED);
    
    cout << "\nLightning Strike hits!" << endl;
    // Calculate damage: High range for lightning attack
    int damage = FighterCharacter::rollDice(12, 20); 
    
    // Update health via getter/setter to ensure specific instance update
    target.setHealth(target.getHealth() - damage); 
    
    util::printColor("Lightning Strike deals " + std::to_string(damage) + " damage to " + target.getName() + "\n", util::FG_RED); 
}
std::vector<std::string> FireBending::getAvailableBendingActions(FighterCharacter& character) {
    vector<std::string> actions = {"Fire Blast", "Fire Breath", "Lightning Strike"};
    
    // System output for menu listing
    cout << "Available Fire Bending Actions for " << character.getName() << ":" << endl;
    for (size_t i = 0; i < actions.size(); ++i) {
        cout << i << ": " << actions[i] << endl;
    }
    return actions;
}
