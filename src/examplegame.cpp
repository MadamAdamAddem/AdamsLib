#include "headers/AdamLib.hpp"

#define MOVESPEED 5


void doLogic(Component<BasicNode*>* host)
{
  static bool keystates[4] = {false,false,false,false};


  BasicNode* parentNode = host->parent;

  
  for(auto keyInput : keyboardInputs)
  {
    bool keyUp = (keyInput.type == SDL_KEYUP);
    switch(keyInput.key.keysym.sym)
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
    parentNode->var["y"] -= MOVESPEED;

  if(keystates[1])
    parentNode->var["x"] -= MOVESPEED;

  if(keystates[2])
    parentNode->var["y"] += MOVESPEED;

  if(keystates[3])
    parentNode->var["x"] += MOVESPEED;


  for(auto mouseInput : mouseInputs)
  {


    switch(mouseInput.type)
    {
      case SDL_MOUSEWHEEL:
        //gameWindow->globalRenderScale += (mouseInput.wheel.y * 0.25f);
        break;

      case SDL_MOUSEBUTTONDOWN:
        break;

      case SDL_MOUSEBUTTONUP:
        break;
      default:
        break;

    }


  }
    //if(mouse.isPressed)
      //gameWindow->setViewport(mouse.x-mouse.prevX, mouse.y-mouse.prevY);

}

void doRender(BasicNode* parent)
{
  //&gameWindow->camera
  parent->textureMap["main"]->render(parent->var["x"]-gameWindow->camera.x, parent->var["y"]-gameWindow->camera.y, gameWindow->renderer);
}



void doLogic2(Component<BasicNode*>* host)
{
  static bool keystates[4] = {false,false,false,false};


  BasicNode* parentNode = host->parent;

  
  for(auto keyInput : keyboardInputs)
  {
    bool keyUp = (keyInput.type == SDL_KEYUP);
    switch(keyInput.key.keysym.sym)
    {
      case SDLK_t:
        keystates[0] = !keyUp;
        break;
      case SDLK_f:
        keystates[1] = !keyUp;
        break;
      case SDLK_g:
        keystates[2] = !keyUp;
        break;
      case SDLK_h:
        keystates[3] = !keyUp;
        break;

      default:
        break;
    }
  }

  if(keystates[0])
    gameWindow->camera.y -= MOVESPEED;

  if(keystates[1])
    gameWindow->camera.x -= MOVESPEED;  
    //parentNode->var["x"] -= MOVESPEED;

  if(keystates[2])
    gameWindow->camera.y += MOVESPEED;
    //parentNode->var["y"] += MOVESPEED;

  if(keystates[3])
    gameWindow->camera.x += MOVESPEED;
    //parentNode->var["x"] += MOVESPEED;


  if(gameWindow->camera.x < 0)
    gameWindow->camera.x = 0;

  if(gameWindow->camera.x > 1280 - gameWindow->camera.w)
    gameWindow->camera.x = 1280 - gameWindow->camera.w;

  if(gameWindow->camera.y < 0)
    gameWindow->camera.y = 0;

  if(gameWindow->camera.y > 720 - gameWindow->camera.y)
    gameWindow->camera.y = 720 - gameWindow->camera.y;
}

void doRender2(BasicNode* parent)
{
  parent->textureMap["main"]->render(parent->var["x"], parent->var["y"], gameWindow->renderer, &gameWindow->camera);
}

Scene* exampleScene()
{
  Scene* newScene = new Scene;

  BasicNode* node2 = new BasicNode(doRender2);
  node2->setTexture("tempbg.png");
  node2->addComponent("dick", doLogic2);
  newScene->sceneNodes.push_back(node2);
  
  BasicNode* node1 = new BasicNode(doRender);
  node1->setTexture("testure.png");
  node1->addComponent("balls", doLogic);
  newScene->sceneNodes.push_back(node1);

  

  
  return newScene;
}



