#include "player.h"
#include "constants.h"
#include <raylib.h>
#include <raymath.h>

void initPlayer(Player& player)
{
  player.position = (Vector3){0.0f, 0.0f, 0.0f};
  player.size = (Vector3){5.0f, 5.0f, 5.0f};
  player.currentVelocity = {0};
  player.acceleration = 10.0f;
  player.deceleration = 15.0f;
  player.walkSpeed = 2.0f;
  player.runSpeed = 4.0f;
  player.animations = {};
  player.animationData = {};
  player.currentFrame = 0;
  player.animTime = 0.0f;
  player.action = IDLE_RIGHT;
  player.direction = RIGHT;

  loadPlayerAnimations(player, PLAYER_FRAME_NUM, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT);
}

std::vector<std::vector<Rectangle>> loadSpritesIntoRectangles(int frameCount, int rowIndex, int frameOffset, int frameWidth, int frameHeight)
{
  std::vector<Rectangle> frames;
  for(int i = 0; i < frameCount - frameOffset; i++)
  {
    frames.push_back({
        (float)(i * frameWidth),
        (float)(rowIndex * frameHeight),
        (float)frameWidth,
        (float)frameHeight
        });
  }

  std::vector<Rectangle> framesFlipped;
  for(int i = frameCount - 1; i >= frameOffset; i--)
  {
    framesFlipped.push_back({
        (float)(i * frameWidth),
        (float)(rowIndex * frameHeight),
        (float)frameWidth,
        (float)frameHeight
        });
  }

  std::vector<std::vector<Rectangle>> allFrames = {frames, framesFlipped};

  return allFrames;
}

void loadPlayerAnimations(Player& player, int numFrames, int frameWidth, int frameHeight)
{
  player.animations.clear();
  player.animationData.clear();

  std::vector<std::vector<Rectangle>> frames = loadSpritesIntoRectangles(numFrames, PLAYER_IDLE_INDEX, 3, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT);

  // load idle animations
  player.animations.push_back(frames[0]);
  player.animations.push_back(frames[1]);
  player.animationData.push_back({PLAYER_IDLE_SPEED});
  player.animationData.push_back({PLAYER_IDLE_SPEED});

  frames.clear();
  frames = loadSpritesIntoRectangles(numFrames, PLAYER_WALK_INDEX, 1, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT);

  // load walk animations
  player.animations.push_back(frames[0]);
  player.animations.push_back(frames[1]);
  player.animationData.push_back({PLAYER_WALK_SPEED});
  player.animationData.push_back({PLAYER_WALK_SPEED});


  frames.clear();
}

Vector3 getPlayerMovementInput(const Camera3D &camera, float cameraRotationAngle)
{
  Vector3 movementInput = {0};

  // Get camera forward vector (normalized)
  Vector3 cameraForward = Vector3Normalize((Vector3){
      sinf(cameraRotationAngle), 
      0, 
      cosf(cameraRotationAngle)
  });

  // Process movement inputs
  if (IsKeyDown(KEY_W)) movementInput = Vector3Add(movementInput, Vector3Negate(cameraForward));
  if (IsKeyDown(KEY_S)) movementInput = Vector3Add(movementInput, cameraForward);
  if (IsKeyDown(KEY_A)) movementInput = Vector3Add(movementInput, (Vector3){-cameraForward.z, 0, cameraForward.x});
  if (IsKeyDown(KEY_D)) movementInput = Vector3Add(movementInput, (Vector3){cameraForward.z, 0, -cameraForward.x});

  // Normalize if there's any input
  if (Vector3Length(movementInput) > 0) {
    movementInput = Vector3Normalize(movementInput);
  }

  return movementInput;
}

void updatePlayerFacingDirection(Player &player)
{
  if(IsKeyDown(KEY_D)) player.direction = RIGHT;
  if(IsKeyDown(KEY_A)) player.direction = LEFT;
}

void handleCameraMovement(Player& player, Camera3D& camera, float& cameraRotationAngle, float& cameraDistance, float deltaTime)
{
  if(IsKeyDown(KEY_Q))
  {
    cameraRotationAngle -= CAMERA_ROTATION_SPEED * deltaTime;
  }
  if(IsKeyDown(KEY_E))
  {
    cameraRotationAngle += CAMERA_ROTATION_SPEED * deltaTime;
  }

  float wheel = GetMouseWheelMove();
  if(wheel != 0)
  {
    cameraDistance = Clamp(cameraDistance - wheel * CAMERA_ZOOM_SPEED * deltaTime, CAMERA_MIN_DISTANCE, CAMERA_MAX_DISTANCE);
  }

  cameraRotationAngle = fmodf(cameraRotationAngle, 2 * PI);

  if(cameraRotationAngle < 0)
  {
    cameraRotationAngle += 2 * PI;
  }

  Vector3 cameraOffset = {
    sinf(cameraRotationAngle) * cameraDistance,
    CAMERA_HEIGHT,
    cosf(cameraRotationAngle) * cameraDistance
  };

  Vector3 desiredCameraPos = {
    player.position.x + cameraOffset.x,
    player.position.y + cameraOffset.y,
    player.position.z + cameraOffset.z
  };

  camera.position = Vector3Lerp(camera.position, desiredCameraPos, CAMERA_FOLLOW_SPEED * deltaTime);

  camera.target = player.position;

}

