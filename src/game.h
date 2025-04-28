#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>

enum GameState
{
  MENU,
  PLAYING,
  PAUSED,
  GAME_OVER
};

struct Game
{
  GameState gameState;
  std::vector<Texture2D> textures;
  bool shouldClose;
  //Font font;
};

void initGame(Game& game);
void loadPlayerSprite(Game& game);

#endif
