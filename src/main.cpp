#include <raylib.h>
#include <raymath.h>
#include "player.h"
#include "game.h"
#include "menu.h"
#include "constants.h"
#include "dungeon.h"

int main()
{
  
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DUNGEONS");

  SetTargetFPS(60);

  Game game;
  initGame(game);

  Player player;
  initPlayer(player);

  MainMenu mainMenu;
  initMenu(mainMenu);

  //Room room;
  //initRoom(room);

  Dungeon dungeon;
  //initDungeon(dungeon, roomCorners);
  loadFirstDungeon(dungeon);
  buildDungeon(dungeon);

  Camera3D camera = {0};
  camera.position = {0.0f, 1.0f, -5.0f};
  camera.target = player.position;
  camera.up = {0.0f, 1.0f, 0.0f};
  camera.fovy = 55.0f;
  camera.projection = CAMERA_PERSPECTIVE;
  float cameraRotationAngle = 0.0f;
  float cameraDistance = 5.0f;

  while(!WindowShouldClose() && !game.shouldClose)
  {
    switch(game.gameState)
    {
      case MENU:
        updateMenu(mainMenu, game);
        BeginDrawing();
        drawMenu(mainMenu);
        EndDrawing();
        break;

      case PLAYING:
        {
          float deltaTime = GetFrameTime();

          updatePlayer(player, deltaTime, camera, cameraRotationAngle, cameraDistance);

          BeginDrawing();
          ClearBackground(SKYBLUE);

          BeginMode3D(camera);
          DrawGrid(11, 20.0f);
          //DrawCube((Vector3){20.0f, 0.0f, -20.0f}, 1.0f, 1.0f, 1.0f, RED);
          //DrawCube((Vector3){20.0f, 0.0f, -20.0f}, 1.0f, 1.0f, 1.0f, RED);
          //DrawCube((Vector3){0.0f, 0.0f, -20.0f}, 1.0f, 1.0f, 1.0f, RED);
          DrawCube((Vector3){0.0f, -1.0f, 0.0f}, 200.0f, 0.1f, 200.0f, DARKGRAY);
          //drawRoom(room);
          drawDungeon();
          drawPlayer(player, camera, game.textures[player.direction]);
          EndMode3D();

          EndDrawing();
          break;
        }

      case PAUSED:
        break;

      case GAME_OVER:
        break;
    }
  }

  UnloadTexture(game.textures[0]);
  UnloadTexture(game.textures[1]);
  return 0;
}
