///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13b - Game Character Class Part III (Polymorphism) - ECE 205 - Spring 2026
//
/// @file    EarthBender.hpp
/// @author  Edward Felipe III <efelipe3@hawaii.edu>
/// EarthBender is a derived class of PlayerCharacter.
/// EarthBenders use earth manipulation to fight enemies and protect allies.
/////////////////////////////////////////////////////////////////////////////////

#ifndef EARTHBENDER_HPP
#define EARTHBENDER_HPP
#include "PlayerCharacter.hpp"
#include "Earth_Bending.hpp" // CORRECT INCLUDE PATH
#include <string>

/// EarthBender: a profession derived from PlayerCharacter that specializes in earth manipulation
class EarthBender : public PlayerCharacter {
    private:
        // Pointer to EarthBending system for performing earth bending actions
        EarthBending* earthBendingSystem;
        
    public:
        /// Constructor:
        explicit EarthBender(std::string& characterName, int& raceCode, bool demoMode);
        // Destructor: Essential cleanup when using raw pointers
        ~EarthBender();
        
        /// use bending system to perform an earth bending action (REMOVED 'override' KEYWORD)
        virtual void performAction(FighterCharacter& target) override;
        
        /// Print EarthBender-specific stats in addition to base stats
        void printStats();
        
        /// EarthBender-specific greeting
        void greet() const override;
};
#endif //EARTHBENDER_HPP
