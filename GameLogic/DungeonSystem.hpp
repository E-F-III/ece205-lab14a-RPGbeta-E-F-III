#ifndef DUNGEONSYSTEM_HPP
#define DUNGEONSYSTEM_HPP

#include <string>
#include <vector>
#include "GameData.hpp"
#include "../Characters/FighterCharacter.hpp"

class DungeonSystem {
private:
    std::string regionId;
    GameData* gameData;
    std::vector<FighterCharacter*>& playerParty;

    bool handleRoomBattle(FighterCharacter* enemy);
    bool handleBossBattle(FighterCharacter* boss);

    void enterDungeon();
    int chooseFork1();
    void battleRoom();
    void campRoom();
    int chooseFork2();
    void bossFight();

public:
    // Signature matches the .cpp exactly to fix "no declaration matches"
    DungeonSystem(const std::string& regionId, GameData* gameData, std::vector<FighterCharacter*>& party);
    int runDungeon();
};

#endif
