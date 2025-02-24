#include "headers/AdamLib.hpp"





int main()
{
  AdamInit();

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