#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 14a - Avatar: Terminal Elements - ECE 205 - Spring 2026
//
/// @file   GameManager.hpp
/// @brief  Top-level scene state machine for overworld flow:
///           prologue → region select → dungeon (via DungeonSystem) → loop
///           Reads all scene text/routing from story_config.json via GameData.
/// @author Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <set>
#include <vector>

#include "GameData.hpp"
#include "DungeonSystem.hpp"
#include "FighterCharacter.hpp"
#include "PlayerCharacter.hpp"

class GameManager {
public:
    GameManager();
    ~GameManager();

    /// Top-level entry point — call once from main()
    void run();

private:
    GameData*                      gameData;
    std::vector<FighterCharacter*> players;
    std::set<std::string>          resolvedRegions; // regions the party has cleared
    int                            gold;

    // ── Overworld scene handlers 
    // Each returns the key of the next scene.

    /// Displays text and a numbered options list, returns chosen option "next"
    std::string handleWorldSelect  (const nlohmann::json& scene);

    /// Displays dialogue text, returns scene["next"]
    std::string handleDialogue     (const nlohmann::json& scene);

    /// Builds the region menu filtered by resolved state, hands off to
    /// DungeonSystem, then returns the appropriate next scene key
    std::string handleRegionSelect (const nlohmann::json& scene);

    /// Evaluates the scene's condition string, returns true_next / false_next
    std::string handleCondition    (const nlohmann::json& scene);

    /// Displays a prompt with options, returns chosen option "next"
    std::string handlePrompt       (const nlohmann::json& scene);

    /// Runs the final boss dungeon, returns on_win / on_lose
    std::string handleFinalBattle  (const nlohmann::json& scene);

    // ── Player setup 
    void setupPlayers();
};

#endif // GAME_MANAGER_HPP
