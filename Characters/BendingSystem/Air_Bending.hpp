///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    Air_Bending.hpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
///
/// AirBender is a derived class of BendingSystem. AirBenders use air manipulation to fight enemies and protect allies.
///////////////////////////////////////////////////////////////////////////////
#ifndef AIR_BENDING_HPP
#define AIR_BENDING_HPP
#include "Bending_System.hpp"
/// AirBending: manages air bending abilities for AirBender characters
class AirBending : public BendingSystem { // Base class is BendingSystem
public:
    /// Constructor: initializes the air bending system
    AirBending();
    void airSlice(FighterCharacter& character,FighterCharacter& target);
    void airBlast(FighterCharacter& character, FighterCharacter& target);
    void tornado(FighterCharacter& character, FighterCharacter& target);
    // void airShield(FighterCharacter& character,FighterCharacter& target);
    // void flight(FighterCharacter& character);
    /// Display available air bending actions for a given character
    std::vector<std::string> getAvailableBendingActions(FighterCharacter& character) override; // Keep virtual and override here
};
#endif
