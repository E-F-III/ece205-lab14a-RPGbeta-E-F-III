# Lab 14a - RPGData
**ECE 205 - Spring 2026**  
**Authors:** 
- Edward Felipe III <efelipe3@hawaii.edu> 
- Steven Javier <sdjavier@hawaii.edu>
- Menden Cannistra <mendenc@hawaii.edu>
---

## Overview
This project focused on implementing a json parser to handle the story. 
The team also decided to refactor the code to implement better Object Oriented Design.
---

## Class Hierarchy

``` 
GameManager
├── GameData
├── DungeonSystem
├── BattleManager
└── GameCharacter
    └── FighterCharacter
        ├── PlayerCharacter
            ├── Airbender 
            ├── Waterbender
            ├── Earthbender
            └── Firebender
        ├── NPCharacter
            ├── NPCAirbender
            ├── NPCWaterbender
            ├── NPCEarthbender
            ├── NPCFirebender
    
```

---

## Game Logic Classes

### Game Manager
The singleton class that tracks the current state of the game.

### Game Data
The singleton class that parses the json file and handles said data.

### DungeonSystem
The class that tracks the current position within the dungeon, and handles different room types.

### BattleManager
The class that tracks the state of a battle within a dungeon, and the final boss.

## Character Class Descriptions

### GameCharacter
The base class for all characters in the game. It provides basic functionality such as setting and getting the character's name, and methods for greeting and speaking.

### FighterCharacter
Derived from GameCharacter, this class represents characters capable of combat. It includes attributes like health, strength, agility, defense, and a bending style. FighterCharacters can perform actions against other characters and have methods to roll dice for combat resolution.

### PlayerCharacter
A subclass of FighterCharacter representing characters controlled by the player. It overrides the greet method and performAction to allow player-driven decisions in battles.

### Airbender
A player-controlled character specializing in air bending. Airbenders can manipulate air for attacks like air slices, defensive shields, and flight. They inherit from PlayerCharacter and use the AirBending system for their abilities.

### Waterbender
A player-controlled character specializing in water bending. Waterbenders manipulate water for healing, defensive barriers, and offensive strikes. They use the WaterBending system.

### Earthbender
A player-controlled character specializing in earth bending. Earthbenders control earth and stone for powerful defensive walls and ground-based attacks. They utilize the EarthBending system.

### Firebender
A player-controlled character specializing in fire bending. Firebenders generate and control fire for intense offensive attacks and explosive abilities. They employ the FireBending system.

### NPCharacter
A subclass of FighterCharacter for non-player characters (NPCs). NPCs are controlled by the game's AI and can be allies or enemies. They have their own greeting and action logic.

### NPCAirBender
An NPC version of the Airbender. These characters use air bending abilities autonomously in battles, controlled by AI logic.

### NPCWaterBender
An NPC version of the Waterbender. They perform water bending actions as part of the game's automated combat system.

### NPCEarthBender
An NPC version of the Earthbender. These NPCs utilize earth bending for AI-driven combat maneuvers.

### NPCFireBender
An NPC version of the Firebender. They execute fire bending attacks and defenses under AI control.

---

## How to Build and Run

### Requirements
- g++ with C++17 support
- make

### Build
```bash
make
```

### Run
```bash
./game
```

### Clean
```bash
make clean
```