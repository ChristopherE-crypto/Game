#include "room.h"
#include "constants.h"
#include <raylib.h>

void initWall(Wall& wall, Vector3 position, float width, float height, float length, Color color)
{
  wall.width = width;
  wall.height = height;
  wall.length = length;
  wall.color = color;
}

void addWallToRoom(Room& room, Wall& wall)
{
  room.walls.push_back(wall);
}

void drawWall(Wall& wall)
{
  DrawCube(wall.position, wall.width, wall.height, wall.length, wall.color);
}

void addWallsToRoom(Room& room)
{
  for(int i = 0; i < 4; i++)
  {
    Wall wall = {
      (Vector3){5.0f + 2 * i, 0.1f, 0.0f},
      1.0f,
      5.0f,
      10.0f,
      RED
    };
    addWallToRoom(room, wall);
  }
}

void initRoom(Room& room)
{
  for(int i = 0; i < 4; i++)
  { 
    Wall wall = {
      (Vector3){room.position.x + (room.width/2 * i), 2.5f, room.position.y},
      1.0f,
      1.0f,
      20.0f,
      RED
    };

    room.walls.push_back(wall);
  }
  //room.width = ROOM_WIDTH;
  //room.height = ROOM_HEIGHT;
  //room.position = {0.0f, 0.0f};
  //addWallsToRoom(room);
}

void buildRoom(Room& room, std::vector<Vector2> roomCorners, float width, float height, float length)
{
  Wall wallEast = {
    (Vector3){roomCorners[0].x, 2.5f, roomCorners[0].y + ROOM_HEIGHT / 2},
    width, // 1
    height, // 5
    length, // 5
    RED
  };

  Wall wallSouth = {
    (Vector3){roomCorners[1].x - ROOM_WIDTH / 2, 2.5f, roomCorners[1].y},
    length,
    height,
    width,
    BLUE
  };

  Wall wallWest = {
    (Vector3){roomCorners[2].x, 2.5f, roomCorners[2].y - ROOM_HEIGHT / 2},
    width,
    height,
    length,
    YELLOW
  };

  Wall wallNorth = {
    (Vector3){roomCorners[3].x + ROOM_WIDTH / 2, 2.5f, roomCorners[3].y},
    length,
    height,
    width,
    GREEN
  };

  room.walls.push_back(wallEast);
  room.walls.push_back(wallSouth);
  room.walls.push_back(wallWest);
  room.walls.push_back(wallNorth);
}

void drawRoom(Room& room)
{
  for(int i = 0; i < room.walls.size(); i++)
  {
    drawWall(room.walls[i]);
  }
  /*
  Wall wall1 = {
    (Vector3){ROOM_UPPER_RIGHT_CORNER.x, 2.5f, ROOM_UPPER_RIGHT_CORNER.y + room.height/2},
    1.0f,
    5.0f,
    20.0f,
    RED
  };
  Wall wall2 = {
    (Vector3){ROOM_LOWER_RIGHT_CORNER.x - room.width/2, 2.5f, ROOM_LOWER_RIGHT_CORNER.y},
    20.0f,
    5.0f,
    1.0f,
    BLUE
  };
  Wall wall3 = {
    (Vector3){ROOM_LOWER_LEFT_CORNER.x, 2.5f, ROOM_LOWER_LEFT_CORNER.y - room.height/2},
    1.0f,
    5.0f,
    20.0f,
    YELLOW
  };
  Wall wall4 = {
    (Vector3){ROOM_UPPER_LEFT_CORNER.x + room.width/2, 2.5f, ROOM_UPPER_LEFT_CORNER.y},
    20.0f,
    5.0f,
    1.0f,
    GREEN
  };

  drawWall(wall1);
  drawWall(wall2);
  drawWall(wall3);
  drawWall(wall4);
*/

  /*
  Wall wall1 = {
    (Vector3){room.position.x + room.width, 2.5f, room.position.y + room.height/2},
    1.0f,
    5.0f,
    room.width,
    RED
  };

  Wall wall2 = {
    (Vector3){(room.position.x + room.width) - room.width/2, 2.5f, room.position.y},
    room.height,
    5.0f,
    1.0f,
    BLUE
  };

  Wall wall3 = {
    (Vector3){room.position.x, 2.5f, room.position.y - room.height/2},
    1.0f,
    5.0f,
    room.width,
    YELLOW
  };

 Wall wall4 = {
    (Vector3){room.position.x + room.width/2, 2.5f, room.position.y},
    room.height,
    5.0f,
    1.0f,
    GREEN,
};



  drawWall(wall1);
  drawWall(wall2);
  drawWall(wall3);
  //drawWall(wall4);
*/


}


