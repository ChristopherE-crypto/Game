#ifndef DUNGEON_H
#define DUNGEON_H
#include "room.h"
#include <vector>

struct Dungeon
{
  std::vector<Room> rooms;
};


void initDungeon(Dungeon& dungeon);
void drawDungeon(Dungeon& dungeon);






#endif
