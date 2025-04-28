#ifndef PLAYER_H
#define PLAYER_H

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

enum Direction
{
  RIGHT,
  LEFT
};

struct AnimationData
{
  float frameDuration;
};

struct Player
{
  Vector3 position;
  Vector3 size;
  Vector3 currentVelocity;
  float acceleration;
  float deceleration;
  float walkSpeed;
  float runSpeed;

  std::vector<std::vector<Rectangle>> animations;
  std::vector<AnimationData> animationData;
  int currentFrame;
  float animTime;

  //bool facingRight;
  //bool idle;
  Action action;
  Direction direction;
};

void initPlayer(Player& player);

Vector3 getPlayerMovementInput(const Camera3D& camera, float cameraRotationAngle);
void updatePlayerFacingDirection(Player& player);

void applyPlayerMovement(Player& player, Vector3 movementInput, float deltaTime);

void loadPlayerAnimations(Player& player, int numFrames, int frameWidth, int frameHeight);
void updatePlayerAnimation(Player& player, float deltaTime);
void handlePlayerActionState(Player& player);

void updatePlayer(Player& player, float deltaTime, Camera3D& camera, float& cameraRotationAngle, float& cameraDistance);

void handleCameraMovement(Player& player, Camera3D& camera, float& cameraRotationAngle, float& cameraDistance, float deltaTime);

void drawPlayer(Player& player, Camera3D& camera, Texture2D& texture);

#endif
