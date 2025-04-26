#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>
#include <vector>

enum GameState
{
  MENU,
  PLAYING,
  PAUSED,
  GAME_OVER
};

struct Button
{
  Rectangle bounds;
  const char* text;
  Color color;
  Color hoverColor;
  bool hovered;
};

enum Action
{
  IDLE_RIGHT,
  IDLE_LEFT,
  WALK_RIGHT,
  WALK_LEFT,
  ATTACK_RIGHT,
  ATTACK_LEFT,
  DIE_RIGHT,
  DIE_LEFT
};

struct AnimationData
{
  float frameDuration;
};

struct Player
{
  Vector3 position;
  Vector3 size;
  float speed;
  std::vector<std::vector<Rectangle>> animations;
  std::vector<AnimationData> animationData;
  bool facingRight;
  bool idle;
  Action action;
};

enum Direction
{
  RIGHT,
  LEFT
};

struct Game
{
  std::vector<Texture2D> textures;
  Direction direction;

  GameState gameState;
  
  //Texture2D heightmap;
  //Model terrainModel;
 // float terrainScale = 1.0f;
//float terrainHeightScale = 0.5f;

  Model treeModel;
  Model rockModel;
  Model boulderModel;

  Font font;
  std::vector<Button> menuButtons;
};

struct Environment
{
  std::vector<Vector3> trees;
  std::vector<std::pair<Vector3, float>> rocks;
  std::vector<std::pair<Vector3, float>> boulders;
};

#endif
