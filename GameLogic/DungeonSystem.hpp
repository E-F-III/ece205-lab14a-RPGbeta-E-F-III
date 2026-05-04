#ifndef DUNGEONSYSTEM_HPP
#define DUNGEONSYSTEM_HPP

///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 14a - Avatar: Terminal Elements - ECE 205 - Spring 2026
//
/// @file   DungeonSystem.hpp
/// @brief  Scene-driven dungeon runner. Starts from the region's "dungeon"
///         location key and follows next/on_win/on_lose links through the
///         scenes map until reaching a win_dialogue or die_restart scene.
/// @author Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include "GameData.hpp"
#include "../Characters/FighterCharacter.hpp"

class DungeonSystem {
public:
    /// @param region   
    /// @param gameData 
    /// @param party    
    DungeonSystem(const GameData::RegionData*    region,
                  GameData*                      gameData,
                  std::vector<FighterCharacter*>& party);

    
    /// @return 1 on region cleared, 0 on party wipe
    int runDungeon();

private:
    const GameData::RegionData*     regionInfo;
    GameData*                       gameData;
    std::vector<FighterCharacter*>& playerParty;

    // ── Scene handlers 

    std::string handleDialogue   (const nlohmann::json& scene);
    std::string handleChoice     (const nlohmann::json& scene);
    std::string handleDungeonRoom(const nlohmann::json& scene);
    std::string handleRest       (const nlohmann::json& scene);
    std::string handleBattle     (const nlohmann::json& scene);
    std::string handleBossBattle (const nlohmann::json& scene);

    // ── Helpers 
    bool anyPlayerAlive() const;
    void restorePartyHealth(int amount);
};

#endif // DUNGEONSYSTEM_HPP
