#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class GameWindow
{
public:
  GameWindow();
  GameWindow(int SCREENW, int SCREENH);
  ~GameWindow();

  SDL_Renderer* getRenderer() {return renderer;}
  SDL_Window* getWindow() {return window;}

  void initAll(int SCREENW, int SCREENH);

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  //TTF_Font* font;
};

class adamTexture
{
public:

  adamTexture();
  adamTexture(const std::string path, SDL_Renderer* renderer);
  ~adamTexture();

  void free();

  bool loadFromFile(const std::string path, SDL_Renderer* renderer);

  //bool loadFromText(char* text, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font);

  void render(int x, int y, SDL_Renderer* renderer, double stretchFactor = 1, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point center = {0,0}, SDL_Color colorMod = {0,0,0,0});

  void setBlendMode(SDL_BlendMode blendMode);

  void setAlphaLevel(Uint8 alpha);

  void replaceTexture(adamTexture* newTexture);

  int getWidth() {return tWidth;}
  int getHeight() {return tHeight;}


private:

  SDL_Texture* texture;
  int tWidth;
  int tHeight;

};

void aSDL_Close();
//void initAll(int SCREENW, int SCREENH, SDL_Window** window, SDL_Renderer** renderer);
//void initAll(int SCREENW, int SCREENH, SDL_Window** window, SDL_Renderer** renderer, TTF_Font** font);
SDL_Renderer* ainitRenderer(SDL_Window* window, bool vsync = false);
SDL_Window* ainitWindow(std::string windowName, int SCREEN_WIDTH, int SCREEN_HEIGHT);

extern GameWindow gameWindow;