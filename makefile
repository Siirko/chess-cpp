CC := g++
CFLAGS ?= -Wall -Werror -g -std=c++11
FLAGS_GUI := -lstdc++fs -lSDL2 -lSDL2_image -lSDL2_ttf -DWITH_GUI
LDLIBS ?= -lm

EXEC = chess-cli
EXECGUI = chess-gui

INCLUDE_PATH ?= ./includes
SRC_PATH = ./src
OBJ_PATH = ./obj
BIN_PATH = ./bin

SOURCES := $(filter-out $(SRC_PATH)/main.cpp $(SRC_PATH)/ui/gui/gui.cpp $(SRC_PATH)/ui/gui/ltexture.cpp, $(wildcard $(SRC_PATH)/*.cpp $(SRC_PATH)/*/*.cpp $(SRC_PATH)/*/*/*.cpp))
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.hpp $(INCLUDE_PATH)/*/*.hpp $(INCLUDE_PATH)/*/*/*.hpp)
OBJECTS  := $(SOURCES:$(SRC_PATH)/%.cpp=$(OBJ_PATH)/%.o)
GUI_ON := false

.PHONY: cli
cli: clean
	$(MAKE) $(BIN_PATH)/$(EXEC)

.PHONY: gui
gui: clean
	$(MAKE) GUI_ON=true $(BIN_PATH)/$(EXECGUI)

docs:
	mkdir -p ./docs
	doxygen Doxyfile

$(BIN_PATH)/$(EXEC): $(OBJ_PATH)/main.o $(OBJECTS)
	mkdir -p $(BIN_PATH)
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "Linking complete!"

$(BIN_PATH)/$(EXECGUI): $(OBJ_PATH)/main.o $(OBJ_PATH)/gui.o  $(OBJ_PATH)/ltexture.o $(OBJECTS) 
	mkdir -p $(BIN_PATH)
	$(CC) -o $@ $^ $(CFLAGS) $(FLAGS_GUI) $(LDLIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp 
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH) 

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	mkdir -p $(dir $@)
ifeq ($(GUI_ON), true)
	$(CC) -o $@ -c $< $(CFLAGS) $(FLAGS_GUI) -I$(INCLUDE_PATH)
else
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)
endif

$(OBJ_PATH)/gui.o: $(SRC_PATH)/ui/gui/gui.cpp
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) $(FLAGS_GUI) -I$(INCLUDE_PATH)

$(OBJ_PATH)/ltexture.o: $(SRC_PATH)/ui/gui/ltexture.cpp
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) $(FLAGS_GUI) -I$(INCLUDE_PATH)

.PHONY: clean
clean:
	rm -fr $(OBJ_PATH)
	rm -fr $(BIN_PATH)
