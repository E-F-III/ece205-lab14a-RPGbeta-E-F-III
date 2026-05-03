// University of Hawaii, College of Engineering
// Lab 14a - RPG Beta - Dungeon Logic Implementation
//
/// @file    DungeonSystem.cpp
/// @author  Menden Cannistra <mendenc@hawaii.edu>
/////////////////////////////////////////////////////////////////////////////////

#include "DungeonSystem.hpp"
#include "../BattleManager/BattleManager.hpp" 
#include "../util/TextDisplay.hpp" 

using namespace std;

// Constructor: Needs the player party to track HP changes across all rooms
DungeonSystem::DungeonSystem(const string& regionId, GameData* gd, vector<FighterCharacter*>& party)
    : currentRegionId(regionId), data(gd), playerParty(party) {}

int DungeonSystem::runDungeon() {
    util::printColor("\n=========================================\n", util::FG_YELLOW);
    util::printType("The journey into the " + currentRegionId + " Catacombs begins...\n", 50);
    util::printColor("=========================================\n", util::FG_YELLOW);

    // Step 1: Entrance Narrative (JSON Key: region.locations.dungeon -> scene_entrance)
    handleDungeonEntrance();

    // --- Start Combat Loop ---

    // Step 2: Room 1 - Minion Battle (JSON Keys: "minion", "scene_battle")
    FighterCharacter* minion = data->createMinionFromJSON(currentRegionId);
    if (!minion) return -1; // Failed to setup battle
    
    bool wonRoom1 = handleRoomBattle(minion); 
    delete minion;

    // Check for death after Room 1. If !wonRoom1, the dungeon ends here.
    if (playerParty[0]->getHealth() <= 0) return -1; 

    // Step 3: Camp Room (JSON Key: "scene_camp_room" or similar rest spot)
    handleCampRest(); // Rest and prepare for boss

    // Step 4: Final Boss Battle (JSON Keys: "boss", "scene_boss_fight")
    FighterCharacter* boss = data->createBossFromJSON(currentRegionId);
    if (!boss) return -1;
    
    bool wonBoss = handleBossBattle(boss); 
    delete boss;

    util::printColor("\n[SYSTEM] The ancient disturbance is neutralized. Balance returns!", util::FG_GREEN);
    return 1; // Success
}


void DungeonSystem::handleDungeonEntrance() {
    // Simulate the entrance scene text output from JSON:
    const std::string entryText = "You enter the ruins of the " + currentRegionId + ". The air is thick with dark magic...";
    util::printColor(entryText, util::FG_CYAN); 

    // Add a pause here to simulate traversing to the first battle room.
}


bool DungeonSystem::handleRoomBattle(FighterCharacter* enemy) {
    if (!enemy) return true; // If no enemy, assume success and continue.

    util::printColor("\n--- BATTLE BEGIN: Encountering Minion ---\n", util::FG_RED); 
    
    // Create a dedicated BattleManager instance for this fight.
    BattleManager battle(playerParty, {enemy});
    battle.runBattle(); // This runs the existing combat loop logic in BattleManager.cpp

    // Determine victory condition based on party status
    bool won = true; 
    for (auto p : playerParty) {
        if (p->getHealth() <= 0) {
            won = false;
            break;
        }
    }
    return won;
}

void DungeonSystem::handleCampRest() {
    // Use the JSON rule: restore a fixed amount of health.
    const int RESTORE_AMOUNT = 30;
    util::printType("You find a secluded camp and recover energy...", 50);
    for (auto p : playerParty) {
        // Apply rest logic to every character in the party
        p->setHealth(min((double)100, (double)p->getHealth() + RESTORE_AMOUNT));
    }
}

bool DungeonSystem::handleBossBattle(FighterCharacter* boss) {
    if (!boss) return true; 

    util::printColor("\n--- BATTLE BEGIN: The Final Boss Encounter ---\n", util::FG_RED); 

    // Logic remains the same as room battle, but with the boss enemy.
    BattleManager battle(playerParty, {boss});
    battle.runBattle();

    bool won = true; // Re-check party status after combat
    for (auto p : playerParty) {
        if (p->getHealth() <= 0) {
            won = false;
            break;
        }
    }
    return won;
}
