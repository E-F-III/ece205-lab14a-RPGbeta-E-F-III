#include "BattleManager.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "util/TextDisplay.hpp"

// Constructor
BattleManager::BattleManager(std::vector<FighterCharacter*> p, std::vector<FighterCharacter*> e)
    : players(p), enemies(e) {}

// Destructor
BattleManager::~BattleManager() {
    // Per your note: main handles cleanup or characters are shared.
}

bool BattleManager::isPartyAlive(const std::vector<FighterCharacter*>& party) {
    for (auto* c : party) {
        if (c->getHealth() > 0) return true;
    }
    return false;
}

void BattleManager::displayHealth() {
    util::clearScreen(); // Keeps the console from scrolling infinitely
    util::printColor("\n========== HEALTH STATUS ==========\n", util::FG_CYAN);
    
    std::cout << "Players:\n";
    for (auto p : players) {
        std::cout << " - " << p->getName() << " ";
        util::printProgressBar(p->getHealth(), 100, '#', util::FG_GREEN);
        std::cout << " (HP: " << p->getHealth() << ")\n";
    }

    std::cout << "\nEnemies:\n";
    for (auto e : enemies) {
        std::cout << " - " << e->getName() << " ";
        util::printProgressBar(e->getHealth(), 100, '#', util::FG_RED);
        std::cout << " (HP: " << e->getHealth() << ")\n";
    }
    util::printColor("===================================\n", util::FG_CYAN);
}

FighterCharacter* BattleManager::getRandomAliveMember(std::vector<FighterCharacter*>& party) {
    std::vector<FighterCharacter*> aliveMembers;
    for (auto member : party) {
        if (member->getHealth() > 0) aliveMembers.push_back(member);
    }

    if (aliveMembers.empty()) return nullptr;
    return aliveMembers[rand() % aliveMembers.size()];
}

void BattleManager::runBattle() {
    while (isPartyAlive(players) && isPartyAlive(enemies)) {
        displayHealth();
        // 1. Players Turn
        for (auto p : players) {
            if (isPartyAlive(enemies)) performTurn(p, players, enemies, false);
        }
        // 2. Enemies Turn
        for (auto e : enemies) {
            if (isPartyAlive(players)) performTurn(e, enemies, players, true);
        }
    }

    if (isPartyAlive(players)) {
        util::printColor("\n★★★ VICTORY! ★★★\n", util::FG_YELLOW);
    } else {
        util::printColor("\n ☠  DEFEAT...  ☠ \n", util::FG_RED);
    }
}

void BattleManager::performTurn(FighterCharacter* attacker,
                                std::vector<FighterCharacter*>& allies,
                                std::vector<FighterCharacter*>& enemies,
                                bool isNPC) {
    if (attacker->getHealth() <= 0) return;
    
    std::string turnMsg = "\n>> " + attacker->getName() + "'s turn!\n";
    util::printColor(turnMsg, util::FG_MAGENTA);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    FighterCharacter* finalTarget = nullptr;
    if (isNPC) {
        // AI Logic: 80% Attack, 20% Support
        if ((rand() % 100 < 20)) {
            finalTarget = getRandomAliveMember(allies);
            if (finalTarget) std::cout << attacker->getName() << " decides to support an ally!\n";
        } else {
            finalTarget = getRandomAliveMember(enemies);
        }
    } else {
        int choice;
        std::cout << "Action: (0) Attack Enemy | (1) Support Ally: ";
        while (!(std::cin >> choice) || (choice != 0 && choice != 1)) {
            std::cout << "Invalid. Enter 0 or 1: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        std::vector<FighterCharacter*>& potentialTargets = (choice == 0) ? enemies : allies;

        for (size_t i = 0; i < potentialTargets.size(); i++) {
            std::cout << i << ": " << potentialTargets[i]->getName()
                      << " (HP: " << potentialTargets[i]->getHealth() << ")\n";
        }
        int targetIdx;
        std::cout << "Select index: ";
        while (!(std::cin >> targetIdx) || targetIdx < 0 || targetIdx >= static_cast<int>(potentialTargets.size()) || potentialTargets[targetIdx]->getHealth() <= 0) {
            std::cout << "Invalid index. Try again: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        finalTarget = potentialTargets[targetIdx];
    }
    if (finalTarget) {
        attacker->performAction(*finalTarget);
    }
}
