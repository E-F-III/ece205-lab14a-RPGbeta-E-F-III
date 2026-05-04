#include "DungeonSystem.hpp"
#include "../util/TextDisplay.hpp"
#include "../BattleManager/BattleManager.hpp"

DungeonSystem::DungeonSystem(const GameData::RegionData* region, GameData* data, std::vector<FighterCharacter*>& party) 
    : regionId(region->id), gameData(data), playerParty(party) {}

int DungeonSystem::runDungeon() {
    Region region = GameData::findRegion(regionId, gameData->getRegions());
}

bool DungeonSystem::handleRoomBattle() {
    
    std::vector<FighterCharacter*> enemies;



    BattleManager bm(playerParty, enemies);
    
    // BattleManager::runBattle() returns void, so we check health after
    bm.runBattle(); 
    
    // Check if any player is still alive
    for (auto* p : playerParty) {
        if (p->getHealth() > 0) return true;
    }
    return false;
}

bool DungeonSystem::handleBossBattle() {
    
    BattleManager bm(playerParty, enemies);
    
    bm.runBattle();
    
    for (auto* p : playerParty) {
        if (p->getHealth() > 0) return true;
    }
    return false;
}
