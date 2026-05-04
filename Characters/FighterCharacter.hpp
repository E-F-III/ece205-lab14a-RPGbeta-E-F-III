///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 11a - Game Character Class Part II - ECE 205 - Spring 2025
//
///
/// @file    FighterCharacter.hpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
/// FighterCharacter is a derived class of GameCharacter.
/// FighterCharacters are GameCharacters that specialize in physical combat, using their strength and agility to defeat enemies.
/////////////////////////////////////////////////////////////////////////////////

#ifndef FIGHTERCHARACTER_HPP
#define FIGHTERCHARACTER_HPP

#include <iostream>
#include "GameCharacter.hpp"

class FighterCharacter : public GameCharacter {
    protected:
        int health;
        int strength;
        int agility;
        int defense;
        bool demoMode; // Flag to indicate if the character is in demo mode (for testing purposes)
        BendingStyle bendingStyle;

    public:
        FighterCharacter(std::string& characterName, int& bendingStyleCode, bool demoMode);

        virtual ~FighterCharacter(); // Virtual destructor for proper cleanup of derived classes

        // Getters
        int getHealth();
        int getStrength();
        int getAgility();
        int getDefense();
        bool isDemoMode() const;
        BendingStyle getBendingStyle();

        // Setters
        void setHealth(int health);
        void setStrength(int strength);
        void setAgility(int agility);
        void setDefense(int defense);
        void setBendingStyle(int bendingStyleChoice);
        
        static int rollDice(int lower, int upper);

        // UI Methods
        void printStats();
        void greet() const override;

        // Action logic
        virtual void performAction(FighterCharacter& target); // Base implementation can be overridden by derived classes for specific actions
};

#endif //FIGHTERCHARACTER_HPP