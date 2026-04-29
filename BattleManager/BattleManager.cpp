#include "BattleManager.hpp"
#include <iostream>
#include <thread>
#include <chrono>

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
    std::cout << "\n========== HEALTH STATUS ==========\n";
    std::cout << "Players:\n";
    for (auto p : players)
        std::cout << " - " << p->getName() << " (HP: " << p->getHealth() << ")\n";
    std::cout << "\nEnemies:\n";
    for (auto e : enemies)
        std::cout << " - " << e->getName() << " (HP: " << e->getHealth() << ")\n";
    std::cout << "===================================\n";
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
        std::cout << "\n★★★ VICTORY! ★★★\n";
    } else {
        std::cout << "\n☠ DEFEAT... ☠\n";
    }
}

void BattleManager::performTurn(FighterCharacter* attacker, 
                                std::vector<FighterCharacter*>& allies, 
                                std::vector<FighterCharacter*>& enemies, 
                                bool isNPC) {
    if (attacker->getHealth() <= 0) return;

    std::cout << "\n>> " << attacker->getName() << "'s turn!\n";
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