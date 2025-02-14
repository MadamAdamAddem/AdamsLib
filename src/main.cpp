#include "Rendering.hpp"
#include "Inputs.hpp"

SDL_Window* window;
GameWindow gameWindow;


int main()
{
  Uint32 frameTime;
  SDL_Event e;
  
  int test;
  SDL_Renderer* renderer = gameWindow.getRenderer();
  adamTexture text;
  text.loadFromFile("buttonBlank.png", renderer);
  

  while(handleEvents(&e)) {
  
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    text.render(0, 0, renderer);

    SDL_RenderPresent(renderer);

    
    frameTime = SDL_GetTicks() - frameTime;

    if(frameTime < 16)
    {
      SDL_Delay(16 - frameTime);
    }

  }

  return 0;

}