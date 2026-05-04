///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    WaterBender.hpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
/// WaterBender is a derived class of PlayerCharacter. WaterBenders use water manipulation to fight enemies and protect allies.
///////////////////////////////////////////////////////////////////////////////

#ifndef WATERBENDER_HPP
#define WATERBENDER_HPP
#include "PlayerCharacter.hpp"
#include "Water_Bending.hpp" // CORRECT INCLUDE PATH
#include <string>

/// WaterBender: a profession derived from PlayerCharacter that specializes in water manipulation
class WaterBender : public PlayerCharacter {
    private:
        // Pointer to WaterBending system for performing water bending actions
        WaterBending* waterBendingSystem; 
        
    public:
        /// Constructor:
        explicit WaterBender(std::string& characterName, int& raceCode, bool demoMode);
        // Destructor: Essential cleanup when using raw pointers
        ~WaterBender();
        
        /// use bending system to perform a water bending action
        virtual void performAction(FighterCharacter& target);
        
        /// Print WaterBender-specific stats in addition to base stats
        void printStats();
        
        /// WaterBender-specific greeting
        void greet() const override;
};
#endif //WATERBENDER_HPP
