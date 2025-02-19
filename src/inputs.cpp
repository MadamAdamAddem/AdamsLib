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
    
  }


  return true;
}
