CXX = g++
CXXFLAGS = -Wall -std=c++17
INCLUDES = -I. -I~/programming/raylib/build/raylib/include/
LDFLAGS = -L~/programming/raylib/build/raylib/
LDLIBS = -lraylib

ifeq ($(OS),Windows_NT)
    LDLIBS += -lopengl32 -lgdi32 -lwinmm
else
    LDLIBS += -lm -ldl -lpthread
endif

SRCS = ./src/main.cpp ./src/player.cpp ./src/menu.cpp ./src/game.cpp ./src/room.cpp ./src/dungeon.cpp
HDRS = ./src/game.h ./src/player.h ./src/menu.h ./src/room.h ./src/dungeon.h
OBJS = $(SRCS:.cpp=.o)
EXEC = game

all: $(EXEC)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
