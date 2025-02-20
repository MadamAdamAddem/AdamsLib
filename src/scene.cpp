#include "Scene.hpp"


Scene::Scene()
{
  sceneNodes.push_back(new BasicNode);
}

//implement
Scene::~Scene()
{

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
  texture = new AdamTexture;
  texture->loadFromFile("testure.png", gameWindow.renderer);
  w = texture->getWidth();
  h = texture->getHeight();  
  
  x = 0; y = 0;
}

BasicNode::~BasicNode()
{
  texture->free();
}

void BasicNode::render()
{
  if(texture!=nullptr) texture->render(x, y, gameWindow.renderer);
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