void applyPlayerMovement(Player &player, Vector3 movementInput, float deltaTime)
{
  bool isMoving = Vector3Length(movementInput) > 0;
  float currentSpeed = IsKeyDown(KEY_LEFT_SHIFT) ? player.runSpeed : player.walkSpeed;
    
  Vector3 targetVelocity = Vector3Scale(movementInput, currentSpeed);
    
  player.currentVelocity = Vector3MoveTowards(
      player.currentVelocity, 
      targetVelocity, 
      isMoving ? player.acceleration * deltaTime : player.deceleration * deltaTime
  );
    
  player.position = Vector3Add(player.position, Vector3Scale(player.currentVelocity, deltaTime));
}

void handlePlayerActionState(Player &player)
{
  if (Vector3Length(player.currentVelocity) > 0.1f) {
      player.action = player.direction == RIGHT ? WALK_RIGHT : WALK_LEFT;
  } 
  else {
      player.action = player.direction == RIGHT ? IDLE_RIGHT : IDLE_LEFT;
  }
    
  //player.direction = player.facingRight ? RIGHT : LEFT;
}

void updatePlayerAnimation(Player &player, float deltaTime)
{
  // Update animation timer
  player.animTime += deltaTime;
  float currentFrameDuration = player.animationData[player.action].frameDuration;
    
  if (player.animTime >= currentFrameDuration) {
      player.animTime = 0;
      player.currentFrame = (player.currentFrame + 1) % player.animations[player.action].size();
  }
}

void updatePlayer(Player& player, float deltaTime, Camera3D& camera, float& cameraRotationAngle, float& cameraDistance)
{

  Action previousAction = player.action;

  Vector3 movementInput = getPlayerMovementInput(camera, cameraRotationAngle);
  updatePlayerFacingDirection(player);

  applyPlayerMovement(player, movementInput, deltaTime);

  handlePlayerActionState(player);

  if(player.action != previousAction)
  {
    float progress = player.animTime / player.animationData[previousAction].frameDuration;
    player.currentFrame = 0;
    player.animTime = progress * player.animationData[player.action].frameDuration;
    //previousAction = player.action;
  }

  updatePlayerAnimation(player, deltaTime);

  handleCameraMovement(player, camera, cameraRotationAngle, cameraDistance, deltaTime);


  /*
  if(IsKeyDown(KEY_Q)) 
  {
    cameraRotationAngle -= cameraRotationSpeed * deltaTime;
  }
  if(isKeyDown(KEY_E))
  {
    cameraRotationAngle += cameraRotationSpeed * deltaTime;
  }

  float wheel = GetMouseWheelMove();
  if(wheel != 0)
  {
    cameraDistance = Clamp(cameraDistance - wheel * zoomSpeed * deltaTime, minCameraDistance, maxCameraDistance);
  }
  

  cameraRotationAngle = fmodf(cameraRotationAngle, 2 * PI);

  if(cameraRotationAngle < 0)
  {
    cameraRotationAngle += 2 * PI;
  }


  cameraOffset = {
    sinf(cameraRotationAngle) * cameraDistance,
    cameraHeight,
    cosf(cameraRotationAngle) * cameraDistance
  };

  Vector3 desiredCameraPos = {
    player.position.x + cameraOffset.x,
    player.position.y + cameraOffset.y,
    player.position.z + cameraOffset.z
  };

  camera.position = Vector3Lerp(camera.position, desiredCameraPos, cameraFollowSpeed * deltaTime);

  camera.target = player.position;
  */
}

void drawPlayer(Player& player, Camera3D& camera, Texture2D& texture)
{
  Vector2 playerSize = {
    PLAYER_FRAME_WIDTH * PLAYER_SPRITE_SCALE,
    PLAYER_FRAME_HEIGHT * PLAYER_SPRITE_SCALE
  };

  bool isPlayerAnimsEmpty = player.animations.empty();
  bool isPlayerAnimsActionEmpty = player.animations[player.action].empty();
  bool isPlayerCurrentFrameInBounds = player.currentFrame < player.animations[player.action].size();

  if(!isPlayerAnimsEmpty && !isPlayerAnimsActionEmpty && isPlayerCurrentFrameInBounds)
  {
    Rectangle frameRect = player.animations[player.action][player.currentFrame];

    DrawBillboardRec(
        camera,
        texture, 
        frameRect, 
        player.position, 
        playerSize, 
        WHITE
    );
  }
}
