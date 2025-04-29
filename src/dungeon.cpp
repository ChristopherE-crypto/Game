#include "dungeon.h"


void initDungeon(Dungeon& dungeon)
{
  for(int i = 0; i < 5; i++)
  {
    Room room = {
      20.0f,
      20.0f,
      (Vector2){0.0f, 0.0f - (20.0f * i)}
    };

    initRoom(room);
    dungeon.rooms.push_back(room);
  }
}

void drawDungeon(Dungeon& dungeon)
{
  for(int i = 0; i < 5; i++)
  {
    drawRoom(dungeon.rooms[i]);
  }
}
