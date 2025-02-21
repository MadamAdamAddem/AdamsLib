#include "Rendering.hpp"
#include "Inputs.hpp"
#include "Game.hpp"

const float FPS = 60;
const int GOALFRAMETIME = (1/FPS)*1000;

GameWindow gameWindow;
Game game;


int main()
{
  Uint32 frameTime = 0;
  SDL_Event e;
  
  int i = 0;

  while(handleEvents(&e)) {

    frameTime = SDL_GetTicks();
  
    game.performGameLogic();
    gameWindow.renderGame();
    






    frameTime = SDL_GetTicks() - frameTime;
    if(frameTime < GOALFRAMETIME) SDL_Delay(GOALFRAMETIME - frameTime);
  }

  return 0;

}