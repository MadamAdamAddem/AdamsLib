#include "headers/AdamLib.hpp"

#define MOVESPEED 5
#define SCREENW 1280
#define SCREENH 720



struct placedObject
{
  SDL_Rect bounds;
  std::string objName;
  std::string textureName;
  AdamTexture* texture;

  ~placedObject() {texture->free();}

}typedef placedObject;


std::vector<placedObject*> objVect;

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

void saveAndExit()
{
  FILE* fp = fopen("../newFile.cpp", "w");
  fprintf(fp, "#include \"src/headers/AdamLib.hpp\"\n\n\n");

  //stores unique obj names
  std::map<std::string, bool> objholder; 
  for(auto object : objVect)
  {
    std::string objName = object->objName;
    objholder[objName] = true;
  }

  //creates render and logic functions
  for(auto object : objholder)
  {
    std::string str = object.first;
    str[0] = std::toupper(object.first[0]);
    fprintf(fp, "void render%s(BasicNode* parent){}\n", str.c_str());
    fprintf(fp, "void logic%s(Component<BasicNode*>* host){}\n\n", str.c_str());
    fprintf(fp, "//--------------------------------------------------\n\n");
  }
  fprintf(fp, "Scene* newScene()\n{\n\tScene* newScene = new Scene(0,0,1280,720);\n");
  fprintf(fp, "\tnewScene->setCamera(0,0,1280,720);\n\n\n");


  //initializes objects
  int i = 1;
  for(auto object : objVect)
  {
    std::string str = object->objName + std::to_string(i);
    std::string funcName = object->objName;
    funcName[0] = std::toupper(object->objName[0]);

    fprintf(fp, "//%s\n{\n", str.c_str());
    fprintf(fp, "\tBasicNode* %s = new BasicNode(newScene, render%s);\n", str.c_str(), funcName.c_str());
    fprintf(fp, "\t%s->setPos(%d, %d);\n", str.c_str(), object->bounds.x, object->bounds.y);
    fprintf(fp, "\t%s->setDim(%d, %d);\n", str.c_str(), object->bounds.w, object->bounds.h);
    fprintf(fp, "\t%s->setTexture(\"assets/%s.png\");\n", str.c_str(), object->textureName.c_str());
    fprintf(fp, "\t%s->addComponent(\"%s\", logic%s);\n", str.c_str(), str.c_str(), funcName.c_str());
    fprintf(fp, "\tnewScene->sceneNodes.push_back(%s);\n", str.c_str());

    fprintf(fp, "\n}\n");
    ++i;
  }


  
  fprintf(fp, "\n\n\n\treturn newScene;\n}");

  for(auto object : objVect)
  {
    delete object;
  }
  objVect.clear();
  exit(1);
}

void renderSideBar(BasicNode* parent)
{
  parent->textureMap["main"]->render(parent->var["x"], parent->var["y"], gameWindow->renderer);
  parent->textureMap["nodeText"]->render(parent->var["ntextX"], parent->var["ntextY"], gameWindow->renderer);
  parent->textureMap["textureText"]->render(parent->var["ttextX"], parent->var["ttextY"], gameWindow->renderer);
  parent->textureMap["xcoordText"]->render(parent->var["xtextX"], parent->var["xtextY"], gameWindow->renderer);
  parent->textureMap["ycoordText"]->render(parent->var["ytextX"], parent->var["ytextY"], gameWindow->renderer);
}

