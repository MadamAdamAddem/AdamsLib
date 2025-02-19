#include "Inputs.hpp"

//holds all inputs that occured in a frame
std::vector<SDL_Event> recentInputs;


bool handleEvents(SDL_Event* e)
{
  recentInputs.clear();
  while(SDL_PollEvent(e) != 0)
  {
    if(e->type == SDL_QUIT)
      return false;

    recentInputs.push_back(*e);

    if(e->type == SDL_MOUSEBUTTONUP)
    {
    }


    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
    }


    if(e->type == SDL_KEYDOWN)
    {
      if(e->key.keysym.sym == SDLK_o)
      {
        gameWindow.resizeWindow(640, 360);
      }
    }
    
  }


  return true;
}
