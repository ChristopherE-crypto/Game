#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "main.h"

// Return a vector of Rectangles for a specific animation row
std::vector<Rectangle> loadSpritesIntoRectangles(int frameCount, int rowIndex, int frameOffset, int frameWidth, int frameHeight) {

    std::vector<Rectangle> frames;
    for (int i = 0; i < frameCount - frameOffset; i++) {
        frames.push_back({
            (float)(i * frameWidth),
            (float)(rowIndex * frameHeight),
            (float)frameWidth,
            (float)frameHeight
        });
    }
    return frames;
}

std::vector<Rectangle> loadSpritesIntoRectanglesFlipped(int frameCount, int rowIndex, int frameOffset, int frameWidth, int frameHeight)
{

  std::vector<Rectangle> frames;
  for(int i = frameCount - 1; i >= frameOffset; i--)
  {
    frames.push_back({
      (float)(i * 100),
      (float)(rowIndex * 100),
      (float)frameWidth,
      (float)frameHeight
    });
  }
  return frames;

}

void loadPlayerAnimations(Player& player, int numFrames, int frameWidth, int frameHeight) {

  player.animations.clear();
  player.animationData.clear();

  const float idleSpeed = 0.5f;
  const float walkSpeed = 0.1f;
  const float attackSpeed = 0.25f;
  const float dieSpeed = 0.5f;

  player.animations.push_back(loadSpritesIntoRectangles(numFrames, 0, 3, frameWidth, frameHeight)); // Idle
  player.animations.push_back(loadSpritesIntoRectanglesFlipped(numFrames, 0, 3, frameWidth, frameHeight));

  player.animationData.push_back({idleSpeed});
  player.animationData.push_back({idleSpeed});

  player.animations.push_back(loadSpritesIntoRectangles(numFrames, 1, 1, frameWidth, frameHeight)); // walk
  player.animations.push_back(loadSpritesIntoRectanglesFlipped(numFrames, 1, 1, frameWidth, frameHeight));

  player.animationData.push_back({walkSpeed});
  player.animationData.push_back({walkSpeed});

  player.animations.push_back(loadSpritesIntoRectangles(numFrames, 2, 3, frameWidth, frameHeight)); // Attack
  player.animations.push_back(loadSpritesIntoRectanglesFlipped(numFrames, 2, 3, frameWidth, frameHeight));

  player.animationData.push_back({attackSpeed});
  player.animationData.push_back({attackSpeed});

  player.animations.push_back(loadSpritesIntoRectangles(numFrames, 6, 5, frameWidth, frameHeight)); // Die
  player.animations.push_back(loadSpritesIntoRectanglesFlipped(numFrames, 6, 5, frameWidth, frameHeight));

  player.animationData.push_back({dieSpeed});
  player.animationData.push_back({dieSpeed});

}

void handleTextureLoading(Game& game)
{
  Image img = LoadImage("../assets/Soldier.png");

  Texture2D spriteSheet = LoadTextureFromImage(img);

  game.textures.push_back(spriteSheet);

  ImageFlipHorizontal(&img);

  spriteSheet = LoadTextureFromImage(img);

  game.textures.push_back(spriteSheet);

  UnloadImage(img);
}

int main() {

  InitWindow(800, 800, "MY GAME");
  SetTargetFPS(60);

  Game game = {
    {},
    RIGHT
  };

  handleTextureLoading(game);

  const int numFrames = 9;
  const int frameWidth = 100; 
  const int frameHeight = 100;

  Player player = {
    {0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f},
    0.1f,
    {}, // Empty vector (will be filled by loadPlayerAnimations)
    {}, // animationData vector
    true,
    true,
    IDLE_RIGHT
  };

  float playerSpriteScale = 0.0625f;

  loadPlayerAnimations(player, numFrames, frameWidth, frameHeight);

  Vector2 playerSize = {frameWidth * playerSpriteScale, frameHeight * playerSpriteScale};

  Vector3 movementInput = {0.0f, 0.0f, 0.0f};
  bool isMoving = false;
  Vector3 currentVelocity = {0};
  float acceleration = 10.0f;
  float deceleration = 15.0f;
  float walkSpeed = 2.0f;
  float runSpeed = 4.0f;

  // setting up the camera
  Camera3D camera = {0};
  camera.position = {0.0f, 2.0f, -5.0f};
  camera.target = player.position;
  camera.up = {0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  Vector3 cameraOffset = {0.0f, 2.0f, -5.0f};
  float cameraFollowSpeed = 5.0f;

  int currentFrame = 0;
  float animTime = 0.0f;
  float frameDuration = 0.1f;

  Action previousAction = player.action;
  int previousFrameCount = 0;

  while (!WindowShouldClose()) {
        
    float deltaTime = GetFrameTime();

    movementInput = {0};
    isMoving = false;

    if(IsKeyDown(KEY_W)) movementInput.z += 1.0f;
    if(IsKeyDown(KEY_S)) movementInput.z -= 1.0f;
    if(IsKeyDown(KEY_A)) movementInput.x += 1.0f;
    if(IsKeyDown(KEY_D)) movementInput.x -= 1.0f;

    if(Vector3Length(movementInput) > 0)
    {
      movementInput = Vector3Normalize(movementInput);
      isMoving = true;

      if(fabsf(movementInput.x) > 0.1f)
      {
        player.facingRight = (movementInput.x < 0);
      }
    }

    float currentSpeed = IsKeyDown(KEY_LEFT_SHIFT) ? runSpeed : walkSpeed;
    Vector3 targetVelocity = Vector3Scale(movementInput, currentSpeed);

    currentVelocity = Vector3MoveTowards(currentVelocity, targetVelocity, isMoving ? acceleration * deltaTime : deceleration * deltaTime);

    player.position = Vector3Add(player.position, Vector3Scale(currentVelocity, deltaTime));

    if(player.action != previousAction)
    {
      float progress = animTime / player.animationData[previousAction].frameDuration;
      currentFrame = 0;
      animTime = progress * player.animationData[player.action].frameDuration;
      previousAction = player.action;
    }

    if(Vector3Length(currentVelocity) > 0.1f)
    {
      player.action = player.facingRight ? WALK_RIGHT : WALK_LEFT;
    }
    else {
      player.action = player.facingRight ? IDLE_RIGHT : IDLE_LEFT;
    }

    game.direction = player.facingRight ? RIGHT : LEFT;
    
    // update animation
    animTime += deltaTime;
    float currentFrameDuration = player.animationData[player.action].frameDuration;
    if(animTime >= currentFrameDuration)
    {
      animTime = 0;
      currentFrame = (currentFrame + 1) % player.animations[player.action].size();
      TraceLog(LOG_INFO, "CURRENT FRAME: %d | CURRENT ACTION: %d", currentFrame, player.action);
    }

    // camera follow
    Vector3 desiredCameraPos = {
      player.position.x + cameraOffset.x,
      player.position.y + cameraOffset.y,
      player.position.z + cameraOffset.z
    };

    camera.position = Vector3Lerp(camera.position, desiredCameraPos, cameraFollowSpeed * deltaTime);

    camera.target = player.position;

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

    DrawGrid(10, 1.0f);

    if(!player.animations.empty() && !player.animations[player.action].empty())
    {
  
      DrawBillboardRec(
          camera, 
          game.textures[game.direction], 
          player.animations[player.action][currentFrame], 
          player.position, 
          playerSize, 
          WHITE
      );

    }

  EndMode3D();

  EndDrawing();

}

  UnloadTexture(game.textures[0]);
  UnloadTexture(game.textures[1]);
  CloseWindow();
  return 0;
}
