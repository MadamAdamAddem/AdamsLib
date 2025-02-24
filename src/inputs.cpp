#include "headers/Inputs.hpp"

//holds all inputs that occured in a frame
std::vector<SDL_Event> keyboardInputs;
std::vector<SDL_Event> mouseInputs;

//implement
std::vector<SDL_Event> controllerInputs;


Uint32 frameTime = 0;
SDL_Event e;


bool handleEvents()
{
  frameTime = SDL_GetTicks();
  keyboardInputs.clear();
  mouseInputs.clear();


  while(SDL_PollEvent(&e) != 0)
  {
    if(e.type == SDL_QUIT)
      return false;

      

    if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
    {
      keyboardInputs.push_back(e);
      break;
    }
      
    
    if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
      mouseInputs.push_back(e);
      break;
    }
      
  }



  return true;
}



bool reduceFrames(Uint32 desiredFPS)
{
  Uint32 goalFrameTime = (1000/desiredFPS);
  frameTime = SDL_GetTicks() - frameTime;
  if(frameTime < goalFrameTime)
  {
    SDL_Delay(goalFrameTime - frameTime);
    return true;
  }
    
  return false;
}
