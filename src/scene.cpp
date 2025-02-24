#include "Scene.hpp"


Scene::Scene()
{

}

//implement
Scene::~Scene()
{
  for(auto node : sceneNodes)
  {
    
  }
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

// ------------------------------------------------------------

BasicNode::BasicNode()
{  
  texture = new AdamTexture();
  x = 0; y = 0;
}

BasicNode::~BasicNode()
{
  texture->free();

  componentMap.clear();
}

void BasicNode::render()
{
  if(texture!=nullptr) texture->render(x, y, gameWindow.renderer);
}

void BasicNode::setTexture(std::string path)
{
  texture->loadFromFile(path, gameWindow.renderer);
}

void BasicNode::performLogic()
{
  for(auto [key, component] : componentMap)
  {
    component->performLogic();
  }

}

void BasicNode::addComponent(std::string key, void (*newFunc)(Component<BasicNode*>* host))
{
  componentMap[key] = new Component<BasicNode*>(this, newFunc);
}

// ------------------------------------------------------------

// ------------------------------------------------------------



