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


// Constructor
GameData::GameData(const string& jsonFilename) {
    ifstream file(jsonFilename);
    if (!file.is_open()) {
        cerr << "ERROR: Could not open " << jsonFilename << "\n";
        exit(1);
    }
    file >> jsonData;
    file.close();

    // ── Config
    config.starting_scene  = jsonData["config"]["starting_scene"].get<string>();
    config.starting_gold   = jsonData["config"]["starting_gold"].get<int>();
    config.starting_health = jsonData["config"]["starting_health"].get<int>();
    config.max_health      = jsonData["config"]["max_health"].get<int>();
    config.home_region_locked_first =
        jsonData["config"]["rules"]["home_region_locked_first"].get<bool>();

    // ── Regions
    for (const auto& region : jsonData["regions"]) {
        RegionData rd;
        rd.id           = region["id"].get<string>();
        rd.name         = region["name"].get<string>();
        rd.disturbance  = region["disturbance"].get<string>();
        rd.dungeon_name = region["dungeon_name"].get<string>();
        rd.hub_scene    = region["hub_scene"].get<string>();
        rd.win_scene    = region["win_scene"].get<string>();

        rd.minion_name  = region["minion"]["name"].get<string>();
        rd.minion_hp    = region["minion"]["hp"].get<int>();
        rd.boss_name    = region["boss"]["name"].get<string>();
        rd.boss_hp      = region["boss"]["hp"].get<int>();

        for (const auto& loc : region["locations"].items()) {
            rd.locations[loc.key()] = loc.value().get<string>();
        }

        regionsList.push_back(rd);
    }

    // ── Build flat enemy index from the JSON enemies table
    buildEnemyIndex();
}

GameData::~GameData() = default;


// buildEnemyIndex
void GameData::buildEnemyIndex() {
    const auto& enemies = jsonData["enemies"];
    for (const auto& entry : enemies.items()) {
        const auto& val = entry.value();

        if (val.is_object() && val.contains("id")) {
            // top-level minion entry
            string id = val["id"].get<string>();
            enemyById[id] = val;
        } else if (val.is_object() && !val.contains("id")) {
            // nested group (e.g. "bosses": { "blazing_warden": {...}, ... })
            for (const auto& boss : val.items()) {
                if (boss.value().contains("id")) {
                    string id = boss.value()["id"].get<string>();
                    enemyById[id] = boss.value();
                }
            }
        }
    }
}


// Accessors
const string GameData::getStartingScene()  const { return config.starting_scene; }
int          GameData::getStartingGold()   const { return config.starting_gold; }
int          GameData::getStartingHealth() const { return config.starting_health; }
int          GameData::getMaxHealth()      const { return config.max_health; }

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

// getScene — returns the JSON object for a scene key
static const nlohmann::json JSON_NULL = nullptr;

const nlohmann::json& GameData::getScene(const string& sceneKey) const {
    if (jsonData["scenes"].contains(sceneKey)) {
        return jsonData["scenes"][sceneKey];
    }
    return JSON_NULL;
}

// createEnemyById — factory by enemy id string
FighterCharacter* GameData::createEnemyById(const string& enemyId) const {
    auto it = enemyById.find(enemyId);
    if (it == enemyById.end()) {
        cerr << "WARNING: unknown enemy id \"" << enemyId << "\"\n";
        return nullptr;
    }

    const auto& data = it->second;
    string name      = data["name"].get<string>();
    int    hp        = data["hp"].get<int>();
    string element   = data.value("element", "fire"); // default fire if null

    int code = 2; // fire default
    if      (element == "air")   code = 0;
    else if (element == "earth") code = 1;
    else if (element == "fire")  code = 2;
    else if (element == "water") code = 3;

    FighterCharacter* npc = nullptr;
    if      (code == 0) npc = new NPCAirBender  (name, code);
    else if (code == 1) npc = new NPCEarthBender(name, code);
    else if (code == 2) npc = new NPCFireBender (name, code);
    else if (code == 3) npc = new NPCWaterBender(name, code);

    if (npc) {
        npc->setHealth(hp);
        // Apply attack/defense from JSON if present
        if (data.contains("attack"))  npc->setStrength(data["attack"].get<int>());
        if (data.contains("defense")) npc->setDefense (data["defense"].get<int>());
    }
    return npc;
}


// Legacy region-based factories (delegate to createEnemyById)
FighterCharacter* GameData::createMinionFromJSON(const string& regionId) {
    // Find the minion id for this region from the regions list
    for (const auto& region : jsonData["regions"]) {
        if (region["id"].get<string>() == regionId) {
            return createEnemyById(region["minion"]["id"].get<string>());
        }
    }
    return nullptr;
}

FighterCharacter* GameData::createBossFromJSON(const string& regionId) {
    for (const auto& region : jsonData["regions"]) {
        if (region["id"].get<string>() == regionId) {
            return createEnemyById(region["boss"]["id"].get<string>());
        }
    }
    return nullptr;
}
