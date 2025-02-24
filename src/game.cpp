#include "headers/Game.hpp"

Game::Game()
{
  
}

Game::Game(Scene* newScene)
{
  loadScene(newScene);
}

//implement
Game::~Game()
{

}

void Game::performGameLogic()
{
  if(currentScene!=nullptr)
    currentScene->performLogic();
}

void Game::loadScene(Scene* newScene)
{
  if(currentScene != nullptr)
    delete currentScene;

  currentScene = newScene;
}

void Game::renderScene()
{
  if(currentScene != nullptr)
  {
    currentScene->render();
  }
}