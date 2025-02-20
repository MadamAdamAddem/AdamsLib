#pragma once
#include "Rendering.hpp"


template<typename ParentNodePtr> class Component
{
public:
  Component(ParentNodePtr _parent, void (*newFunc)() = nullptr) {parent = _parent; funcptr = newFunc;}
  ~Component() {};

  void performLogic() {if(funcptr != nullptr) funcptr();}

  ParentNodePtr parent;

  void (*funcptr)() = nullptr;
};



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

  void addComponent(void (*newFunc)());

  void render();

  void performLogic();

  std::vector<Component<BasicNode*>> componentVector;

};

class Scene
{
public:
  Scene();
  ~Scene();

  void performLogic();

  void render();

  std::vector<SceneNode*> sceneNodes;
};

extern std::vector<SDL_Event> recentInputs;

