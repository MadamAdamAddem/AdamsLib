#include "headers/AdamLib.hpp"





int main()
{
  AdamInit();

  gameWindow->resizeWindow(1280, 720);
  game->loadScene(exampleScene());

  while(handleEvents()) 
  {  
    game->performGameLogic();
    gameWindow->renderGame();
    reduceFrames(60);
  }

  AdamClose();
  return 0;
}