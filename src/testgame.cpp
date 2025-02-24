#include "AdamLib.hpp"



void doLogic(Component<BasicNode*>* host)
{
  BasicNode* parentNode = host->parent;
  
  if(keyboardInputs.empty())
    return;

  switch(keyboardInputs.front().key.keysym.sym)
  {
    case SDLK_w:
      parentNode->y -= 5;
      break;
    case SDLK_a:
      parentNode->x -= 5;
      break;
    case SDLK_s:
      parentNode->y += 5;
      break;
    case SDLK_d:
      parentNode->x += 5;
      break;
    default:
      break;
  }

  if(keyboardInputs.size() < 2)
    return;

  switch(keyboardInputs.at(1).key.keysym.sym)
  {
    case SDLK_w:
      parentNode->y -= 5;
      break;
    case SDLK_a:
      parentNode->x -= 5;
      break;
    case SDLK_s:
      parentNode->y += 5;
      break;
    case SDLK_d:
      parentNode->x += 5;
      break;
    default:
      break;
  }
}

Scene* testScene1()
{
  Scene* newScene = new Scene;
  BasicNode* newNode = new BasicNode;
  newNode->setTexture("testure.png");
  newNode->addComponent("balls", doLogic);
  newScene->sceneNodes.push_back(newNode);

  return newScene;
}