void logicSideBar(Component<BasicNode*>* host)
{
  static SDL_Rect nodeHitbox = {155+SCREENW, 14, 134, 18};
  static SDL_Rect textureHitbox = {155+SCREENW, 33, 134, 18};
  static SDL_Rect xcoordHitbox = {155+SCREENW, 54, 134, 18};
  static SDL_Rect ycoordHitbox = {155+SCREENW, 78, 134, 18};

  static SDL_Rect enterHitbox = {113+SCREENW, 465, 74, 13};
  static SDL_Rect saveHitbox = {48+SCREENW, 535, 203, 13};

  static std::string nodeString = " ";
  static std::string textureString = " ";
  static std::string xcoordString = " ";
  static std::string ycoordString = " ";

  static int currentString = 0;

  SDL_Rect mouseRect = {mouse.x, mouse.y, 10, 10};

  std::string wstring = "";
  bool backspace = false;
  bool validTextInput = false;


  //take keyboard input
  for(auto keyInput : keyboardInputs)
  {
    if(keyInput.type == SDL_TEXTINPUT)
    {
      if(currentString != 3 && currentString != 4)
      {
        wstring += keyInput.text.text;
        validTextInput = true;
      }
      else if(keyInput.key.keysym.sym >= SDLK_0 && keyInput.key.keysym.sym <= SDLK_9)
      {
        wstring += keyInput.text.text;
        validTextInput = true;
      }

      continue;
    }

    if(keyInput.type == SDL_KEYDOWN)
    {
      if(keyInput.key.keysym.sym == SDLK_BACKSPACE)
      {
        backspace = true;
        validTextInput = true;
        break;
      }
    }

  }

  //take mouse input
  for(auto mouseInput : mouseInputs)
  {
    if(mouseInput.type == SDL_MOUSEBUTTONDOWN)
    {
      if(SDL_HasIntersection(&nodeHitbox, &mouseRect))
      {
        takeTextInput = true;
        currentString = 1;
      }
      else if(SDL_HasIntersection(&textureHitbox, &mouseRect))
      {
        takeTextInput = true;
        currentString = 2;
      }
      else if(SDL_HasIntersection(&xcoordHitbox, &mouseRect))
      {
        takeTextInput = true;
        currentString = 3;
      }
      else if(SDL_HasIntersection(&ycoordHitbox, &mouseRect))
      {
        takeTextInput = true;
        currentString = 4;
      }
      
      //load new object with proper attributes
      else if(SDL_HasIntersection(&enterHitbox, &mouseRect))
      {
        if(nodeString.length() > 1 && textureString.length() > 1)
        {
          placedObject* newObj = new placedObject;
          newObj->texture = new AdamTexture;
          newObj->objName = nodeString.substr(1);
          newObj->textureName = textureString.substr(1);
        
          int x = (xcoordString.length() > 1 ? std::stoi(xcoordString) : 100);
          int y = (ycoordString.length() > 1 ? std::stoi(ycoordString) : 100);

          newObj->texture->loadFromFile("assets/" + newObj->textureName, gameWindow->renderer);
          newObj->bounds = {x, y, newObj->texture->getWidth(), newObj->texture->getHeight()};
          objVect.push_back(newObj);
        }
      }
      
      //save and exit if click "complete scene"
      else if(SDL_HasIntersection(&saveHitbox, &mouseRect))
      {
        saveAndExit();
        break;
      }
      else
      {
        takeTextInput = false;
        currentString = 0;
      }

    }
  }

  if(validTextInput == false)
    return;

  //update string textures when change is made
  switch(currentString)
  {
    case 0:
      break;
    case 1:
      if(backspace && nodeString.length() > 1)
        nodeString.pop_back();
      else
        nodeString += wstring;

      nodeString = nodeString.substr(0,12);
      host->parent->textureMap["nodeText"]->loadFromText(nodeString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;
    case 2:
      if(backspace && textureString.length() > 1)
        textureString.pop_back();
      else
        textureString += wstring;
      
      textureString = textureString.substr(0,12);
      host->parent->textureMap["textureText"]->loadFromText(textureString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;
    case 3:
      if(backspace && xcoordString.length() > 1)
        xcoordString.pop_back();
      else
        xcoordString += wstring;
      
      xcoordString = xcoordString.substr(0,5);
      host->parent->textureMap["xcoordText"]->loadFromText(xcoordString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;
    case 4:
      if(backspace && ycoordString.length() > 1)
        ycoordString.pop_back();
      else
       ycoordString += wstring;
  
      ycoordString = ycoordString.substr(0,5);
      host->parent->textureMap["ycoordText"]->loadFromText(ycoordString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;
  }



}

//-----------------------------------------------------------------------------------------


void renderObjectPlacer(BasicNode* parent)
{
  Camera* cam = parent->parentScene->camera;
  parent->textureMap["main"]->render((parent->var["x"]-cam->cameraRect.x)*cam->scale, (parent->var["y"]-cam->cameraRect.y)*cam->scale, gameWindow->renderer, cam->scale);

  for(auto rect : objVect)
  {
    rect->texture->render((rect->bounds.x-cam->cameraRect.x)*cam->scale, (rect->bounds.y-cam->cameraRect.y)*cam->scale, gameWindow->renderer, cam->scale);
  }

}

SDL_Rect camAdjustedBounds(SDL_Rect* rect)
{
  Camera* cam = game->currentScene->camera;
  SDL_Rect newRect;
  newRect.x = (rect->x - cam->cameraRect.x)*cam->scale;
  newRect.y = (rect->y - cam->cameraRect.y)*cam->scale;
  newRect.w = rect->w * cam->scale;
  newRect.h = rect->h * cam->scale;

  return newRect;
}

void logicObjectPlacer(Component<BasicNode*>* host)
{
  Camera* cam = host->parent->parentScene->camera;

  SDL_Rect mouseRect = {(mouse.x-cam->cameraRect.x), (mouse.y-cam->cameraRect.y), 1, 1};
  static SDL_Rect* chosenRect = nullptr;

  for(auto mouseInput : mouseInputs)
  {
    if(mouseInput.type == SDL_MOUSEBUTTONDOWN)
    {
      //this is probably really expensive but idc
      for(auto& rect : objVect)
      {
        SDL_Rect tmp = camAdjustedBounds(&rect->bounds);
        if(SDL_HasIntersection(&tmp, &mouseRect))
        {
          chosenRect = &rect->bounds;
          break;
        }
      }
    }
    if(mouseInput.type == SDL_MOUSEWHEEL)
    {
      //gameWindow->globalRenderScale += (mouseInput.wheel.y * 0.25f);
      host->parent->parentScene->camera->scale += (mouseInput.wheel.y * 0.25f);
    }

    if(mouseInput.type == SDL_MOUSEBUTTONUP)
      chosenRect = nullptr;
  }


  if(chosenRect != nullptr)
  {
    chosenRect->x += (mouse.x - mouse.prevX)/cam->scale;
    chosenRect->y += (mouse.y - mouse.prevY)/cam->scale;
  }



}



Scene* exampleScene()
{
  Scene* newScene = new Scene(0, 0, 1580, 720);
  newScene->setCamera(0,0,1580, 720);
  

{
  BasicNode* objectPlacer = new BasicNode(newScene, renderObjectPlacer);
  objectPlacer->setPos(0,0);
  objectPlacer->setDim(1280, 720);
  objectPlacer->setTexture("assets/bigbg.png");
  objectPlacer->addComponent("objectPlacer", logicObjectPlacer);
  newScene->sceneNodes.push_back(objectPlacer);
}

//sidebar serena your husband a groupie
{
  BasicNode* sideBar = new BasicNode(newScene, renderSideBar);
  sideBar->setPos(1280, 0);
  sideBar->setDim(300, 720);
  sideBar->setTexture("assets/sidebar.png");

  sideBar->textureMap["nodeText"] = new AdamTexture;
  sideBar->textureMap["nodeText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["ntextX"] = 150+SCREENW;
  sideBar->var["ntextY"] = 9;

  sideBar->textureMap["textureText"] = new AdamTexture;
  sideBar->textureMap["textureText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["ttextX"] = 150+SCREENW;
  sideBar->var["ttextY"] = 29;

  sideBar->textureMap["xcoordText"] = new AdamTexture;
  sideBar->textureMap["xcoordText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["xtextX"] = 150+SCREENW;
  sideBar->var["xtextY"] = 51;

  sideBar->textureMap["ycoordText"] = new AdamTexture;
  sideBar->textureMap["ycoordText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["ytextX"] = 150+SCREENW;
  sideBar->var["ytextY"] = 75;

  sideBar->addComponent("sideBar", logicSideBar);
  newScene->sceneNodes.push_back(sideBar);
}

  

  
  return newScene;
}