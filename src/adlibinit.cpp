#include "headers/AdamLib.hpp"


void AdamInit()
{
  gameWindow = new GameWindow(640, 360);
  game = new Game;
}

void AdamClose()
{
  delete gameWindow;
  delete game;
}
