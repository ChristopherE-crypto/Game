#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "main.h"

// Return a vector of Rectangles for a specific animation row
std::vector<Rectangle> loadSpritesIntoRectangles(int frameCount, int rowIndex, int frameWidth, int frameHeight) {

    std::vector<Rectangle> frames;
    for (int i = 0; i < frameCount; i++) {
        frames.push_back({
            (float)(i * frameWidth),
            (float)(rowIndex * frameHeight),
            (float)frameWidth,
            (float)frameHeight
        });
    }
    return frames;
}

std::vector<Rectangle> loadSpritesIntoRectanglesFlipped(int frameCount, int rowIndex, int frameWidth, int frameHeight)
{

  std::vector<Rectangle> frames;
  for(int i = frameCount - 1; i >= 1; i--)
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

void loadPlayerAnimations(Player& player, int frameWidth, int frameHeight) {

  player.animations.clear();

  player.animations.push_back(loadSpritesIntoRectangles(6, 0, frameWidth, frameHeight)); // Idle
  player.animations.push_back(loadSpritesIntoRectanglesFlipped(6, 0, frameWidth, frameHeight));

  player.animations.push_back(loadSpritesIntoRectangles(9, 1, frameWidth, frameHeight)); // walk
  player.animations.push_back(loadSpritesIntoRectanglesFlipped(9, 1, frameWidth, frameHeight));

  player.animations.push_back(loadSpritesIntoRectangles(6, 2, frameWidth, frameHeight)); // Attack
  player.animations.push_back(loadSpritesIntoRectanglesFlipped(6, 2, frameWidth, frameHeight));

  player.animations.push_back(loadSpritesIntoRectangles(4, 6, frameWidth, frameHeight)); // Die
  player.animations.push_back(loadSpritesIntoRectanglesFlipped(4, 6, frameWidth, frameHeight));
}

void handleTextureLoading(Game& game)
{
  Image img = LoadImage("/home/chrise/programming/learning_raylib/my_game/assets/Soldier.png");

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
    {}
  };

  handleTextureLoading(game);

  const int frameWidth = 100; 
  const int frameHeight = 100;

  Player player = {
    {0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f},
    0.1f,
    {}, // Empty vector (will be filled by loadPlayerAnimations)
    true
  };

  float playerSpriteScale = 0.0625f;

  loadPlayerAnimations(player, frameWidth, frameHeight);



  // Rest of your camera setup...
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

  while (!WindowShouldClose()) {
        
    float deltaTime = GetFrameTime();

    if(IsKeyDown(KEY_W))
    {
      player.position.z += player.speed;
    }

    if(IsKeyDown(KEY_S))
    {
      player.position.z -= player.speed;
    }

    if(IsKeyDown(KEY_A))
    {
      player.position.x += player.speed;
      player.facingRight = false;
    }

    if(IsKeyDown(KEY_D))
    {
      player.position.x -= player.speed;
      player.facingRight = true;
    }

    // update animation
    animTime += deltaTime;
    if(animTime >= frameDuration)
    {
      animTime = 0;
      currentFrame = (currentFrame + 1) % player.animations[3].size();
    }

    // camera follow
    Vector3 desiredCameraPos = {
      player.position.x + cameraOffset.x,
      player.position.y + cameraOffset.y,
      player.position.z + cameraOffset.z
    };

    camera.position = Vector3Lerp(camera.position, desiredCameraPos, cameraFollowSpeed * deltaTime);

    camera.target = player.position;

    Rectangle frameRect = player.animations[3][0];

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

    DrawGrid(10, 1.0f);

    if(!player.animations.empty() && !player.animations[1].empty())
    {

      if(player.facingRight)
      {
        DrawBillboardRec(
            camera,
            game.textures[0],
            player.animations[2][currentFrame],
            player.position,
            (Vector2){frameWidth * playerSpriteScale, frameHeight * playerSpriteScale},
            WHITE
        );
      }
      else {
        DrawBillboardRec(
            camera,
            game.textures[1],
            player.animations[3][currentFrame],
            player.position,
            (Vector2){frameWidth * playerSpriteScale, frameHeight * playerSpriteScale}, 
            WHITE
        );
      }
    }

  EndMode3D();

  EndDrawing();

}

  UnloadTexture(game.textures[0]);
  UnloadTexture(game.textures[1]);
  CloseWindow();
  return 0;
}
