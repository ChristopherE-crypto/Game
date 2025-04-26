#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>
#include <cstring>
#include "main.h"
//#include "rlights.h"

/*
 * PLAYER SPRITESHEET COMES FROM: https://zerie.itch.io/tiny-rpg-character-asset-pack
 * PINE 3D MODEL FROM: Pine tree by Poly by Google [CC-BY] (https://creativecommons.org/licenses/by/3.0/) via Poly Pizza (https://poly.pizza/m/7rTNpk6j01O)
 * ROCK 3D MODEL FROM: Rocks by Quaternius (https://poly.pizza/m/OQvi8PIZ40)
 * ROCK 3D MODEL FROM: Rock Medium by Quaternius (https://poly.pizza/m/s1OJ3bBzqc)
 * BOULDER 3D MODEL FROM: Rock Medium by Quaternius (https://poly.pizza/m/KZdEP3uUpa)
 *
 *
 */


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

void drawTreeModel(Model model, Vector3 position, float scale = 1.0f)
{
  DrawModelEx(model, position, (Vector3){0,1,0}, 0.0f, (Vector3){scale, scale, scale}, WHITE);
}

void drawRockModel(Model model, Vector3 position, float scale = 1.0f)
{
  DrawModelEx(model, position, (Vector3){0,1,0}, 0.0f, (Vector3){scale, scale, scale}, WHITE);
}

void drawBoulderModel(Model model, Vector3 position, float scale = 1.0f)
{
  DrawModelEx(model, position, (Vector3){0,1,0}, 0.0f, (Vector3){scale, scale, scale}, WHITE);
}

void populateStarterArea(Environment& env)
{
  env.trees.push_back({5.0f, 1.0f, 5.0f});
  env.trees.push_back({-3.0f, 1.0f, 8.0f});
  env.trees.push_back({7.0f, 1.0f, -4.0f});
  env.trees.push_back({3.0f, 1.0f, 5.0f});

  env.rocks.push_back({{2.0f, 0.1f, 3.0f}, 0.5f});
  env.rocks.push_back({{-2.0f, 0.1f, 4.0f}, 0.7f});

  env.boulders.push_back({{-5.0f, -0.1f, 0.0f}, 1.2f});
  env.boulders.push_back({{4.0f, -0.1f, -6.0f}, 1.5f});
}

void initMenu(Game& game)
{
  game.font = GetFontDefault();

  float buttonWidth = 200;
  float buttonHeight = 50;
  float startY = 300;
  float spacing = 20;

  game.menuButtons.push_back({
      {800/2 - buttonWidth/2, startY, buttonWidth, buttonHeight},
      "Start Game",
      BLUE,
      SKYBLUE,
      false
  });

  game.menuButtons.push_back({
      {800/2 - buttonWidth/2, startY + buttonHeight + spacing, buttonWidth, buttonHeight},
      "Quit",
      RED,
      PINK,
      false
  });

}

void drawMenu(Game& game)
{
  ClearBackground(BLACK);

  const char* title = "DUNGEONS";
  int titleFontSize = 50;
  Vector2 titleSize = MeasureTextEx(game.font, title, titleFontSize, 2);

  DrawTextEx(game.font, title, (Vector2){(float)800/2 - titleSize.x/2, 150.0f}, titleFontSize, 2, WHITE);

  for(auto& button : game.menuButtons)
  {
    Color btnColor = button.hovered ? button.hoverColor : button.color;
    DrawRectangleRec(button.bounds, btnColor);

    Vector2 textSize = MeasureTextEx(game.font, button.text, 20, 1);
    DrawTextEx(game.font, button.text, (Vector2){button.bounds.x + button.bounds.width/2 - textSize.x/2, button.bounds.y + button.bounds.height/2 - textSize.y/2}, 20, 1, WHITE);
  }
}

void updateMenu(Game& game)
{
  Vector2 mousePos = GetMousePosition();

  for(auto& button : game.menuButtons)
  {
    button.hovered = CheckCollisionPointRec(mousePos, button.bounds);

    if(button.hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      if(strcmp(button.text, "Start Game") == 0)
      {
        game.gameState = PLAYING;
      }
      else if(strcmp(button.text, "Quit") == 0)
      {
        CloseWindow();
      }
    }
  }
}

