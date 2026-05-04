#include "DungeonSystem.hpp"
#include "../util/TextDisplay.hpp"
#include "../BattleManager/BattleManager.hpp"

DungeonSystem::DungeonSystem(const std::string& region, GameData* data, std::vector<FighterCharacter*>& party) 
    : regionId(region), gameData(data), playerParty(party) {}

int DungeonSystem::runDungeon() {
    // 1. Create Minion
    FighterCharacter* minion = gameData->createMinionFromJSON(regionId);
    if (!minion) return -1;

    util::printColor("\n[ROOM 1] A " + minion->getName() + " blocks your path!", util::FG_RED);
    
    bool wonRoom1 = handleRoomBattle(minion);
    delete minion;

    // Check if player lost or died
    if (!wonRoom1) {
        return -1;
    }

    // 2. Rest Phase
    util::printColor("\n[CAMP] You find a moment of peace to recover.", util::FG_CYAN);
    for(auto p : playerParty) {
        if(p->getHealth() > 0) p->setHealth(p->getHealth() + 20);
    }

    // 3. Final Boss
    FighterCharacter* boss = gameData->createBossFromJSON(regionId);
    if (!boss) return 1; 

    util::printColor("\n[BOSS ROOM] The " + boss->getName() + " appears!", util::FG_MAGENTA);
    
    bool wonBoss = handleBossBattle(boss);
    delete boss;

    return wonBoss ? 1 : -1;
}

bool DungeonSystem::handleRoomBattle(FighterCharacter* enemy) {
    std::vector<FighterCharacter*> enemies = { enemy };
    BattleManager bm(playerParty, enemies);
    
    // BattleManager::runBattle() returns void, so we check health after
    bm.runBattle(); 
    
    // Check if any player is still alive
    for (auto* p : playerParty) {
        if (p->getHealth() > 0) return true;
    }
    return false;
}

bool DungeonSystem::handleBossBattle(FighterCharacter* boss) {
    std::vector<FighterCharacter*> enemies = { boss };
    BattleManager bm(playerParty, enemies);
    
    bm.runBattle();
    
    for (auto* p : playerParty) {
        if (p->getHealth() > 0) return true;
    }
    return false;
}
