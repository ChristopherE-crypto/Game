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
};

#endif
