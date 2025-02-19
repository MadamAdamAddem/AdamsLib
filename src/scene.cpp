#include "Scene.hpp"


Scene::Scene()
{
  testNode = new BasicNode;
}

Scene::~Scene()
{

}

void Scene::render()
{
  testNode->render();
}

void Scene::performLogic()
{
  testNode->performLogic();
}

// ------------------------------------------------------------

BasicNode::BasicNode()
{
  texture = new AdamTexture;
  texture->loadFromFile("testure.png", gameWindow.renderer);

  testComponent = new TestComponent;
}

BasicNode::~BasicNode()
{
  texture->free();
}


void BasicNode::render()
{
  if(texture!=nullptr) texture->render(0, 0, gameWindow.renderer);
}

void BasicNode::performLogic()
{
  testComponent->performLogic(this);
}

// ------------------------------------------------------------


// ------------------------------------------------------------

void funcptrtest()
{
  std::cout << "a function pointer has been used" << std::endl;
}

TestComponent::TestComponent()
{
  funcptr = funcptrtest;
}

TestComponent::~TestComponent()
{

}

void TestComponent::performLogic(BasicNode* parent)
{
  funcptr();
}

