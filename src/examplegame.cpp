#include "headers/AdamLib.hpp"



void doLogic(Component<BasicNode*>* host)
{
  static bool keystates[4] = {false,false,false,false};
  BasicNode* parentNode = host->parent;

  
  for(auto inputs : keyboardInputs)
  {
    bool keyUp = (inputs.type == SDL_KEYUP);
    switch(inputs.key.keysym.sym)
    {
      case SDLK_w:
        keystates[0] = !keyUp;
        break;
      case SDLK_a:
        keystates[1] = !keyUp;
        break;
      case SDLK_s:
        keystates[2] = !keyUp;
        break;
      case SDLK_d:
        keystates[3] = !keyUp;
        break;
      case SDLK_o:
        break;

      default:
        break;
    }
  }

  if(keystates[0])
    parentNode->var["y"] -= 1;

  if(keystates[1])
    parentNode->var["x"] -= 1;

  if(keystates[2])
    parentNode->var["y"] += 1;

  if(keystates[3])
    parentNode->var["x"] += 1;


}

void doRender(BasicNode* parent)
{
  parent->textureMap["main"]->render(parent->var["x"], parent->var["y"], gameWindow->renderer);
}

Scene* exampleScene()
{
  Scene* newScene = new Scene;
  BasicNode* newNode = new BasicNode(doRender);
  newNode->setTexture("testure.png");
  newNode->addComponent("balls", doLogic);
  newScene->sceneNodes.push_back(newNode);

  
  return newScene;
}



