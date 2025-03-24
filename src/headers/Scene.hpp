#pragma once
#include "Rendering.hpp"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

Scene* newScene();

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

  std::unordered_map<std::string, Component<BasicNode*>*> componentMap;

  std::unordered_map<std::string, AdamTexture*> textureMap;
  std::unordered_map<std::string, float> var;

};




class Camera
{
public:
  Camera();
  Camera(float x, float y, float w, float h);
  ~Camera();


  float scale;
  SDL_FRect cameraRect;
};


class Scene
{
public:
  Scene();
  Scene(float x, float y, float w, float h, int tSize, int tammW, int tammH);
  ~Scene();

  void performLogic();
  void render();
  void setCamera(float x, float y, float w, float h);
  SDL_FRect* getCameraRect() {return &camera->cameraRect;}
  SDL_FRect  checkIfTileCollision(SDL_FRect* const obj);

  std::vector<SceneNode*> sceneNodes;
  Camera* camera;


  int width;
  int height;

  int tileSize;
  int ammTilesWide;
  int ammTilesHigh;

  std::vector<std::pair<tmx::Tileset*, AdamTexture*>> tileSets;
  std::vector<tmx::TileLayer*> tileLayers;

};

extern std::vector<SDL_Event> keyboardInputs;
extern std::vector<SDL_Event> mouseInputs;


