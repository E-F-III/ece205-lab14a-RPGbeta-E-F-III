// University of Hawaii, College of Engineering
// Lab 14a - RPG Beta - Data Layer Implementation (FINAL)
//
/// @file    GameData.cpp
/// @author  Menden Cannistra <mendenc@hawaii.edu>
/////////////////////////////////////////////////////////////////////////////////

#include "GameData.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "../util/TextDisplay.hpp" 
#include "util/json.hpp"

using namespace std;
using namespace nlohmann;

// ========================================================================
// GLOBAL HELPER FUNCTION DEFINITION (Must be defined outside the class)
// This function must exist *before* any methods that use it are defined.
const RegionData* findRegion(const string& regionId, const std::vector<RegionData>& regionsList) {
    for (const auto& reg : regionsList) {
        if (reg.id == regionId) return &reg;
    }
    return nullptr;
}

// Constructor: Initializing the data layer from JSON
GameData::GameData(const string& jsonFilename) {
    util::printColor("[DATA LOADER] Initializing from " + jsonFilename + "...", util::FG_CYAN); 

    try {
        ifstream file(jsonFilename);
        if (!file.is_open()) {
            throw runtime_error("Critical Error: Could not find JSON file.");
        }

        json j;
        file >> j;

        // 1. Parse Config Section (Key: "config")
        auto configRoot = j["config"];
        this->config.starting_scene = configRoot.value("starting_scene", "");
        this->config.starting_gold = configRoot.value("starting_gold", 50);
        auto rules = configRoot["rules"];
        this->config.home_region_locked_first = rules.value("home_region_locked_first", true);

        // 2. Parse Regions (Key: "regions" array)
        for (auto& reg : j["regions"]) {
            RegionData rd;
            rd.id = reg["id"]; 
            rd.name = reg["name"];
            
            // Map mandatory JSON keys for scene IDs
            rd.hub_scene = reg["hub_scene"]; 
            rd.win_scene = reg["win_scene"];
            
            for (auto& [key, val] : reg["locations"].items()) {
                rd.locations[key] = val;
            }

            // Extract specific HP values for easy lookup using default values
            if (reg.count("minion")) rd.minion_hp = reg["minion"].value("hp", 0);
            else rd.minion_hp = 0;

            if (reg.count("boss")) rd.boss_hp = reg["boss"].value("hp", 0);
            else rd.boss_hp = 0;

            this->regionsList.push_back(rd);
        }

        file.close();

    } catch (const exception& e) {
        util::printColor("Data Load Error: " + string(e.what()), util::FG_RED); 
    }
}


GameData::~GameData() = default; // Explicit definition of destructor

// Getter implementations using the class members
const std::string GameData::getStartingScene() const { return config.starting_scene; }

// Factory: Create minion object using stored HP and appropriate NPC class.
FighterCharacter* GameData::createMinionFromJSON(const string& regionId) {
    util::printColor("\n[FACTORY] Attempting to create minion for region: " + regionId, util::FG_YELLOW);

    // Use the helper function defined globally above!
    const auto* targetRegion = findRegion(regionId, this->regionsList);

    if (!targetRegion) {
        util::printColor("ERROR: Region ID not found!", util::FG_RED);
        return nullptr;
    }
    
    // Map region ID to correct NPC class based on your existing classes (using the name from JSON)
    // NOTE: This block MUST be completed by you using all 4 regions and their respective boss/minion types.
    if (regionId == "fire_nation") {
        return new NPCFireBender(targetRegion->name, 2); 
    } else if (regionId == "water_tribe") {
        return new NPCWaterBender(targetRegion->name, 3); 
    } else if (regionId == "earth_kingdom") {
        return new NPCEarthBender(targetRegion->name, 1); 
    } else if (regionId == "air_temple") {
        return new NPCAirBender(targetRegion->name, 0);
    } else {
        return nullptr;
    }
}

// Factory: Create boss object using stored HP and appropriate NPC class.
FighterCharacter* GameData::createBossFromJSON(const std::string& regionId) {
    util::printColor("\n[FACTORY] Attempting to create Boss for region: " + regionId, util::FG_YELLOW);

    // Use the helper function defined globally above!
    const auto* targetRegion = findRegion(regionId, this->regionsList);

    if (!targetRegion) {
        return nullptr;
    }
    
    // Repeat the pattern for bosses:
    if (regionId == "fire_nation") {
        return new NPCFireBender(targetRegion->name, 2); 
    } else if (regionId == "water_tribe") {
        return new NPCWaterBender(targetRegion->name, 3);
    } else if (regionId == "earth_kingdom") {
        return new NPCEarthBender(targetRegion->name, 1);
    } else if (regionId == "air_temple") {
        return new NPCAirBender(targetRegion->name, 0);
    } else {
        return nullptr;
    }
}

