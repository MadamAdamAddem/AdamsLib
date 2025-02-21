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

  componentVector.clear();
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
  for(auto component : componentVector)
  {
    component.performLogic();
  }

}

void BasicNode::addComponent(void (*newFunc)())
{
  componentVector.push_back(Component<BasicNode*>(this, newFunc));
}

// ------------------------------------------------------------

// ------------------------------------------------------------



