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

void loadPlayerAnimations(Player& player, int frameWidth, int frameHeight) {
    player.animations.clear();
    player.animations.push_back(loadSpritesIntoRectangles(6, 0, frameWidth, frameHeight)); // Idle
    player.animations.push_back(loadSpritesIntoRectangles(8, 1, frameWidth, frameHeight)); // Walk
    player.animations.push_back(loadSpritesIntoRectangles(6, 2, frameWidth, frameHeight)); // Attack
    player.animations.push_back(loadSpritesIntoRectangles(4, 6, frameWidth, frameHeight)); // Die
}

int main() {
    InitWindow(800, 800, "MY GAME");
    SetTargetFPS(60);

    // Load texture first to get dimensions
    Texture2D spriteSheet = LoadTexture("/home/chrise/programming/learning_raylib/my_game/assets/Soldier.png");
    const int frameWidth = 100;  // Hardcode if your frames are exactly 100x100
    const int frameHeight = 100; // Adjust if needed

    Player player = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        0.1f,
        {} // Empty vector (will be filled by loadPlayerAnimations)
    };

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

      // Player movement (WASD)
      if (IsKeyDown(KEY_W)) player.position.z -= player.speed;
      if (IsKeyDown(KEY_S)) player.position.z += player.speed;
      if (IsKeyDown(KEY_A)) player.position.x -= player.speed;
      if (IsKeyDown(KEY_D)) player.position.x += player.speed;

      // update animation
      animTime += deltaTime;
      if(animTime >= frameDuration)
      {
        animTime = 0;
        currentFrame = (currentFrame + 1) % 8;
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
            if (!player.animations.empty() && !player.animations[1].empty()) {
                DrawBillboardRec(
                    camera,
                    spriteSheet,
                    player.animations[1][currentFrame], // Access walk frames correctly
                    player.position,
                    Vector2{frameWidth * 0.0875f, frameHeight * 0.0875f}, // 50% scale (adjust as needed)
                    WHITE
                );
            }
        EndMode3D();
        EndDrawing();
    }

    UnloadTexture(spriteSheet);
    CloseWindow();
    return 0;
}
