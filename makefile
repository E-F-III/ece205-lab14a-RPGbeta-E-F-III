# ===========================================================
# Makefile for ECE205 Lab 13a - Game Battle
# ===========================================================

CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g

TARGET   := game_battle
OBJ_DIR  := obj

# ===========================================================
# Source files
# ===========================================================
SRCS := main.cpp \
        Characters/GameCharacter.cpp \
        Characters/FighterCharacter.cpp \
        Characters/BendingSystem/Air_Bending.cpp \
        Characters/BendingSystem/Bending_System.cpp \
        Characters/BendingSystem/Earth_Bending.cpp \
        Characters/BendingSystem/Fire_Bending.cpp \
        Characters/BendingSystem/Water_Bending.cpp \
        Characters/PlayerControlled/AirBender.cpp \
        Characters/PlayerControlled/EarthBender.cpp \
        Characters/PlayerControlled/FireBender.cpp \
        Characters/PlayerControlled/PlayerCharacter.cpp \
        Characters/PlayerControlled/WaterBender.cpp \
        Characters/NPC/NPCAirBender.cpp \
        Characters/NPC/NPCEarthBender.cpp \
        Characters/NPC/NPCFireBender.cpp \
        Characters/NPC/NPCharacter.cpp \
        Characters/NPC/NPCWaterBender.cpp \
        BattleManager/BattleManager.cpp \
        util/TextDisplay.cpp \

# ===========================================================
# Object files (mirrors source paths under obj/)
# ===========================================================
OBJS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Include paths
INCLUDES := -I. \
            -ICharacters \
            -ICharacters/BendingSystem \
            -ICharacters/PlayerControlled \
            -ICharacters/NPC \
            -IBattleManager \
            -Iutil

# ===========================================================
# Default target
# ===========================================================
all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Build successful: ./$(TARGET)"

# ===========================================================
# Compile rules — create obj subdirs as needed
# ===========================================================
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create top-level obj dir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# ===========================================================
# Run the program
# ===========================================================
run: $(TARGET)
	./$(TARGET)

# ===========================================================
# Remove build artifacts
# ===========================================================
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Cleaned up build artifacts."

# ===========================================================
# Rebuild from scratch
# ===========================================================
rebuild: clean all

.PHONY: all run clean rebuild