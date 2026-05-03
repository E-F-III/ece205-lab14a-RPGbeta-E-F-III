// University of Hawaii, College of Engineering
// Lab 14a - RPG Beta - Dungeon Logic Header
//
/// @file    DungeonSystem.hpp
/// @author  Menden Cannistra <mendenc@hawaii.edu>
/////////////////////////////////////////////////////////////////////////////////

#ifndef DUNGEON_SYSTEM_HPP
#define DUNGEON_SYSTEM_HPP

#include <string>
#include <vector>
#include "FighterCharacter.hpp"
#include "GameData.hpp"

class DungeonSystem {
public:
    // Constructor takes the party by reference to track health across rooms
    DungeonSystem(const std::string& regionId, GameData* gameData, std::vector<FighterCharacter*>& party);

    int runDungeon();

private:
    std::string currentRegionId;
    GameData* data;
    std::vector<FighterCharacter*>& playerParty;

    void handleDungeonEntrance();
    bool handleRoomBattle(FighterCharacter* enemy);
    void handleCampRest();
    bool handleBossBattle(FighterCharacter* boss);
};

#endif // DUNGEON_SYSTEM_HPP
