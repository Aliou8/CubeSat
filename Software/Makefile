# Makefile pour le projet C/C++
PROJET_NAME = CubeSat
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
TES_DIR = test

# Compilateurs et options
CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -g -O2 -std=c++20 
C_FLAGS = -Wall -Wextra -g -O2
LDFLAGS = -lm -lws2_32 

# Fichiers sources et objets
# On utilise wildcard pour trouver tous les fichiers .cpp et .c dans le dossier src

SRC_CXX = $(wildcard $(SRC_DIR)/*.cpp)
SRC_C = $(wildcard $(SRC_DIR)/*.c)
OBJ_CXX = $(SRC_CXX:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ_C = $(SRC_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


.PHONY: all clean prepare
all: prepare $(BIN_DIR)/$(PROJET_NAME)

prepare:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(BIN_DIR)/$(PROJET_NAME): $(OBJ_CXX) $(OBJ_C)
	@$(CXX) $(OBJ_CXX) $(OBJ_C) -o $@ $(LDFLAGS)
	@echo "Linking complete: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $< to $@"
	@$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiled $< to $@"
	@$(CC) $(C_FLAGS) -I$(INCLUDE_DIR) -c $< -o $@	

# Nettoyage du répertoire de build
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Build directory cleaned."

ARGS ?=
# Exécution du projet
run: all
	@echo "Running the project..."
	@./$(BIN_DIR)/$(PROJET_NAME) $(ARGS)
	
    