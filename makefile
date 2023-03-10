CC := g++
CFLAGS ?= -Wall -Werror -g -lstdc++fs -std=c++11 -lSDL2 -lSDL2_image -lSDL2_ttf
LDLIBS ?= -lm

EXEC = chess-cpp

INCLUDE_PATH ?= ./include

SRC_PATH = ./src
OBJ_PATH = ./obj
BIN_PATH = ./bin

SOURCES  := $(wildcard $(SRC_PATH)/*.cpp $(SRC_PATH)/*/*.cpp $(SRC_PATH)/*/*/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.hpp $(INCLUDE_PATH)/*/*.hpp $(INCLUDE_PATH)/*/*/*.hpp)
OBJECTS  := $(SOURCES:$(SRC_PATH)/%.cpp=$(OBJ_PATH)/%.o)

all: $(BIN_PATH)/$(EXEC)

$(BIN_PATH)/$(EXEC): $(OBJECTS)
	mkdir -p $(BIN_PATH)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

.PHONY: clean
clean:
	rm -fr $(OBJ_PATH)
	rm -fr $(BIN_PATH)