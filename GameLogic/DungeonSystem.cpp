#include "DungeonSystem.hpp"
#include "../util/TextDisplay.hpp"
#include "../BattleManager/BattleManager.hpp"

DungeonSystem::DungeonSystem(const std::string& region, GameData* data, std::vector<FighterCharacter*>& party) 
    : regionId(region), gameData(data), playerParty(party) {}

int DungeonSystem::runDungeon() {
    enterDungeon();

    int choice = chooseFork1();

    if (choice == 0 || choice == 1) { // left or middle -> battle room
        if (!battleRoom()) return -1; // lost battle

        chooseFork2(); // both lead to boss

        return bossFight() ? 1 : -1;
    } else { // right -> camp room
        campRoom();

        return bossFight() ? 1 : -1;
    }
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

void DungeonSystem::enterDungeon() {
    util::printColor("\n[DUNGEON ENTRANCE] You enter the dungeon. The disturbance grows stronger deeper inside.", util::FG_YELLOW);
}

int DungeonSystem::chooseFork1() {
    util::printColor("\n[FORK] The tunnel splits into three paths.", util::FG_CYAN);
    util::printColor("1. Take the left path", util::FG_WHITE);
    util::printColor("2. Take the middle path", util::FG_WHITE);
    util::printColor("3. Take the right path", util::FG_WHITE);
    int choice = util::promptInt("Choose a path (1-3): ", 1, 3);
    return choice - 1; // 0,1,2
}

bool DungeonSystem::battleRoom() {
    FighterCharacter* minion = gameData->createMinionFromJSON(regionId);
    if (!minion) return false;

    util::printColor("\n[BATTLE ROOM] A " + minion->getName() + " blocks your path!", util::FG_RED);
    
    bool won = handleRoomBattle(minion);
    delete minion;
    return won;
}

void DungeonSystem::campRoom() {
    util::printColor("\n[CAMP] You find a quiet camp spot. Rest and prepare for the boss.", util::FG_CYAN);
    for(auto p : playerParty) {
        if(p->getHealth() > 0) p->setHealth(p->getHealth() + 30);
    }
}

int DungeonSystem::chooseFork2() {
    util::printColor("\n[FORK] Another fork appears, but something feels off...", util::FG_CYAN);
    util::printColor("1. Go left", util::FG_WHITE);
    util::printColor("2. Go right", util::FG_WHITE);
    int choice = util::promptInt("Choose a path (1-2): ", 1, 2);
    return choice - 1; // 0 or 1
}

bool DungeonSystem::bossFight() {
    FighterCharacter* boss = gameData->createBossFromJSON(regionId);
    if (!boss) return false;

    util::printColor("\n[BOSS ROOM] The " + boss->getName() + " appears!", util::FG_MAGENTA);
    
    bool won = handleBossBattle(boss);
    delete boss;
    return won;
}
