#include "game.h"
#include <raylib.h>

void initGame(Game& game)
{
  game.shouldClose = false;
  game.gameState = MENU;
  loadPlayerSprite(game);
}

void loadPlayerSprite(Game& game)
{
  Image img = LoadImage("./assets/Soldier.png");
  game.textures.push_back(LoadTextureFromImage(img));
  ImageFlipHorizontal(&img);
  game.textures.push_back(LoadTextureFromImage(img));
  UnloadImage(img);
}
