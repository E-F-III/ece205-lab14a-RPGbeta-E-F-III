#include "GameData.hpp"
#include <iostream>
#include <fstream>
#include "../util/TextDisplay.hpp"
#include "util/json.hpp"

using namespace std;
using namespace nlohmann;

GameData::GameData(const string& jsonFilename) {
    ifstream file(jsonFilename);
    if (!file.is_open()) {
        cerr << "ERROR: Could not open " << jsonFilename << "\n";
        exit(1);
    }

    json j;
    file >> j;
    file.close();

    // Load config
    config.starting_scene = j["config"]["starting_scene"];
    config.starting_gold = j["config"]["starting_gold"];
    config.home_region_locked_first = j["config"]["home_region_locked_first"];

    // Load regions
    for (const auto& region : j["regions"]) {
        RegionData rd;
        rd.id = region["id"];
        rd.name = region["name"];
        rd.hub_scene = region["hub_scene"];
        rd.win_scene = region["win_scene"];
        rd.minion_hp = region["minion_hp"];
        rd.boss_hp = region["boss_hp"];

        for (const auto& location : region["locations"].items()) {
            rd.locations[location.key()] = location.value();
        }
        regionsList.push_back(rd);
    }
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

const std::vector<GameData::RegionData>& GameData::getRegions() {
    return regionsList;
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
