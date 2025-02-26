#include "headers/AdamLib.hpp"





int main()
{
  AdamInit();

  gameWindow->resizeWindow(1780, 720);
  game->loadScene(exampleScene());

  while(handleEvents()) 
  {  
    game->performGameLogic();
    gameWindow->renderGame();
    reduceFrames(20);
  }

  AdamClose();
  return 0;
}