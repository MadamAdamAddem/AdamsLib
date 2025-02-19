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

  testComponent = new HealthComponent;
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

InputComponent::InputComponent()
{

}

InputComponent::~InputComponent()
{

}

void InputComponent::performLogic(BasicNode* parent)
{

}

// ------------------------------------------------------------

HealthComponent::HealthComponent()
{

}

HealthComponent::~HealthComponent()
{

}

void HealthComponent::performLogic(BasicNode* parent)
{

}

