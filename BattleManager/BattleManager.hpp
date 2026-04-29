#ifndef BATTLE_MANAGER_HPP
#define BATTLE_MANAGER_HPP

#include <vector>
#include <string>
#include "FighterCharacter.hpp"

class BattleManager {
private:
    // Member variables to hold our two teams
    std::vector<FighterCharacter*> players;
    std::vector<FighterCharacter*> enemies;

    // --- Private Helper Methods (Internal Logic) ---
    
    /**
     * @brief Checks if at least one member of the party has HP > 0
     */
    bool isPartyAlive(const std::vector<FighterCharacter*>& party);

    /**
     * @brief Prints the current health of all combatants to the console
     */
    void displayHealth();

    /**
     * @brief Randomly selects an alive target from a given party
     */
    FighterCharacter* getRandomAliveMember(std::vector<FighterCharacter*>& party);

    /**
     * @brief Handles the logic for a single character's turn
     * @param attacker The character currently acting
     * @param allies The team the attacker belongs to
     * @param targets The opposing team
     * @param isNPC True if the character is AI-controlled
     */
    void performTurn(FighterCharacter* attacker, 
                     std::vector<FighterCharacter*>& allies, 
                     std::vector<FighterCharacter*>& targets, 
                     bool isNPC);

public:
    /**
     * @brief Constructor that takes prepared vectors of players and enemies
     */
    BattleManager(std::vector<FighterCharacter*> p, std::vector<FighterCharacter*> e);

    /**
     * @brief Destructor
     */
    ~BattleManager();

    /**
     * @brief The main engine loop that runs until one side is defeated
     */
    void runBattle();
};

#endif