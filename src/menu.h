#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <vector>
#include "game.h"

struct Button
{
  Rectangle bounds;
  const char* text;
  Color color;
  Color hoverColor;
  bool hovered;
};

struct MainMenu
{
  float buttonWidth;
  float buttonHeight;
  float startY;
  float spacing;
  std::vector<Button> buttons;
  Font font;
};

void getGame(Game& gameRef);
void initMenu(MainMenu& mainMenu);
void updateMenu(MainMenu& mainMenu, Game& game);
void drawMenu(MainMenu& mainMenu);

#endif
