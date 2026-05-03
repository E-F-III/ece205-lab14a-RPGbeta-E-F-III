#include "GameData.hpp"
#include <iostream>
#include <fstream>
#include "../util/TextDisplay.hpp"
#include "util/json.hpp"


using namespace std;
using namespace nlohmann;


GameData::GameData(const string& jsonFilename) {
    // Basic initialization to avoid unused parameter warning if JSON loading isn't fully implemented here
    (void)jsonFilename; 
    
    // Hardcoded fallback data for testing if JSON fails
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


    // FIX: Create local variables because NPC constructors take non-const references (std::string& and int&)
    string tempName = targetRegion->name;
    int codeFire = 2;
    int codeWater = 3;
    int codeEarth = 1;
    int codeAir = 0;


    if (regionId == "fire_nation")     return new NPCFireBender(tempName, codeFire);
    if (regionId == "water_tribe")     return new NPCWaterBender(tempName, codeWater);
    if (regionId == "earth_kingdom")  return new NPCEarthBender(tempName, codeEarth);
    if (regionId == "air_temple")      return new NPCAirBender(tempName, codeAir);
    return nullptr;
}


FighterCharacter* GameData::createBossFromJSON(const string& regionId) {
    const auto* targetRegion = GameData::findRegion(regionId, this->regionsList);
    if (!targetRegion) return nullptr;


    string tempName = targetRegion->name + " Overlord";
    int codeFire = 2;
    int codeWater = 3;
    int codeEarth = 1;
    int codeAir = 0;


    if (regionId == "fire_nation")     return new NPCFireBender(tempName, codeFire);
    if (regionId == "water_tribe")     return new NPCWaterBender(tempName, codeWater);
    if (regionId == "earth_kingdom")  return new NPCEarthBender(tempName, codeEarth);
    if (regionId == "air_temple")      return new NPCAirBender(tempName, codeAir);
    return nullptr;
}
