// University of Hawaii, College of Engineering
// Lab 14a - RPG Beta - Data Layer Header
//
/// @file    GameData.hpp
/// @author  Menden Cannistra <mendenc@hawaii.edu>
/////////////////////////////////////////////////////////////////////////////////

#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include <vector>
#include <string>
#include <map>
#include "FighterCharacter.hpp" 
// We need to include all NPC headers here because the factory methods use them!
#include "../Characters/NPC/NPCAirBender.hpp" 
#include "../Characters/NPC/NPCEarthBender.hpp"
#include "../Characters/NPC/NPCFireBender.hpp"
#include "../Characters/NPC/NPCWaterBender.hpp"

// We use a helper function declaration for findRegion here to solve the scope error.
class GameData; // Forward declaration needed because of mutual dependency

enum class SceneType {
    world_select, dialogue, region_select, death, prompt, final_battle, 
    ending, hub, training, store, inn, dungeon_room, battle, boss_battle, rest
};

class GameData {
public:
    GameData(const std::string& jsonFilename);
    ~GameData(); // Explicitly define destructor
    
    // Config & Factory Helpers
    const std::string getStartingScene() const;
    FighterCharacter* createMinionFromJSON(const std::string& regionId);
    FighterCharacter* createBossFromJSON(const std::string& regionId);

private:
    struct SceneData {
        std::string id;
        SceneType type;
        std::string text;
        std::map<std::string, std::string> options; 
        std::string next;
    };

    struct ConfigData {
        std::string starting_scene;
        int starting_gold;
        bool home_region_locked_first;
    };

    // *** FIX: Added missing members (hub_scene, win_scene) ***
    struct RegionData {
        std::string id;
        std::string name;
        std::map<std::string, std::string> locations;
        std::string hub_scene; // JSON key added
        std::string win_scene; // JSON key added
        int minion_hp = 0;     // Default initialization
        int boss_hp = 0;       // Default initialization
    };

    ConfigData config;
    std::map<std::string, SceneData> sceneMap;
    std::vector<RegionData> regionsList;
};

#endif // GAMEDATA_HPP
