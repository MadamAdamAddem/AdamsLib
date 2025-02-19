#pragma once
#include "Rendering.hpp"

class SceneNode;
class BasicNode;


class Component
{
public:
  virtual void performLogic(BasicNode* parent) = 0;
};

class TestComponent : public Component
{
public:
  TestComponent();
  ~TestComponent();

  int health;

  void performLogic(BasicNode* parent);

  void (*funcptr)();
};

/* Example Components 

class HealthComponent : public Component
{
public:
  HealthComponent();
  ~HealthComponent();

  int health;

  void performLogic(BasicNode* parent);
};

class InputComponent : public Component
{
public:
  InputComponent();
  ~InputComponent();

  
  void performLogic(BasicNode* parent);
};

 ------------------ */


class SceneNode
{
public:
  virtual void render() = 0;
  virtual void performLogic() = 0;

  int x, y, w, h;
  AdamTexture* texture = nullptr;
};

class BasicNode : public SceneNode
{
public:
  BasicNode();
  ~BasicNode();

  void render();

  void performLogic();

  Component* testComponent;

};

class Scene
{
public:
  Scene();
  ~Scene();

  void performLogic();

  void render();

  SceneNode* testNode;
};

extern std::vector<SDL_Event> recentInputs;

