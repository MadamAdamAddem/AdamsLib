#include "headers/AdamLib.hpp"

#define MOVESPEED 5


std::vector<SDL_Rect> rectVect;

/*
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
  int camX = parent->parentScene->getCamera()->x;
  int camY = parent->parentScene->getCamera()->y;

  parent->textureMap["main"]->render(parent->var["x"]-camX, parent->var["y"]-camY, gameWindow->renderer);
}



void doLogic2(Component<BasicNode*>* host)
{
  static bool keystates[4] = {false,false,false,false};


  BasicNode* parentNode = host->parent;
  SDL_Rect* camera = parentNode->parentScene->getCamera();

  
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
    camera->y -= MOVESPEED;

  if(keystates[1])
    camera->x -= MOVESPEED;  
    //parentNode->var["x"] -= MOVESPEED;

  if(keystates[2])
    camera->y += MOVESPEED;
    //parentNode->var["y"] += MOVESPEED;

  if(keystates[3])
    camera->x += MOVESPEED;



  if(camera->x < 0)
    camera->x = 0;

  if(camera->x > parentNode->parentScene->width - camera->w)
    camera->x = parentNode->parentScene->width - camera->w;

  if(camera->y < 0)
    camera->y = 0;

  if(camera->y > parentNode->parentScene->height - camera->h)
    camera->y = parentNode->parentScene->height - camera->h;
}

void doRender2(BasicNode* parent)
{
  parent->textureMap["main"]->render(parent->var["x"], parent->var["y"], gameWindow->renderer, parent->parentScene->getCamera());
}

Scene* exampleScene()
{
  Scene* newScene = new Scene(0, 0, 1280, 720);
  
  
  BasicNode* node2 = new BasicNode(doRender2, newScene);
  node2->setTexture("assets/tempbg.png");
  node2->addComponent("dick", doLogic2);
  newScene->sceneNodes.push_back(node2);
  
  BasicNode* node1 = new BasicNode(doRender, newScene);
  node1->textureMap["main"]->loadFromText("dick fuck", {0,0,0,0}, gameWindow->renderer, gameWindow->font);
  node1->addComponent("balls", doLogic);
  newScene->sceneNodes.push_back(node1);

  

  
  return newScene;
} */

void renderSideBar(BasicNode* parent)
{
  parent->textureMap["main"]->render(parent->var["x"], parent->var["y"], gameWindow->renderer);
  parent->textureMap["sceneText"]->render(parent->var["stextX"], parent->var["stextY"], gameWindow->renderer);
  parent->textureMap["nodeText"]->render(parent->var["ntextX"], parent->var["ntextY"], gameWindow->renderer);
  parent->textureMap["textureText"]->render(parent->var["ttextX"], parent->var["ttextY"], gameWindow->renderer);
}

