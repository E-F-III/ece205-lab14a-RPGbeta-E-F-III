#include "GameData.hpp"
#include <iostream>
#include <fstream>
#include "../util/TextDisplay.hpp"
#include "util/json.hpp"

using namespace std;
using namespace nlohmann;

GameData::GameData(const string& jsonFilename) {
    // Basic initialization
    (void)jsonFilename; 
    
    // Hardcoded fallback regions so the game works even without the JSON file
    RegionData fire; fire.id = "fire_nation"; fire.name = "Fire Nation Outpost";
    regionsList.push_back(fire);
    RegionData water; water.id = "water_tribe"; water.name = "Northern Water Tribe";
    regionsList.push_back(water);
    RegionData earth; earth.id = "earth_kingdom"; earth.name = "Ba Sing Se Walls";
    regionsList.push_back(earth);
    RegionData air; air.id = "air_temple"; air.name = "Southern Air Temple";
    regionsList.push_back(air);
    
    config.starting_scene = "intro";
}

GameData::~GameData() = default;

const std::string GameData::getStartingScene() const {
    return config.starting_scene;
}

const GameData::RegionData* GameData::findRegion(const string& regionId, const std::vector<RegionData>& regionsList) {
    for (const auto& reg : regionsList) {
        if (reg.id == regionId) return &reg;
    }
    return nullptr;
}

FighterCharacter* GameData::createMinionFromJSON(const string& regionId) {
    const auto* targetRegion = GameData::findRegion(regionId, this->regionsList);
    if (!targetRegion) return nullptr;

    // FIX: We create modifiable variables to pass into constructors that use &
    string name = targetRegion->name;
    int code_fire = 2; int code_water = 3; int code_earth = 1; int code_air = 0;

    if (regionId == "fire_nation")    return new NPCFireBender(name, code_fire);
    if (regionId == "water_tribe")    return new NPCWaterBender(name, code_water);
    if (regionId == "earth_kingdom")  return new NPCEarthBender(name, code_earth);
    if (regionId == "air_temple")     return new NPCAirBender(name, code_air);
    return nullptr;
}

FighterCharacter* GameData::createBossFromJSON(const string& regionId) {
    const auto* targetRegion = GameData::findRegion(regionId, this->regionsList);
    if (!targetRegion) return nullptr;

    string name = targetRegion->name + " (BOSS)";
    int code_fire = 2; int code_water = 3; int code_earth = 1; int code_air = 0;

    if (regionId == "fire_nation")    return new NPCFireBender(name, code_fire);
    if (regionId == "water_tribe")    return new NPCWaterBender(name, code_water);
    if (regionId == "earth_kingdom")  return new NPCEarthBender(name, code_earth);
    if (regionId == "air_temple")     return new NPCAirBender(name, code_air);
    return nullptr;
}
