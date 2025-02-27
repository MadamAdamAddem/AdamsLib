#pragma once
#include "Rendering.hpp"

Scene* exampleScene();

class Scene;

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

  Scene* parentScene = nullptr;
};

class BasicNode : public SceneNode
{
public:
  BasicNode(Scene* sceneParent, void(*renderptr)(BasicNode* parent) = nullptr);
  ~BasicNode();

  void addComponent(std::string key, void (*newFunc)(Component<BasicNode*>* host));

  void render();
  void setTexture(std::string path);
  void setTexture(AdamTexture* newTexture);
  void setPos(int x, int y);
  void setDim(int w, int y);

  //Don't call this directly, let the universe run its course
  void performLogic();

  void (*renderfuncptr)(BasicNode* parent);

  std::map<std::string, Component<BasicNode*>*> componentMap;

  //"main" is main texture, already initialized. call textureMap["main"]->replaceTexture or textureMap["main"]->loadFromFile to change.
  std::map<std::string, AdamTexture*> textureMap;
  std::map<std::string, float> var;

};

class Camera
{
public:
  Camera();
  Camera(int x, int y, int w, int h);
  ~Camera();


  float scale;
  SDL_Rect cameraRect;
};


class Scene
{
public:
  Scene();
  Scene(int x, int y, int w, int h);
  ~Scene();

  void performLogic();
  void render();
  void setCamera(int x, int y, int w, int h);
  SDL_Rect* getCamera() {return &camera->cameraRect;}

  std::vector<SceneNode*> sceneNodes;
  Camera* camera;

  int width;
  int height;
};

extern std::vector<SDL_Event> keyboardInputs;
extern std::vector<SDL_Event> mouseInputs;


