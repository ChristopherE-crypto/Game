#ifndef DUNGEON_H
#define DUNGEON_H
#include "room.h"
#include <vector>

struct Dungeon
{
  std::vector<Room> rooms;
  std::vector<std::vector<Vector2>> roomCorners;
};


void initDungeon(Dungeon& dungeon);
void drawDungeon(Dungeon& dungeon);
void buildStarterRoom(Dungeon& dungeon);
void buildDungeon(Dungeon& dungeon);
void loadFirstDungeon(Dungeon& dungeon);





#endif
