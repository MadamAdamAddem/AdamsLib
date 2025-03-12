#include "headers/Scene.hpp"


Scene::Scene() : Scene(0, 0, 1280, 720, 0, 0, 0)
{

}

Scene::Scene(float x, float y, float w, float h, int tSize, int tammW, int tammH)
{
  tileSets.reserve(3);
  width = w; height = h;
  camera = new Camera(x, y, gameWindow->screenW, gameWindow->screenH);
}

//implement
Scene::~Scene()
{
  for(auto node : sceneNodes)
  {
    
  }

  delete camera;
}

void Scene::render()
{
  for(auto node : sceneNodes)
  {
    node->render();
  }
}

void Scene::performLogic()
{
  for(auto node : sceneNodes)
  {
    node->performLogic();
  }
}

void Scene::setCamera(float x, float y, float w, float h)
{
  camera->cameraRect = {x, y, w, h};
}

// ------------------------------------------------------------

BasicNode::BasicNode(Scene* sceneParent, void (*renderptr)(BasicNode* parent))
{
  var["x"] = 0;
  var["y"] = 0;
  var["w"] = 0;
  var["h"] = 0;
  textureMap["main"] = new AdamTexture();
  
  renderfuncptr = renderptr;
  parentScene = sceneParent;
}

BasicNode::~BasicNode()
{
  for(auto [key, component] : componentMap)
    delete component;
  componentMap.clear();

  for(auto [key, texture] : textureMap)
    delete texture;
  textureMap.clear();

  var.clear();
}

void BasicNode::render()
{
  if(renderfuncptr != nullptr)
  {
    renderfuncptr(this);
    return;
  } 
}

void BasicNode::setTexture(std::string path)
{
  textureMap["main"]->loadFromFile(path, gameWindow->renderer);
}

void BasicNode::setTexture(AdamTexture* newTexture)
{
  textureMap["main"]->replaceTexture(newTexture);
}

void BasicNode::performLogic()
{
  for(auto [key, component] : componentMap)
  {
    component->performLogic();
  }

}

void BasicNode::setPos(int x, int y)
{
  var["x"] = x;
  var["y"] = y;
}

void BasicNode::setDim(int w, int h)
{
  var["w"] = w;
  var["h"] = h;
}

void BasicNode::addComponent(std::string key, void (*newFunc)(Component<BasicNode*>* host))
{
  componentMap[key] = new Component<BasicNode*>(this, newFunc);
}

// ------------------------------------------------------------

TileNode::TileNode(Scene* sceneParent)
{
  parentScene = sceneParent;
}

TileNode::~TileNode()
{

}

void TileNode::render()
{
  //layer->getTiles()[0].ID;
  for(int i=1; i<=16; ++i)
  {
    SDL_Rect clip = {parentScene->tileSets[0].first->getTile(i)->imagePosition.x, parentScene->tileSets[0].first->getTile(i)->imagePosition.y, 25, 25};
    parentScene->tileSets[0].second->render(clip.x, clip.y, gameWindow->renderer, 1, 1, &clip);
  }
}

void TileNode::performLogic()
{
  
}

// ------------------------------------------------------------

Camera::Camera() : Camera(0, 0, gameWindow->screenW, gameWindow->screenH)
{

}

Camera::Camera(float x, float y, float w, float h)
{
  cameraRect = {x, y, w, h};
  scale = 1.0f;
}

Camera::~Camera()
{

}

// ------------------------------------------------------------



