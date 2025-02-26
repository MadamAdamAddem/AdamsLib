#include "headers/Scene.hpp"


Scene::Scene() : Scene(0, 0, 1280, 720)
{

}

Scene::Scene(int x, int y, int w, int h)
{
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

  //SDL_Rect shitfuck = {100, 100, 50, 50};
  //SDL_RenderDrawRect(gameWindow->renderer, &shitfuck);
}

void Scene::performLogic()
{
  for(auto node : sceneNodes)
  {
    node->performLogic();
  }
}

void Scene::setCamera(int x, int y, int w, int h)
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

Camera::Camera() : Camera(0, 0, gameWindow->screenW, gameWindow->screenH)
{

}

Camera::Camera(int x, int y, int w, int h)
{
  cameraRect = {x, y, w, h};
}

Camera::~Camera()
{

}

// ------------------------------------------------------------



