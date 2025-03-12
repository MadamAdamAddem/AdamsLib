#include "headers/AdamLib.hpp"


void AdamInit()
{
  gameWindow = new GameWindow(640, 360);
  game = new Game;
  SDL_StopTextInput();
}

void AdamInit(const int screenW, const int screenH)
{
  gameWindow = new GameWindow(screenW, screenH);
  game = new Game;
  SDL_StopTextInput();
}

void AdamClose()
{
  delete gameWindow;
  delete game;
}
