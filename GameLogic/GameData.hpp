#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 14a - Avatar: Terminal Elements - ECE 205 - Spring 2026
//
/// @file   GameData.hpp
/// @brief  Loads and owns the story JSON. Provides region data and enemy
///         factories for DungeonSystem and GameManager.
/// @author Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include <vector>

#include "json.hpp"
#include "../Characters/FighterCharacter.hpp"
#include "../Characters/NPC/NPCAirBender.hpp"
#include "../Characters/NPC/NPCEarthBender.hpp"
#include "../Characters/NPC/NPCFireBender.hpp"
#include "../Characters/NPC/NPCWaterBender.hpp"

class GameData {
public:
    // ── Public data structures ────────────────────────────────────────────────
    struct RegionData {
        std::string id;
        std::string name;
        std::string hub_scene;
        std::string win_scene;
        std::string minion_name;
        std::string boss_name;
        int         minion_hp = 0;
        int         boss_hp   = 0;
        std::map<std::string, std::string> locations;
    };

    // ── Constructor / Destructor ──────────────────────────────────────────────
    GameData(const std::string& jsonFilename);
    ~GameData();

    // ── Accessors ─────────────────────────────────────────────────────────────
    const std::string                  getStartingScene() const;
    const std::vector<RegionData>&     getRegions()       const;

    // ── Enemy factories ───────────────────────────────────────────────────────
    FighterCharacter* createMinionFromJSON(const std::string& regionId);
    FighterCharacter* createBossFromJSON  (const std::string& regionId);

    // ── Static helper ─────────────────────────────────────────────────────────
    static const RegionData* findRegion(const std::string& regionId,
                                        const std::vector<RegionData>& list);

private:
    struct ConfigData {
        std::string starting_scene;
        int         starting_gold             = 50;
        bool        home_region_locked_first  = false;
    };

    ConfigData              config;
    std::vector<RegionData> regionsList;
    nlohmann::json          jsonData;   // full parsed JSON kept for factories
};

#endif // GAMEDATA_HPP