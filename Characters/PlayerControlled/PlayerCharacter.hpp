///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 11a - Game Character Class Part II - ECE 205 - Spring 2025
//
///
/// @file    PlayerCharacter.hpp
/// @author  Steven Daniel Javier <sdjavier@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#ifndef PLAYERCHARACTER_HPP
#define PLAYERCHARACTER_HPP

#include "FighterCharacter.hpp"
#include <string>

class PlayerCharacter : public FighterCharacter {
    public:
        // Pass parameters up to the FighterCharacter constructor
        PlayerCharacter(std::string& characterName, int& bendingStyleCode, bool demoMode);

        bool demoMode; // Flag to indicate if the player is in demo mode (for testing purposes)

        virtual ~PlayerCharacter() = default;

        // You can override greet if players have a specific greeting
        void greet() const override;

        // Specific player logic (like manual target selection)
        void performAction(FighterCharacter& target) override;
};

#endif
