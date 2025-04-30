#include "dungeon.h"
#include "constants.h"

void buildStarterRoom(Dungeon& dungeon)
{
  Room room;
  std::vector<Vector2> roomCorners = {ROOM_UPPER_RIGHT_CORNER, ROOM_LOWER_RIGHT_CORNER, ROOM_LOWER_LEFT_CORNER, ROOM_UPPER_LEFT_CORNER};
  buildRoom(room, roomCorners, 1.0f, 5.0f, 20.0f);
  dungeon.rooms.push_back(room);
}

void buildDungeon(Dungeon& dungeon)
{
  Room room;
  for(auto& roomCorner : dungeon.roomCorners)
  {
    buildRoom(room, roomCorner, 1.0f, 5.0f, 20.0f);
    dungeon.rooms.push_back(room);
  }
}

void loadFirstDungeon(Dungeon& dungeon)
{
  std::vector<std::vector<Vector2>> roomCorners = {
    {
      ROOM_UPPER_RIGHT_CORNER,
      ROOM_LOWER_RIGHT_CORNER,
      ROOM_LOWER_LEFT_CORNER,
      ROOM_UPPER_LEFT_CORNER
    },
    {
      (Vector2){20.0f, -40.0f},
      (Vector2){20.0f, -20.0f},
      (Vector2){0.0f, -20.0f},
      (Vector2){0.0f, -40.0f}
    },
    {
      (Vector2){20.0f, -60.0f},
      (Vector2){20.0f, -40.0f},
      (Vector2){0.0f, -40.0f},
      (Vector2){0.0f, -60.0f}
    },
    {
      (Vector2){40.0f, -60.0f},
      (Vector2){40.0f, -40.0f},
      (Vector2){20.0f, -40.0f},
      (Vector2){20.0f, -60.0f}
    },
    {
      (Vector2){40.0f, -80.0f},
      (Vector2){40.0f, -60.0f},
      (Vector2){20.0f, -60.0f},
      (Vector2){20.0f, -80.0f}
    }
  };

  dungeon.roomCorners = roomCorners;
}


void initDungeon(Dungeon& dungeon)
{
  //dungeon.roomCorners = roomCorners;
}

void drawDungeon(Dungeon& dungeon)
{
  for(int i = 0; i < dungeon.rooms.size(); i++)
  {
    drawRoom(dungeon.rooms[i]);
  }
  //drawRoom(dungeon.rooms[]);
}
