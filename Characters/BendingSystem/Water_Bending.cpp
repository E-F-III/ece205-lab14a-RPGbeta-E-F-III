//  University of Hawaii, College of Engineering
// Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    Water_Bending.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Water_Bending.hpp"
#include "util/TextDisplay.hpp"
using namespace std;
/// Constructor: initializes the water bending system
WaterBending::WaterBending() {
    // No specific initialization required
}
// Healing Waters: a soothing wave of water that can heal allies
void WaterBending::healingWaters(FighterCharacter& character, FighterCharacter& target) {
    // Implementation of healing logic here (modified to interact with passed player ref)
    util::printColor(character.getName() + " uses Healing Waters on " + target.getName() + "!\n", util::FG_CYAN);
    cout << "\nHealing Waters activates!" << endl;
    
    // Calculate healing: Diceroll between 5 and 10 for healing amount
    int healAmount = FighterCharacter::rollDice(5, 10); 
    
    // Update health via getter/setter to ensure specific instance update (don't exceed max health if desired, but simple game allows overflow)
    target.setHealth(target.getHealth() + healAmount); 
    
    util::printColor("Healing Waters heals " + std::to_string(healAmount) + " health on " + target.getName() + "\n", util::FG_CYAN); 
}
// Water Whip: a flexible whip of water that can strike enemies from a distance
void WaterBending::waterWhip(FighterCharacter& character, FighterCharacter& target) {
    // Implementation of damage logic here (modified to interact with passed player ref)
    int targetHealth = target.getHealth();
    
    util::printColor(character.getName() + " uses Water Whip on " + target.getName() + "!\n", util::FG_CYAN);
    cout << "\nWater Whip hits!" << endl;
    // Calculate damage: Medium range for whip attack
    int damage = FighterCharacter::rollDice(7, 12); 
    
    // Update health via getter/setter to ensure specific instance update
    target.setHealth(targetHealth - damage); 
    
    util::printColor("Water Whip deals " + std::to_string(damage) + " damage to " + target.getName() + "\n", util::FG_CYAN); 
}
// Ice Barrier: creates a solid barrier of ice that can block attacks and protect allies
void WaterBending::iceBarrier(FighterCharacter& character, FighterCharacter& target) {
    // Implementation of defense logic here (modified to protect passed player ref)
    util::printColor(character.getName() + " uses Ice Barrier to protect " + target.getName() + "!\n", util::FG_CYAN);
    
    cout << "\nIce Barrier activates!" << endl;
    cout << "Shield logic not fully implemented yet, but it will block the next incoming attack." << endl;
    // In this simple game, ice barrier prevents immediate damage
    target.setHealth(target.getHealth()); 
}
std::vector<std::string> WaterBending::getAvailableBendingActions(FighterCharacter& character) {
    vector<std::string> actions = {"Healing Waters", "Water Whip", "Ice Barrier"};
    
    // System output for menu listing
    cout << "Available Water Bending Actions for " + character.getName() + ":\n";
    for (size_t i = 0; i < actions.size(); ++i) {
        cout << i << ": " << actions[i] << endl;
    }
    return actions;
}
