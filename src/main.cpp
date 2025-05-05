#include "headers/AdamLib.hpp"





int main()
{
  AdamInit(1280, 720);

  game->loadScene(newScene());

  while(handleEvents()) 
  {  
    game->performGameLogic();
    gameWindow->renderGame();
    std::cout << reduceFrames(60) << std::endl;
  }

  AdamClose();
  return 0;
}