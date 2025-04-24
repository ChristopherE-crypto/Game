#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>
#include <vector>

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

struct Player
{
  Vector3 position;
  Vector3 size;
  float speed;
  std::vector<std::vector<Rectangle>> animations;
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
};

#endif
