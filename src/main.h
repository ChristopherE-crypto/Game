#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>
#include <vector>

struct Player
{
  Vector3 position;
  Vector3 size;
  float speed;
  std::vector<std::vector<Rectangle>> animations;
  bool facingRight;
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

enum Direction
{
  RIGHT,
  LEFT
};

struct Game
{
  std::vector<Texture2D> textures;
};

#endif
