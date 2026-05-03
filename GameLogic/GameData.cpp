#include "GameData.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "../util/TextDisplay.hpp"
#include "util/json.hpp"

using namespace std;
using namespace nlohmann;

GameData::GameData(const string& jsonFilename) {
    // ... (Your existing constructor code remains the same) ...
}

GameData::~GameData() = default;

const std::string GameData::getStartingScene() const {
    return config.starting_scene;
}

// FIX: Added GameData:: scope and removed local static keyword
const GameData::RegionData* GameData::findRegion(const string& regionId, const std::vector<RegionData>& regionsList) {
    for (const auto& reg : regionsList) {
        if (reg.id == regionId) return &reg;
    }
    return nullptr;
}

FighterCharacter* GameData::createMinionFromJSON(const string& regionId) {
    util::printColor("\n[FACTORY] Creating minion for: " + regionId, util::FG_YELLOW);
    
    // FIX: Called via class scope
    const auto* targetRegion = GameData::findRegion(regionId, this->regionsList);
    
    if (!targetRegion) {
        util::printColor("ERROR: Region ID not found!", util::FG_RED);
        return nullptr;
    }

    if (regionId == "fire_nation") return new NPCFireBender(targetRegion->name, 2);
    if (regionId == "water_tribe") return new NPCWaterBender(targetRegion->name, 3);
    if (regionId == "earth_kingdom") return new NPCEarthBender(targetRegion->name, 1);
    if (regionId == "air_temple") return new NPCAirBender(targetRegion->name, 0);
    return nullptr;
}

FighterCharacter* GameData::createBossFromJSON(const string& regionId) {
    util::printColor("\n[FACTORY] Creating Boss for: " + regionId, util::FG_YELLOW);
    
    const auto* targetRegion = GameData::findRegion(regionId, this->regionsList);
    if (!targetRegion) return nullptr;

    if (regionId == "fire_nation") return new NPCFireBender(targetRegion->name, 2);
    if (regionId == "water_tribe") return new NPCWaterBender(targetRegion->name, 3);
    if (regionId == "earth_kingdom") return new NPCEarthBender(targetRegion->name, 1);
    if (regionId == "air_temple") return new NPCAirBender(targetRegion->name, 0);
    return nullptr;
}
