#pragma once
#include "Rendering.hpp"

Scene* exampleScene();

template<typename ParentNodePtr> class Component
{
public:
  Component(ParentNodePtr _parent, void (*newFunc)(Component* host) = nullptr) {parent = _parent; funcptr = newFunc;}
  ~Component() {};

  //Don't call this directly, let the universe run its course
  void performLogic() {if(funcptr != nullptr) funcptr(this);}

  ParentNodePtr parent;

  void (*funcptr)(Component* host) = nullptr;
};



class SceneNode
{
public:
  virtual void render() = 0;
  virtual void performLogic() = 0;
};

class BasicNode : public SceneNode
{
public:
  BasicNode();
  BasicNode(void (*renderptr)(BasicNode* parent));
  ~BasicNode();

  void addComponent(std::string key, void (*newFunc)(Component<BasicNode*>* host));

  void render();
  void setTexture(std::string path);
  void setTexture(AdamTexture* newTexture);

  //Don't call this directly, let the universe run its course
  void performLogic();

  void (*renderfuncptr)(BasicNode* parent);

  std::map<std::string, Component<BasicNode*>*> componentMap;

  //"main" is main texture, already initialized. call textureMap["main"]->replaceTexture or textureMap["main"]->loadFromFile to change.
  std::map<std::string, AdamTexture*> textureMap;
  std::map<std::string, int> var;

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


