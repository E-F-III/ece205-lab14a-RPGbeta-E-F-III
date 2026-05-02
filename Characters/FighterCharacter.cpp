///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    FighterCharacter.cpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
/// FighterCharacter is a derived class of GameCharacter.
/// FighterCharacters are GameCharacters that specialize in physical combat, using their strength and agility to defeat enemies.
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <random>
#include "GameCharacter.hpp"
#include "FighterCharacter.hpp"
#include "util/TextDisplay.hpp"
using namespace std;

int FighterCharacter::rollDice(int lower, int upper) {
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<int> distribution(lower, upper);
    return distribution(engine);
}

FighterCharacter::FighterCharacter(std::string& name, int& styleCode) : GameCharacter(name) {
    this->health = 100;
    this->strength = rollDice(0, 10);
    this->agility = rollDice(0, 10);
    this->defense = rollDice(0, 10);
    setBendingStyle(styleCode); // Set the style only for fighters.
}

FighterCharacter::~FighterCharacter() {
    // Virtual destructor implementation
}

void FighterCharacter::setBendingStyle(int choice) {
    switch (choice) {
        case 0: bendingStyle = air; break;
        case 1: bendingStyle = earth; break;
        case 2: bendingStyle = fire; break;
        case 3: bendingStyle = water; break;
    }
}

// Getters
int FighterCharacter::getHealth() {
    return health;
}

int FighterCharacter::getStrength() {
    return strength;
}

int FighterCharacter::getAgility() {
    return agility;
}

int FighterCharacter::getDefense() {
    return defense;
}

BendingStyle FighterCharacter::getBendingStyle() {
    return bendingStyle;
}

// Setters
void FighterCharacter::setHealth(int health) {
    this->health = health;
}

void FighterCharacter::setStrength(int strength) {
    this->strength = strength;
}

void FighterCharacter::setAgility(int agility) {
    this->agility = agility;
}

void FighterCharacter::setDefense(int defense) {
    this->defense = defense;
}

void FighterCharacter::printStats() {
    std::string styleNames[] = {"Air", "Earth", "Fire", "Water"};
    util::printColor("--- " + name + " Stats ---\n", util::FG_WHITE);
    std::cout << "Bending: " << styleNames[bendingStyle] << std::endl;
    util::printColor("Health: " + std::to_string(health) + "\n", util::FG_GREEN);
}

void FighterCharacter::greet() const {
    cout << name + ": Greetings! I am a master of bending arts!" << endl;
}

// perform action is a placeholder for now, but it will be the main function that handles combat logic and interactions with other characters.
void FighterCharacter::performAction(FighterCharacter& target) {
    std::cout << name + " performs a basic attack on " << target.getName() + "!" << std::endl;
    // Basic attack logic can be implemented here, and this method can be overridden by derived classes for more specific actions.
}