void logicSideBar(Component<BasicNode*>* host)
{
  static SDL_Rect sceneHitbox = {1135, 25, 135, 25};
  static SDL_Rect nodeHitbox = {1135, 65, 135, 25};
  static SDL_Rect textureHitbox = {1135, 105, 135, 25};
  static SDL_Rect enterHitbox = {1080, 200, 85, 25};

  static std::string sceneString = " ";
  static std::string nodeString = " ";
  static std::string textureString = " ";
  static int currentString = 0;

  SDL_Rect mouseRect = {mouse.x, mouse.y, 10, 10};

  std::string wstring = "";
  bool backspace = false;


  for(auto keyInput : keyboardInputs)
  {
    if(keyInput.type == SDL_TEXTINPUT)
    {
      wstring += keyInput.text.text;
      continue;
    }

    if(keyInput.type == SDL_KEYDOWN)
    {
      if(keyInput.key.keysym.sym == SDLK_BACKSPACE)
      {
        backspace = true;
        break;
      }

      
    }

  }

  for(auto mouseInput : mouseInputs)
  {
    if(mouseInput.type == SDL_MOUSEBUTTONDOWN)
    {
      if(SDL_HasIntersection(&sceneHitbox, &mouseRect))
      {
        takeTextInput = true;
        currentString = 1;
      }

      else if(SDL_HasIntersection(&nodeHitbox, &mouseRect))
      {
        takeTextInput = true;
        currentString = 2;
      }

      else if(SDL_HasIntersection(&textureHitbox, &mouseRect))
      {
        takeTextInput = true;
        currentString = 3;
      }
      else if(SDL_HasIntersection(&enterHitbox, &mouseRect))
      {
        if(nodeString.length() > 1 && textureString.length() > 1)
        {
          rectVect.push_back({100,100,100,100});
          nodeString = " ";
          textureString = " ";
        }
      }

      else
      {
        takeTextInput = false;
        currentString = 0;
      }

    }
  }

  switch(currentString)
  {
    case 0:
      break;
    case 1:
      if(backspace && sceneString.length() > 1)
        sceneString.pop_back();
      else
        sceneString += wstring;

      host->parent->textureMap["sceneText"]->loadFromText(sceneString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;
    case 2:
      if(backspace && nodeString.length() > 1)
        nodeString.pop_back();
      else
        nodeString += wstring;

      host->parent->textureMap["nodeText"]->loadFromText(nodeString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;
    case 3:
      if(backspace && textureString.length() > 1)
        textureString.pop_back();
      else
        textureString += wstring;
        
      host->parent->textureMap["textureText"]->loadFromText(textureString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;
  }



}


void renderObjectPlacer(BasicNode* parent)
{
  SDL_SetRenderDrawColor(gameWindow->renderer, 0, 0, 0, 0);
  for(auto rect : rectVect)
  {
    SDL_RenderDrawRect(gameWindow->renderer, &rect);
  }
  SDL_SetRenderDrawColor(gameWindow->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void logicObjectPlacer(Component<BasicNode*>* host)
{

  SDL_Rect mouseRect = {mouse.x, mouse.y, 10, 10};
  static SDL_Rect* chosenRect = nullptr;

  for(auto mouseInput : mouseInputs)
  {
    if(mouseInput.type == SDL_MOUSEBUTTONDOWN)
    {
      for(auto& rect : rectVect)
      {
        if(SDL_HasIntersection(&rect, &mouseRect))
        {
          chosenRect = &rect;
        }
      }
    }

    if(mouseInput.type == SDL_MOUSEBUTTONUP)
      chosenRect = nullptr;
  }


  if(chosenRect != nullptr)
  {
    chosenRect->x += mouse.x - mouse.prevX;
    chosenRect->y += mouse.y - mouse.prevY;
  }



}



Scene* exampleScene()
{
  Scene* newScene = new Scene(0, 0, 1280, 720);
  
  
  BasicNode* sideBar = new BasicNode(newScene, renderSideBar);
  sideBar->setPos(980, 0);
  sideBar->setDim(300, 720);
  sideBar->setTexture("assets/sidebar.png");

  sideBar->textureMap["sceneText"] = new AdamTexture;
  sideBar->textureMap["sceneText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["stextX"] = 1135;
  sideBar->var["stextY"] = 25;

  sideBar->textureMap["nodeText"] = new AdamTexture;
  sideBar->textureMap["nodeText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["ntextX"] = 1135;
  sideBar->var["ntextY"] = 65;

  sideBar->textureMap["textureText"] = new AdamTexture;
  sideBar->textureMap["textureText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["ttextX"] = 1135;
  sideBar->var["ttextY"] = 105;

  sideBar->addComponent("sideBar", logicSideBar);
  newScene->sceneNodes.push_back(sideBar);


  BasicNode* objectPlacer = new BasicNode(newScene, renderObjectPlacer);
  objectPlacer->setPos(0,0);
  objectPlacer->setDim(0,0);
  objectPlacer->addComponent("objectPlacer", logicObjectPlacer);
  newScene->sceneNodes.push_back(objectPlacer);
  
  

  
  return newScene;
}