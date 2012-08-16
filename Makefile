DIRS := src src/graphics
PROGRAM_DIRS := $(DIRS)

INCLUDE_DIRS := -I lib/linux/SDL2/include -I lib/linux/glew/include
WARNINGS := -pedantic -Wall -Werror -Wextra

PACKAGES := gl glu libpng
CXX      := g++-4.7
CXXFLAGS := $(WARNINGS) -fopenmp -lpthread -std=c++0x -Ofast $(INCLUDE_DIRS)
CXXFLAGS += $(shell pkg-config --cflags $(PACKAGES))

LIBS := -L ./lib/linux -lGLEW -lSDL2
LIBS += $(shell pkg-config --libs $(PACKAGES))

PROGRAM = bin/main

SRC := src
OBJ := obj
BIN := bin

all: dirs $(PROGRAM)

debug: CXXFLAGS += -O0 -g
debug: LIBS += -g
debug: all

prof: CXXFLAGS += -pg
prof: LIBS += -pg
prof: all

SRC_PROGRAM := $(foreach dir, $(PROGRAM_DIRS), $(wildcard $(dir)/*.cpp))

OBJ_PROGRAM := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_PROGRAM))

DEPFILES := $(OBJ_PROGRAM:.o=.d)
DEPFILES := $(sort $(DEPFILES))

.PHONY: all clean dirs echo

all: dirs $(PROGRAM)

$(PROGRAM): $(OBJ_PROGRAM)

$(BIN)/%:
	@echo LINK $@
	@$(CXX) $^ $(LIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	@echo CXX $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@$(CXX) $(CXXFLAGS) -MM -MT "$(@:.d=.o) $@" $< > $(@:.o=.d)

clean:
	@$(RM) -rf $(PROGRAM) $(OBJ)

dirs:
	@mkdir -p $(OBJ)
	@mkdir -p $(patsubst $(SRC)/%, $(OBJ)/%, $(shell find $(PROGRAM_DIRS) -type d))

ifneq ($(MAKECMDGOALS),clean)
  -include $(DEPFILES)
endif

