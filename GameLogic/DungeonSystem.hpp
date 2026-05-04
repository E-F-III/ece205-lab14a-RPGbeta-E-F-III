#ifndef DUNGEONSYSTEM_HPP
#define DUNGEONSYSTEM_HPP

#include <string>
#include <vector>
#include "GameData.hpp"
#include "../Characters/FighterCharacter.hpp"

class DungeonSystem {
private:
    std::string regionId;
    GameData::RegionData regionInfo;
    GameData* gameData;
    std::vector<FighterCharacter*>& playerParty;
    std::string currentScene;

    bool handleRoomCape();
    bool handleRoomBattle();
    bool handleBossBattle();

public:
    // Signature matches the .cpp exactly to fix "no declaration matches"
    DungeonSystem(const GameData::RegionData* region, GameData* gameData, std::vector<FighterCharacter*>& party);
    int runDungeon();
};

#endif
