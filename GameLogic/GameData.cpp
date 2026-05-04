///////////////////////////////////////////////////////////////////////////////
// University of Hawaii, College of Engineering
// Lab 14a - Avatar: Terminal Elements - ECE 205 - Spring 2026
//
/// @file   GameData.cpp
/// @author Edward Felipe III <efelipe3@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "GameData.hpp"
#include "TextDisplay.hpp"
#include "NPCAirBender.hpp"
#include "NPCEarthBender.hpp"
#include "NPCFireBender.hpp"
#include "NPCWaterBender.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace nlohmann;

GameData::GameData(const string& jsonFilename) {
    ifstream file(jsonFilename);
    if (!file.is_open()) {
        cerr << "ERROR: Could not open " << jsonFilename << "\n";
        exit(1);
    }

    file >> jsonData;   // store the full JSON for use in factory methods
    file.close();

    // ── Config
    config.starting_scene = jsonData["config"]["starting_scene"].get<string>();
    config.starting_gold  = jsonData["config"]["starting_gold"].get<int>();

    config.home_region_locked_first =
        jsonData["config"]["rules"]["home_region_locked_first"].get<bool>();

    // ── Regions
    for (const auto& region : jsonData["regions"]) {
        RegionData rd;
        rd.id        = region["id"].get<string>();
        rd.name      = region["name"].get<string>();
        rd.hub_scene = region["hub_scene"].get<string>();
        rd.win_scene = region["win_scene"].get<string>();

        rd.minion_name = region["minion"]["name"].get<string>();
        rd.minion_hp   = region["minion"]["hp"].get<int>();
        rd.boss_name   = region["boss"]["name"].get<string>();
        rd.boss_hp     = region["boss"]["hp"].get<int>();

        for (const auto& loc : region["locations"].items()) {
            rd.locations[loc.key()] = loc.value().get<string>();
        }

        regionsList.push_back(rd);
    }
}

GameData::~GameData() = default;

const string GameData::getStartingScene() const {
    return config.starting_scene;
}

const vector<GameData::RegionData>& GameData::getRegions() const {
    return regionsList;
}

const GameData::RegionData* GameData::findRegion(const string& regionId,
                                                  const vector<RegionData>& list) {
    for (const auto& reg : list) {
        if (reg.id == regionId) return &reg;
    }
    return nullptr;
}

FighterCharacter* GameData::createMinionFromJSON(const string& regionId) {
    for (const auto& region : jsonData["regions"]) {
        if (region["id"].get<string>() != regionId) continue;

        string name = region["minion"]["name"].get<string>();
        int    hp   = region["minion"]["hp"].get<int>();

        int code = 0;
        if      (regionId == "fire_nation")   code = 2;
        else if (regionId == "water_tribe")   code = 3;
        else if (regionId == "earth_kingdom") code = 1;
        else if (regionId == "air_temple")    code = 0;

        FighterCharacter* npc = nullptr;
        if (regionId == "fire_nation")   npc = new NPCFireBender (name, code);
        if (regionId == "water_tribe")   npc = new NPCWaterBender(name, code);
        if (regionId == "earth_kingdom") npc = new NPCEarthBender(name, code);
        if (regionId == "air_temple")    npc = new NPCAirBender  (name, code);

        if (npc) npc->setHealth(hp);
        return npc;
    }
    return nullptr;
}

FighterCharacter* GameData::createBossFromJSON(const string& regionId) {
    for (const auto& region : jsonData["regions"]) {
        if (region["id"].get<string>() != regionId) continue;

        string name = region["boss"]["name"].get<string>();
        int    hp   = region["boss"]["hp"].get<int>();

        FighterCharacter* npc = nullptr;

        // needed for racecode reference. 
        // race not needed for our game. will remove in future.
        int code = 0;
        if      (regionId == "fire_nation")   code = 2;
        else if (regionId == "water_tribe")   code = 3;
        else if (regionId == "earth_kingdom") code = 1;
        else if (regionId == "air_temple")    code = 0;

        if (regionId == "fire_nation")   npc = new NPCFireBender (name, code);
        if (regionId == "water_tribe")   npc = new NPCWaterBender(name, code);
        if (regionId == "earth_kingdom") npc = new NPCEarthBender(name, code);
        if (regionId == "air_temple")    npc = new NPCAirBender  (name, code);

        if (npc) npc->setHealth(hp);
        return npc;
    }
    return nullptr;
}