#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include <vector>
#include <string>
#include <map>
#include "FighterCharacter.hpp"
#include "../Characters/NPC/NPCAirBender.hpp"
#include "../Characters/NPC/NPCEarthBender.hpp"
#include "../Characters/NPC/NPCFireBender.hpp"
#include "../Characters/NPC/NPCWaterBender.hpp"

class GameData {
public:
    // FIX: Moved RegionData to public so it can be used as a return type
    struct RegionData {
        std::string id;
        std::string name;
        std::map<std::string, std::string> locations;
        std::string hub_scene;
        std::string win_scene;
        int minion_hp = 0;
        int boss_hp = 0;
    };

    GameData(const std::string& jsonFilename);
    ~GameData();

    const std::string getStartingScene() const;
    FighterCharacter* createMinionFromJSON(const std::string& regionId);
    FighterCharacter* createBossFromJSON(const std::string& regionId);

    // FIX: Added static declaration for the helper function
    static const RegionData* findRegion(const std::string& regionId, const std::vector<RegionData>& regionsList);

private:
    struct SceneData {
        std::string id;
        // SceneType type; // Assuming SceneType is defined elsewhere as in your snippet
        std::string text;
        std::map<std::string, std::string> options;
        std::string next;
    };

    struct ConfigData {
        std::string starting_scene;
        int starting_gold;
        bool home_region_locked_first;
    };

    ConfigData config;
    std::vector<RegionData> regionsList;
};

#endif
