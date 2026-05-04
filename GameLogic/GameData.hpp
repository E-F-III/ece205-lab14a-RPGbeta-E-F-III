#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include <string>
#include <map>
#include <vector>
#include "FighterCharacter.hpp"
#include "../Characters/NPC/NPCAirBender.hpp"
#include "../Characters/NPC/NPCEarthBender.hpp"
#include "../Characters/NPC/NPCFireBender.hpp"
#include "../Characters/NPC/NPCWaterBender.hpp"

class GameData {
public:
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

    // Static helper to find region by ID
    static const RegionData* findRegion(const std::string& regionId, const std::vector<RegionData>& regionsList);
    const std::vector<RegionData>& getRegions();

private:
    struct ConfigData {
        std::string starting_scene;
        int starting_gold;
        bool home_region_locked_first;
    };

    ConfigData config;
    std::vector<RegionData> regionsList;

};
#endif
