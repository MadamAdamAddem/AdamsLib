#include "headers/Rendering.hpp"
#include "headers/Scene.hpp"
#include "headers/Game.hpp"

#define SCREENW 1280
#define SCREENH 720

GameWindow* gameWindow;
Game* game;

AdamTexture::AdamTexture()
{
  texture = nullptr;
  tWidth = 0;
  tHeight = 0;
}

AdamTexture::AdamTexture(const std::string path, SDL_Renderer* renderer)
{
  texture = nullptr;
  tWidth = 0;
  tHeight = 0;
  loadFromFile(path, renderer);
}

AdamTexture::~AdamTexture()
{
  free();
}

void AdamTexture::free()
{
  if(texture == nullptr) return;

  SDL_DestroyTexture(texture);
  tWidth = 0;
  tHeight = 0;
}

bool AdamTexture::loadFromFile(const std::string path, SDL_Renderer* renderer)
{
  free();


  texture = IMG_LoadTexture(renderer, path.c_str());
  if(texture == nullptr)
  {
    std::cout << "Failed to load texture from file!" << std::endl;
    return false;
  }
    

  SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
  SDL_QueryTexture(texture, NULL, NULL, &tWidth, &tHeight);
  

  
  return true;

}

bool AdamTexture::loadFromText(const std::string text, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font)
{
  free();
  
  SDL_Surface* tmpSurface = TTF_RenderUTF8_Blended(font, text.c_str(), textColor);

  if(tmpSurface == NULL)
  {
      std::cout << "Text failure\n" << std::endl;
      return false;
  }

  texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
  if(texture == NULL)
  {
      std::cout << "Text texture failure\n" << std::endl;
      return false;
  }

  tWidth = tmpSurface->w;
  tHeight = tmpSurface->h;

  SDL_FreeSurface(tmpSurface);
  SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
  
  return true;
}

void AdamTexture::render(SDL_Renderer* renderer, SDL_Rect rSpace, SDL_Rect* clip, SDL_Color colorMod, double angle, SDL_Point center)
{
  if(texture == nullptr || renderer == nullptr)
  {
    std::cout << "Failed to render texture!" << std::endl;
    return;
  }

  
  if(clip != nullptr)
  {
    rSpace.w = clip->w;
    rSpace.h = clip->h;
  }

  if(colorMod.a != 0)
    SDL_SetTextureColorMod(texture, colorMod.r, colorMod.g, colorMod.b);
  
  SDL_RenderCopyEx(renderer, texture, clip, &rSpace, angle, &center, SDL_FLIP_NONE);
}

void AdamTexture::setBlendMode(SDL_BlendMode blendMode)
{
  SDL_SetTextureBlendMode(texture, blendMode);
}

void AdamTexture::setAlphaLevel(Uint8 alpha)
{
  SDL_SetTextureAlphaMod(texture, alpha);
}

void AdamTexture::replaceTexture(AdamTexture* newTexture)
{
  texture = newTexture->texture;
  tWidth = newTexture->tWidth;
  tHeight = newTexture->tHeight;
}

// ------------------------------------------------------------

GameWindow::GameWindow() : GameWindow(640, 360)
{
  
}

GameWindow::GameWindow(int newW, int newH)
{
  window = nullptr;
  renderer = nullptr;
  screenW = newW;
  screenH = newH;
  globalRenderScale = screenW / SCREENW;
  viewport = {0,0,newW,newH};

  initAll();
}

GameWindow::~GameWindow()
{
  aSDL_Close();
}

void GameWindow::initAll()
{ 
  std::string fontString = "../src/assets/arial.ttf";

  window = ainitWindow();
  if(window == nullptr)
    exit(1);

  renderer = ainitRenderer();
  if(renderer == nullptr)
    exit(1);

  TTF_SetFontHinting(font, TTF_HINTING_NORMAL);
  font = TTF_OpenFont(fontString.c_str(), 18);
  if(font == nullptr)
    exit(1);
}

void GameWindow::resizeWindow(int newW, int newH)
{
  screenW = newW;
  screenH = newH;
  globalRenderScale = newW / SCREENW;
  viewport = {0,0,newW,newH};
  SDL_SetWindowSize(window, screenW, screenH);
}

void GameWindow::renderGame()
{

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
  //SDL_RenderSetViewport(renderer, &viewport);
  SDL_RenderSetScale(renderer, globalRenderScale, globalRenderScale);

  game->renderScene();
  SDL_RenderPresent(renderer);
  
  return;
}

void GameWindow::setViewport(int x, int y)
{
  viewport.x += x;
  viewport.y += y;
}

//Initiates SDL, SDL_image, and SDL_TTF with a window
SDL_Window* GameWindow::ainitWindow()
{

  SDL_Window* tempWindow = nullptr;
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL initialization failed\n");
    return nullptr;
  }
  

  //nearest texture filtering
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
	{
		printf("Linear texture filtering not enabled!\n");
		return nullptr;
	}

  tempWindow = SDL_CreateWindow("Test Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN);

  if(tempWindow == nullptr)
  {
    printf("Window initialization failed\n");
    return nullptr;
  } 
  int imgFlags = IMG_INIT_PNG;

  if(!(IMG_Init(imgFlags) & imgFlags))
  {
    printf("SDL_image initialization failed\n");
    return nullptr;
  }

  //Initialize SDL_ttf
  if(TTF_Init() == -1)
  {
    printf( "SDL_ttf initialization failed\n");
    return NULL;
  } 
    

    return tempWindow;
}

//Initiates a renderer with vsync optional
SDL_Renderer* GameWindow::ainitRenderer(bool vsync)
{
  SDL_Renderer* tempRenderer = nullptr;
  tempRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | ((vsync) ? SDL_RENDERER_PRESENTVSYNC : 0));

  if(tempRenderer == nullptr)
  {
    std::cout << "Renderer Error" << SDL_GetError() << std::endl;
    return nullptr;
  }

  SDL_SetRenderDrawColor(tempRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  //SDL_RenderSetLogicalSize(tempRenderer, 640, 360);
  return tempRenderer;
}

// ------------------------------------------------------------






void aSDL_Close()
{
  SDL_DestroyWindow(gameWindow->getWindow());
  SDL_DestroyRenderer(gameWindow->getRenderer());

  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
}





