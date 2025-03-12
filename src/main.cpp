#include "headers/AdamLib.hpp"





int main()
{
  AdamInit(1280, 720);

  game->loadScene(newScene());

  while(handleEvents()) 
  {  
    game->performGameLogic();
    gameWindow->renderGame();
    reduceFrames(60);
  }

  AdamClose();
  return 0;
}