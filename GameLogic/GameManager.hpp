#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 14a - Avatar: Terminal Elements - ECE 205 - Spring 2026
//
/// @file   GameManager.hpp
/// @brief  Drives the top-level game flow:
///           1. Player setup
///           2. Region select
///           3. Dungeon run (via DungeonSystem)
/// @author Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>

#include "json.hpp"
#include "GameData.hpp"
#include "DungeonSystem.hpp"
#include "FighterCharacter.hpp"
#include "PlayerCharacter.hpp"

class GameManager {
public:
    GameManager();
    ~GameManager();

    /// Top-level entry point
    void run();

private:
    GameData*                      gameData;
    nlohmann::json                 storyData;
    std::vector<FighterCharacter*> players;

    void setupPlayers();
    void selectRegionAndRunDungeon();

    // I/O helpers
    int  promptInt (const std::string& prompt, int lo, int hi) const;
    void waitEnter () const;
};

#endif // GAME_MANAGER_HPP
