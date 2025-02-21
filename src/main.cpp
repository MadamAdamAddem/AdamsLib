#include "Rendering.hpp"
#include "Inputs.hpp"
#include "Game.hpp"


GameWindow gameWindow;
Game game;


int main()
{

  while(handleEvents()) 
  {  
    game.performGameLogic();
    gameWindow.renderGame();
    reduceFrames(60);
  }

  return 0;

}