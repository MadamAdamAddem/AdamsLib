#include "Rendering.hpp"
#include "Inputs.hpp"
#include "Game.hpp"


GameWindow gameWindow;
Game game;



int main()
{

  gameWindow.resizeWindow(640, 360);
  game.loadScene(testScene1());

  while(handleEvents()) 
  {  
    game.performGameLogic();
    gameWindow.renderGame();
    reduceFrames(60);
  }

  return 0;

}