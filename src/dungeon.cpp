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

void drawDungeon()
{

  // first room
  // draw east wall
  DrawCubeV(
      (Vector3) {20.0f, 2.5f, -10.0f},
      (Vector3) {1.0f, 10.0f, 20.0f},
      GRAY
      );
  // draw south wall
  DrawCubeV(
      (Vector3) {10.0f, 2.5f, 0.0f},
      (Vector3) {20.0, 10.0f, 1.0f},
      GRAY
      );
  // draw west wall
  DrawCubeV(
      (Vector3) {0.0f, 2.5f, -10.0f},
      (Vector3) {1.0f, 10.0f, 20.0f},
      GRAY
      );

  // drawing north wall (includes door)
  DrawCubeV(
      (Vector3) {2.5f, 2.5f, -20.0f},
      (Vector3) {5.0f, 10.0f, 1.0f},
      GRAY
      );
  DrawCubeV(
      (Vector3) {17.5f, 2.5f, -20.0f},
      (Vector3) {5.0f, 10.0f, 1.0f},
      GRAY
      );

  // second room
  DrawCubeV(
      (Vector3) {10.0f, 2.5f, -40.0f},
      (Vector3) {20.0f, 10.0f, 1.0f},
      RED
      );
  DrawCubeV(
      (Vector3) {0.0f, 2.5f, -30.0f},
      (Vector3) {1.0f, 10.0f, 20.0f},
      RED
      );
  DrawCubeV(
      (Vector3) {20.0f, 2.5f, -37.5f},
      (Vector3) {1.0f, 10.0f, 5.0f},
      RED
      );
  DrawCubeV(
      (Vector3) {20.0f, 2.5f, -22.5f},
      (Vector3) {1.0f, 10.0f, 5.0f},
      RED
      );

  // third room
  DrawCubeV(
      (Vector3) {40.0f, 2.5f, -30.0f},
      (Vector3) {1.0f, 10.0f, 20.0f},
      GREEN
      );
  DrawCubeV(
      (Vector3) {30.0f, 2.5f, -20.0f},
      (Vector3) {20.0f, 10.0f, 1.0f},
      GREEN
      );
  DrawCubeV(
      (Vector3) {22.5f, 2.5f, -40.0f},
      (Vector3) {5.0f, 10.0f, 1.0f},
      GREEN
      );
  DrawCubeV(
      (Vector3) {37.5f, 2.5f, -40.0f},
      (Vector3) {5.0f, 10.0f, 1.0f},
      GREEN
      );
  
  // fourth room
  DrawCubeV(
      (Vector3) {40.0f, 2.5f, -50.0f},
      (Vector3) {1.0f, 10.0f, 20.0f},
      PURPLE
      );
  DrawCubeV(
      (Vector3) {20.0f, 2.5f, -50.0f},
      (Vector3) {1.0f, 10.0f, 20.0f},
      PURPLE
      );
  DrawCubeV(
      (Vector3) {22.5f, 2.5f, -60.0f},
      (Vector3) {5.0f, 10.0f, 1.0f},
      PURPLE
      );
  DrawCubeV(
      (Vector3) {37.5f, 2.5f, -60.0},
      (Vector3) {5.0f, 10.0f, 1.0f},
      PURPLE
      );

  // fifth room
  DrawCubeV(
      (Vector3) {40.0f, 2.5f, -70.0f},
      (Vector3) {1.0f, 10.0f, 20.0f},
      RED
      );
  DrawCubeV(
      (Vector3) {20.0f, 2.5f, -70.0f},
      (Vector3) {1.0f, 10.f, 20.0f},
      RED
      );
  DrawCubeV(
      (Vector3) {30.0f, 2.5f, -80.0f},
      (Vector3) {20.0f, 10.0f, 1.0f},
      RED
      );
  
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
