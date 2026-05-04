///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    Water_Bending.hpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
///
/// WaterBender is a derived class of PlayerCharacter. WaterBenders use water manipulation to fight enemies and protect allies.
///////////////////////////////////////////////////////////////////////////////
#ifndef WATER_BENDING_HPP
#define WATER_BENDING_HPP
#include "Bending_System.hpp"
/// WaterBending: manages water bending abilities for WaterBender characters
class WaterBending : public BendingSystem { // Base class is BendingSystem
public:
    /// Constructor: initializes the water bending system
    WaterBending();
    void healingWaters(FighterCharacter& character, FighterCharacter& target);
    void waterWhip(FighterCharacter& character, FighterCharacter& target);
    void waterVortex(FighterCharacter& character, FighterCharacter& target);
    // void iceBarrier(FighterCharacter& character, FighterCharacter& target);
    /// Display available water bending actions for a given character
    std::vector<std::string> getAvailableBendingActions(FighterCharacter& character) override; // Keep virtual and override here
};
#endif