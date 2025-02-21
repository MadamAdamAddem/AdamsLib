#pragma once
#include "Scene.hpp"


class Game
{
public:
  Game();
  Game(Scene* newScene);
  ~Game();

  void performGameLogic();
  void loadScene(Scene* newScene);

  Scene* currentScene = nullptr;
};