#include "Inputs.hpp"



bool handleEvents(SDL_Event* e)
{


  while(SDL_PollEvent(e) != 0)
  {
    if(e->type == SDL_QUIT)
      return false;


    if(e->type == SDL_MOUSEBUTTONUP)
    {
    }


    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
    }

      
    if(e->type == SDL_KEYDOWN)
    {
      if(e->key.keysym.sym == SDLK_ESCAPE)
      {}
    }
    
  }


  return true;
}
