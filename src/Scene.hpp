#pragma once
#include "Rendering.hpp"


template<typename ParentNodePtr> class Component
{
public:
  Component(ParentNodePtr _parent, void (*newFunc)(Component* host) = nullptr) {parent = _parent; funcptr = newFunc;}
  ~Component() {};

  void performLogic() {if(funcptr != nullptr) funcptr(this);}

  ParentNodePtr parent;

  void (*funcptr)(Component* host) = nullptr;
};

Scene* testScene1();

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
template <typename ParentNodePtr> friend class Component;

public:
  BasicNode();
  ~BasicNode();

  void addComponent(std::string key, void (*newFunc)(Component<BasicNode*>* host));

  void render();
  void setTexture(std::string path);

  void performLogic();

protected:
  std::map<std::string, Component<BasicNode*>*> componentMap;
  std::map<std::string, int> variables;

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

extern std::vector<SDL_Event> keyboardInputs;
extern std::vector<SDL_Event> mouseInputs;