int main() {

  InitWindow(800, 800, "MY GAME");

  SetTargetFPS(60);

  Game game = {
    {},
    RIGHT,
    MENU
  };

  initMenu(game);

  Environment env;
  populateStarterArea(env);

  handleTextureLoading(game);
  
  game.treeModel = LoadModel("../assets/pine_tree.glb");
  game.rockModel = LoadModel("../assets/rock_3.glb");
  game.boulderModel = LoadModel("../assets/boulder.glb");
  

  const int numFrames = 9;
  const int frameWidth = 100; 
  const int frameHeight = 100;

  Player player = {
    {0.0f, 0.5f, 0.0f},
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

  float cameraFollowSpeed = 5.0f;

  float cameraRotationAngle = 0.0f;
  float cameraRotationSpeed = 1.5f;
  float cameraDistance = 5.0f;
  float cameraHeight = 2.0f;
  float minCameraDistance = 3.0f;
  float maxCameraDistance = 20.0f;
  float zoomSpeed = 75.0f;

  Vector3 cameraOffset = {
    sinf(cameraRotationAngle) * cameraDistance,
    cameraHeight,
    cosf(cameraRotationAngle) * cameraDistance
  };

  int currentFrame = 0;
  float animTime = 0.0f;
  float frameDuration = 0.1f;

  Action previousAction = player.action;
  int previousFrameCount = 0;
 
  while (!WindowShouldClose())
  {

    switch(game.gameState)
    {
      case MENU:
        updateMenu(game);
        BeginDrawing();
        drawMenu(game);
        EndDrawing();
        break;

      case PLAYING: {
        float deltaTime = GetFrameTime();

        Vector3 cameraForward = Vector3Normalize((Vector3){sinf(cameraRotationAngle), 0, cosf(cameraRotationAngle)});

        movementInput = {0};
        isMoving = false;

        if(IsKeyDown(KEY_S)) movementInput = Vector3Add(movementInput, cameraForward);
        if(IsKeyDown(KEY_W)) movementInput = Vector3Add(movementInput, Vector3Negate(cameraForward));
        if(IsKeyDown(KEY_A)) movementInput = Vector3Add(movementInput, (Vector3){-cameraForward.z, 0, cameraForward.x});
        if(IsKeyDown(KEY_D)) movementInput = Vector3Add(movementInput, (Vector3){cameraForward.z, 0, -cameraForward.x});

        if(IsKeyDown(KEY_Q))
        {
          cameraRotationAngle -= cameraRotationSpeed * deltaTime;
        }
        if(IsKeyDown(KEY_E))
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

        if(Vector3Length(movementInput) > 0)
        {
          movementInput = Vector3Normalize(movementInput);
          isMoving = true;

          if(IsKeyDown(KEY_D)) player.facingRight = true;
          if(IsKeyDown(KEY_A)) player.facingRight = false;
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

        cameraOffset = {
          sinf(cameraRotationAngle) * cameraDistance,
          cameraHeight,
          cosf(cameraRotationAngle) * cameraDistance
        };

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
        ClearBackground(SKYBLUE);

        BeginMode3D(camera);

        DrawGrid(10, 1.0f);

        DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){50,50}, DARKGREEN);

        for(auto& treePos : env.trees)
        {
          drawTreeModel(game.treeModel, treePos);
        }

        for(auto& rockPos : env.rocks)
        {
          drawRockModel(game.rockModel, rockPos.first);
        }

        for(auto& boulderPos : env.boulders)
        {
          drawBoulderModel(game.boulderModel, boulderPos.first);
        }

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

        break;
    }

      case PAUSED:
        break;

      case GAME_OVER:
        break;


    }

}
  UnloadModel(game.treeModel);
  UnloadModel(game.rockModel);
  UnloadModel(game.boulderModel);
  UnloadTexture(game.textures[0]);
  UnloadTexture(game.textures[1]);
  CloseWindow();
  return 0;
}
