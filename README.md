# Lab 13a - Let the Battle Begin!
**ECE 205 - Spring 2026**  
**Authors:** Edward Felipe III <efelipe3@hawaii.edu>, Steven Javier <sdjavier@hawaii.edu>, Menden Cannistra <mendenc@hawaii.edu>
---

## Overview
This project focused on implementing containers to track characters within a turn based battle system.
---

## Class Hierarchy

``` 
GameCharacter
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

## Subclass Descriptions

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

---

## Sample Interaction

```
Enter the number of player characters (Max 4): 3

Enter a name for Player 1: Edward
Enter a bending style (0=Air, 1=Earth, 2=Fire, 3=Water): 0
--- Edward Stats ---
Bending: Air
Health: 100
Edward the AirBender: Greetings! I am Edward. The wind is at my command, and I will use it to protect my allies

Enter a name for Player 2: Steven
Enter a bending style (0=Air, 1=Earth, 2=Fire, 3=Water): 3
--- Steven Stats ---
Bending: Water
Health: 100
Steven the WaterBender: Greetings! I am Steven. The water is at my command, and I will use it to protect my allies

Enter a name for Player 3: Menden
Enter a bending style (0=Air, 1=Earth, 2=Fire, 3=Water): 2
--- Menden Stats ---
Bending: Fire
Health: 100
Menden the FireBender: Greetings! I am Menden. The flames are at my command, and I will use them to protect my allies
Enter the number of enemy characters (Max 4): 3

========== HEALTH STATUS ==========
Players:
 - Edward(Health): 100
 - Steven(Health): 100
 - Menden(Health): 100

Enemies:
 - Enemy 1(Health): 100
 - Enemy 2(Health): 100
 - Enemy 3(Health): 100
===================================

>> Edward's turn!
Choose a target type: 0=Enemy, 1=Ally: 1
Choose an ally to support:
0: Edward (Health: 100)
1: Steven (Health: 100)
2: Menden (Health: 100)
2

Game Master: What would you like Edward to do?
Available Air Bending Actions for Edward:
0: Air Slice
1: Air Shield
2: Flight
Enter the number corresponding to your choice (0=Slice, 1=Shield, 2=Flight): 1

--- Action Selected: Air Shield ---

Edward creates an Air Shield! A swirling barrier of wind protects them from incoming attacks.

Air Shield activates!ProtectsMenden
Shield logic not fully implemented yet, but it will block the next incoming attack.

>> Steven's turn!
Choose a target type: 0=Enemy, 1=Ally: 0
Choose an enemy to attack:
0: Enemy 1 (Health: 100)
1: Enemy 2 (Health: 100)
2: Enemy 3 (Health: 100)
0

Game Master: What would you like Steven to do?
Available Water Bending Actions for Steven:
0: Healing Waters
1: Water Whip
2: Ice Barrier
Enter the number corresponding to your choice (0=Healing, 1=Whip, 2=Barrier): 1

--- Action Selected: Water Whip ---

Steven uses Water Whip on Enemy 1!

Water Whip hits!
Water Whip deals 9 damage to Enemy 1
```