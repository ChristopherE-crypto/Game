#include "menu.h"
#include "constants.h"
#include <raylib.h>
#include <cstring>

//Game game;

void initMenu(MainMenu& mainMenu)
{
  mainMenu.buttonWidth = 200;
  mainMenu.buttonHeight = 50;
  mainMenu.startY = 300;
  mainMenu.spacing = 20;

  mainMenu.font = GetFontDefault();

  mainMenu.buttons.push_back({
      {(float)WINDOW_WIDTH/2 - mainMenu.buttonWidth/2, mainMenu.startY, mainMenu.buttonWidth, mainMenu.buttonHeight},
      "Start Game",
      BLUE,
      SKYBLUE,
      false
      });

  mainMenu.buttons.push_back({
      {(float)WINDOW_WIDTH/2 - mainMenu.buttonWidth/2, mainMenu.startY + mainMenu.buttonHeight + mainMenu.spacing, mainMenu.buttonWidth, mainMenu.buttonHeight},
      "Quit",
      RED,
      PINK,
      false
      });

}

void drawMenu(MainMenu& mainMenu)
{
  ClearBackground(BLACK);

  const char* title = "DUNGEONS";
  Vector2 titleSize = MeasureTextEx(mainMenu.font, title, TITLE_FONT_SIZE, 2);

  DrawTextEx(mainMenu.font, title, (Vector2){(float)WINDOW_WIDTH/2 - titleSize.x/2, 150.0f}, TITLE_FONT_SIZE, 2, WHITE);

  for(auto& button : mainMenu.buttons)
  {
    Color btnColor = button.hovered ? button.hoverColor : button.color;
    DrawRectangleRec(button.bounds, btnColor);

    Vector2 textSize = MeasureTextEx(mainMenu.font, button.text, 20, 1);
    DrawTextEx(mainMenu.font, button.text, (Vector2){button.bounds.x + button.bounds.width/2 - textSize.x/2, button.bounds.y + button.bounds.height/2 - textSize.y/2}, 20, 1, WHITE);
  }
}

void updateMenu(MainMenu& mainMenu, Game& game)
{
  Vector2 mousePos = GetMousePosition();

  for(auto& button : mainMenu.buttons)
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
        game.shouldClose = true;
      }
    }
  }
}
