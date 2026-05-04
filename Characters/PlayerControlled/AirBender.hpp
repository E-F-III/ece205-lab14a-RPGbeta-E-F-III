/////////////////////////////////////////////////////////////////////////////////
#ifndef AIRBENDER_HPP
#define AIRBENDER_HPP
#include "PlayerCharacter.hpp"
#include "Air_Bending.hpp" // CORRECT INCLUDE PATH
#include <string>
/// AirBender: a profession derived from PlayerCharacter that specializes in air manipulation
class AirBender : public PlayerCharacter {
    private:
        // Pointer to AirBending system for performing air bending actions
        AirBending* airBendingSystem;
        
    public:
        /// Constructor:
        explicit AirBender(std::string& characterName, int& raceCode, bool demoMode);
        // Destructor: Essential cleanup when using raw pointers
        ~AirBender();
        
        /// use bending system to perform an air bending action (REMOVED 'override' KEYWORD)
        virtual void performAction(FighterCharacter& target);
        
        /// Print AirBender-specific stats in addition to base stats
        void printStats();
        
        /// AirBender-specific greeting
        void greet() const override;
};
#endif //AIRBENDER_HPP
