#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 14a - Avatar: Terminal Elements - ECE 205 - Spring 2026
//
/// @file   GameData.hpp
/// @brief  Loads and owns story_config.json. Provides region/scene/enemy
///         data for GameManager and DungeonSystem.
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
    // ── Region data 
    struct RegionData {
        std::string id;
        std::string name;
        std::string disturbance;
        std::string dungeon_name;
        std::string hub_scene;       // scene key for the hub
        std::string win_scene;       // scene key shown on region clear
        std::string minion_name;
        std::string boss_name;
        int         minion_hp = 0;
        int         boss_hp   = 0;
        std::map<std::string, std::string> locations; // "dungeon" → scene key
    };

    // ── Constructor / Destructor 
    explicit GameData(const std::string& jsonFilename);
    ~GameData();

    // ── Region accessors 
    const std::vector<RegionData>&  getRegions()       const;
    const std::string               getStartingScene() const;
    int                             getStartingGold()  const;
    int                             getStartingHealth() const;
    int                             getMaxHealth()      const;

    /// Returns pointer into regionsList (nullptr if not found)
    static const RegionData* findRegion(const std::string& regionId,
                                        const std::vector<RegionData>& list);

    
    const nlohmann::json& getScene(const std::string& sceneKey) const;

    // ── Enemy factory
    FighterCharacter* createEnemyById(const std::string& enemyId) const;

    // ── 
    FighterCharacter* createMinionFromJSON(const std::string& regionId);
    FighterCharacter* createBossFromJSON  (const std::string& regionId);

private:
    struct ConfigData {
        std::string starting_scene;
        int         starting_gold            = 50;
        int         starting_health          = 100;
        int         max_health               = 100;
        bool        home_region_locked_first = false;
    };

    ConfigData              config;
    std::vector<RegionData> regionsList;
    nlohmann::json          jsonData;       // full parsed JSON

    // Flat map: enemy id → json object (built once in constructor)
    std::map<std::string, nlohmann::json> enemyById;

    void buildEnemyIndex();
};

#endif // GAMEDATA_HPP
