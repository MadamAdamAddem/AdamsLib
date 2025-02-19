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

void moveTexture()
{
  for(auto input : recentInputs)
  {
    if(input.type == SDL_KEYDOWN)
    {
      if(input.key.keysym.sym == SDLK_o)
      {
        gameWindow.resizeWindow(640, 360);
      }
    }
  }

  gameWindow.lol->testNode->x += 5;
}

BasicNode::BasicNode()
{
  texture = new AdamTexture;
  texture->loadFromFile("testure.png", gameWindow.renderer);
  w = texture->getWidth();
  h = texture->getHeight();

  addComponent(moveTexture);

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



