#ifndef ROOM_H
#define ROOM_H

#include <raylib.h>
#include <vector>

struct Wall
{
  Vector3 position;
  float width;
  float height;
  float length;
  Color color;
};

struct Room
{
  float width;
  float height;
  Vector2 position;
  std::vector<Wall> walls; // always size 4
};

void initWall(Wall& wall);
void addWallToRoom(Room& room, Wall& wall);
void drawWall(Wall& wall);
void initRoom(Room& room);
void drawRoom(Room& room);





#endif
