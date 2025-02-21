#include "Inputs.hpp"

//holds all inputs that occured in a frame
std::vector<SDL_Event> recentInputs;
Uint32 frameTime = 0;
SDL_Event e;

bool handleEvents()
{
  frameTime = SDL_GetTicks();
  recentInputs.clear();

  while(SDL_PollEvent(&e) != 0)
  {
    if(e.type == SDL_QUIT)
      return false;

    recentInputs.push_back(e);
  }



  return true;
}



bool reduceFrames(Uint32 desiredFPS)
{
  Uint32 goalFrameTime = (1/desiredFPS)*1000;
  frameTime = SDL_GetTicks() - frameTime;
  if(frameTime < goalFrameTime)
  {
    SDL_Delay(goalFrameTime - frameTime);
    return true;
  }
    
  return false;
}
