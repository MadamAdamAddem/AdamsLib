#include "headers/AdamLib.hpp"
#include <list>

#define MOVESPEED 5
#define SCREENW 1280
#define SCREENH 720



typedef struct placedObject
{
  SDL_FRect bounds;
  float wStretch = 1;
  float hStretch = 1;
  bool customDim = false;
  std::string objName;
  std::string textureName;
  AdamTexture* texture;

  ~placedObject() {texture->free();}

}placedObject;



std::list<placedObject*> objList;
static placedObject* selectedObj = nullptr;
static bool isHoldingObj = false;

void saveAndExit()
{

  FILE* fp = fopen("../newFile.cpp", "w");
  fprintf(fp, "#include \"src/headers/AdamLib.hpp\"\n\n\n");

  //stores unique obj names
  std::unordered_map<std::string, int> objholder; 
  for(auto object : objList)
  {
    std::string objName = object->objName;
    objholder[objName] = 1;
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
  for(auto object : objList)
  {
    std::string str = object->objName + std::to_string(objholder[object->objName]++);
    std::string funcName = object->objName;
    funcName[0] = std::toupper(object->objName[0]);

    fprintf(fp, "//%s\n{\n", str.c_str());
    fprintf(fp, "\tBasicNode* %s = new BasicNode(newScene, render%s);\n", str.c_str(), funcName.c_str());
    fprintf(fp, "\t%s->setPos(%.0f, %.0f);\n", str.c_str(), object->bounds.x, object->bounds.y);
    fprintf(fp, "\t%s->setDim(%.0f, %.0f);\n", str.c_str(), object->bounds.w, object->bounds.h);
    fprintf(fp, "\t%s->setTexture(\"assets/%s.png\");\n", str.c_str(), object->textureName.c_str());
    fprintf(fp, "\t%s->addComponent(\"%s\", logic%s);\n", str.c_str(), str.c_str(), funcName.c_str());
    fprintf(fp, "\tnewScene->sceneNodes.push_back(%s);\n", str.c_str());

    fprintf(fp, "\n}\n");
  }


  
  fprintf(fp, "\n\n\n\treturn newScene;\n}");

  for(auto object : objList)
  {
    delete object;
  }
  objList.clear();
  exit(1);
}

void renderSideBar(BasicNode* parent)
{
  parent->textureMap["main"]->render(parent->var["x"], parent->var["y"], gameWindow->renderer);
  parent->textureMap["nodeText"]->render(parent->var["ntextX"], parent->var["ntextY"], gameWindow->renderer);
  parent->textureMap["textureText"]->render(parent->var["ttextX"], parent->var["ttextY"], gameWindow->renderer);
  parent->textureMap["xcoordText"]->render(parent->var["xtextX"], parent->var["xtextY"], gameWindow->renderer);
  parent->textureMap["ycoordText"]->render(parent->var["ytextX"], parent->var["ytextY"], gameWindow->renderer);
  parent->textureMap["heightText"]->render(parent->var["htextX"], parent->var["htextY"], gameWindow->renderer);
  parent->textureMap["widthText"]->render(parent->var["wtextX"], parent->var["wtextY"], gameWindow->renderer);
  parent->textureMap["heightwidth"]->render(parent->var["hwtextX"], parent->var["hwtextY"], gameWindow->renderer);

}

void logicSideBar(Component<BasicNode*>* host)
{
  static SDL_FRect nodeHitbox = {155+SCREENW, 14, 134, 18};
  static SDL_FRect textureHitbox = {155+SCREENW, 45, 134, 18};
  static SDL_FRect xcoordHitbox = {155+SCREENW, 81, 134, 18};
  static SDL_FRect ycoordHitbox = {155+SCREENW, 120, 134, 18};
  static SDL_FRect heightHitbox = {155+SCREENW, 159, 134, 18};
  static SDL_FRect widthHitbox = {155+SCREENW, 197, 134, 18};
  static SDL_FRect setCustomDimHitbox = {12+SCREENW, 234, 134, 31};

  static SDL_FRect enterHitbox = {113+SCREENW, 465, 74, 13};
  static SDL_FRect saveHitbox = {48+SCREENW, 535, 203, 13};

  static std::string nodeString = " ";
  static std::string textureString = " ";
  static std::string xcoordString = " ";
  static std::string ycoordString = " ";
  static std::string heightString = " ";
  static std::string widthString = " ";

  static int updateString = 0;
  static bool enableCustomDim = false;

  SDL_FRect mouseRect = {mouse.x-5, mouse.y-5, 10, 10};
  BasicNode* self = host->parent;

  std::string wstring = "";
  bool backspace = false;
  bool validTextInput = false;


  #define  NOUPDATE 0
  #define  UPDATENODE 1
  #define  UPDATETEXTURE 2
  #define  UPDATEXCOORD 3
  #define  UPDATEYCOORD 4
  #define  UPDATEHEIGHT 5
  #define  UPDATEWIDTH 6
  #define  UPDATEALL 7

  static placedObject* lastObj = nullptr;
  if(selectedObj != nullptr)
  {
    enableCustomDim = selectedObj->customDim;
    if(selectedObj != lastObj)
    {
      self->textureMap["heightwidth"]->setAlphaLevel(255*enableCustomDim);

      self->textureMap["nodeText"]->loadFromText(selectedObj->objName, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      self->textureMap["textureText"]->loadFromText(selectedObj->textureName, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      self->textureMap["xcoordText"]->loadFromText(std::to_string((int)selectedObj->bounds.x), {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      self->textureMap["ycoordText"]->loadFromText(std::to_string((int)selectedObj->bounds.y), {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      self->textureMap["heightText"]->loadFromText(std::to_string((int)selectedObj->bounds.h), {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      self->textureMap["widthText"]->loadFromText(std::to_string((int)selectedObj->bounds.w), {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      self->textureMap["heightText"]->setAlphaLevel(255*enableCustomDim);
      self->textureMap["widthText"]->setAlphaLevel(255*enableCustomDim);

      lastObj = selectedObj;
    }
  }
  else
    lastObj = nullptr;
    

  //take keyboard input
  for(auto& keyInput : keyboardInputs)
  {
    if(keyInput.type == SDL_TEXTINPUT)
    {
      if(updateString < 3)
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

      else if(keyInput.key.keysym.sym == SDLK_TAB && updateString != 0)
      {
        updateString = (updateString + 1) % ((enableCustomDim*2)+5);
        validTextInput = true;
        break;
      }
    }

  }

  //take mouse input
  for(auto& mouseInput : mouseInputs)
  {
    if(mouseInput.type == SDL_MOUSEBUTTONDOWN)
    {
      if(mouseInput.button.button != SDL_BUTTON_LEFT)
        continue;

      if(SDL_HasIntersectionF(&nodeHitbox, &mouseRect))
      {
        takeTextInput = true;
        updateString = UPDATENODE;
      }
      else if(SDL_HasIntersectionF(&textureHitbox, &mouseRect))
      {
        takeTextInput = true;
        updateString = UPDATETEXTURE;
      }
      else if(SDL_HasIntersectionF(&xcoordHitbox, &mouseRect))
      {
        takeTextInput = true;
        updateString = UPDATEXCOORD;
      }
      else if(SDL_HasIntersectionF(&ycoordHitbox, &mouseRect))
      {
        takeTextInput = true;
        updateString = UPDATEYCOORD;
      }
      else if(enableCustomDim && SDL_HasIntersectionF(&heightHitbox, &mouseRect))
      {
        takeTextInput = true;
        updateString = UPDATEHEIGHT;
      }
      else if(enableCustomDim && SDL_HasIntersectionF(&widthHitbox, &mouseRect))
      {
        takeTextInput = true;
        updateString = UPDATEWIDTH;
      }
      else if(SDL_HasIntersectionF(&setCustomDimHitbox, &mouseRect))
      { 
        enableCustomDim = !enableCustomDim;
        self->textureMap["heightwidth"]->setAlphaLevel(255*enableCustomDim);
        self->textureMap["heightText"]->setAlphaLevel(255*enableCustomDim);
        self->textureMap["widthText"]->setAlphaLevel(255*enableCustomDim);

        if(selectedObj == nullptr)
          continue;

        selectedObj->customDim = enableCustomDim;
        if(enableCustomDim == false)
        {
          selectedObj->bounds.w = selectedObj->texture->getWidth();
          selectedObj->bounds.h = selectedObj->texture->getHeight();

          selectedObj->wStretch = 1;
          selectedObj->hStretch = 1;
          updateString = updateString | UPDATEHEIGHT | UPDATEWIDTH;
        }
        else
        {
          /*std::string tmpWidth = std::to_string((int)selectedObj->bounds.w);
          std::string tmpHeight = std::to_string((int)selectedObj->bounds.h);
          self->textureMap["widthText"]->loadFromText(tmpWidth, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
          self->textureMap["heightText"]->loadFromText(tmpHeight, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);*/
        }
      }
      
      //create new object or modify existing w/ attributes
      else if(SDL_HasIntersectionF(&enterHitbox, &mouseRect))
      {
        if(!(nodeString.length() > 1) || !(textureString.length() > 1))
          continue;

        placedObject* newObj;
        if(selectedObj == nullptr)
        {
          newObj = new placedObject;
          newObj->texture = new AdamTexture;
          objList.push_back(newObj);
          selectedObj = newObj;
        }
        else
          newObj = selectedObj;

        newObj->objName = nodeString.substr(1);
        newObj->textureName = textureString.substr(1);
        newObj->texture->loadFromFile("assets/" + newObj->textureName, gameWindow->renderer);
        float x = (xcoordString.length() > 1 ? std::stof(xcoordString) : 100.0f);
        float y = (ycoordString.length() > 1 ? std::stof(ycoordString) : 100.0f);
        float w = ((enableCustomDim && widthString.length() > 1) ? std::stof(widthString) : (float)newObj->texture->getWidth());
        float h = ((enableCustomDim && heightString.length() > 1) ? std::stof(heightString) : (float)newObj->texture->getHeight());


        newObj->bounds = {x, y, w, h};
        newObj->customDim = enableCustomDim;
        newObj->wStretch = w/(float)newObj->texture->getWidth();
        newObj->hStretch = h/(float)newObj->texture->getHeight();
      }
      
      //save and exit if click "complete scene"
      else if(SDL_HasIntersectionF(&saveHitbox, &mouseRect))
      {
        saveAndExit();
        break;
      }
      else
      {
        takeTextInput = false;
        updateString = NOUPDATE;
      }

    }

    if(mouseInput.type == SDL_MOUSEBUTTONUP)
    {
      if(mouseInput.button.button != SDL_BUTTON_LEFT || selectedObj == nullptr)
        continue;

      self->textureMap["xcoordText"]->loadFromText(std::to_string((int)selectedObj->bounds.x), {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      self->textureMap["ycoordText"]->loadFromText(std::to_string((int)selectedObj->bounds.y), {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      
    }
  }

  if(validTextInput == false)
    return;

  //update string textures when change is made
  switch(updateString)
  {
    case 0:
      break;
    case 1:
      if(backspace && nodeString.length() > 1)
        nodeString.pop_back();
      else
        nodeString += wstring;

      nodeString = nodeString.substr(0,12);
      self->textureMap["nodeText"]->loadFromText(nodeString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;

    case 2:
      if(backspace && textureString.length() > 1)
        textureString.pop_back();
      else
        textureString += wstring;
      
      textureString = textureString.substr(0,12);
      self->textureMap["textureText"]->loadFromText(textureString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;

    case 3:
      if(backspace && xcoordString.length() > 1)
        xcoordString.pop_back();
      else
        xcoordString += wstring;
      
      xcoordString = xcoordString.substr(0,5);
      self->textureMap["xcoordText"]->loadFromText(xcoordString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;

    case 4:
      if(backspace && ycoordString.length() > 1)
        ycoordString.pop_back();
      else
       ycoordString += wstring;
  
      ycoordString = ycoordString.substr(0,5);
      self->textureMap["ycoordText"]->loadFromText(ycoordString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;

    case 5:

      if(backspace && heightString.length() > 1)
        heightString.pop_back();
      else
        heightString += wstring;
  
      heightString = heightString.substr(0,5);
      self->textureMap["heightText"]->loadFromText(heightString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;

    case 6:

      if(backspace && widthString.length() > 1)
        widthString.pop_back();
      else
        widthString += wstring;
  
      widthString = widthString.substr(0,5);
      self->textureMap["widthText"]->loadFromText(widthString, {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
      break;
  }
  
}

//-----------------------------------------------------------------------------------------

SDL_FRect camAdjustedBounds(SDL_FRect* rect)
{
  Camera* cam = game->currentScene->camera;
  SDL_FRect newRect;
  newRect.x = (rect->x - cam->cameraRect.x)*cam->scale;
  newRect.y = (rect->y - cam->cameraRect.y)*cam->scale;
  newRect.w = rect->w * cam->scale;
  newRect.h = rect->h * cam->scale;

  return newRect;
}

placedObject* returnSelectedObject(SDL_FRect* mouseRect)
{
  for(auto& rect : objList)
  {
    SDL_FRect tmp = camAdjustedBounds(&rect->bounds);
    if(SDL_HasIntersectionF(&tmp, mouseRect))
    {
      return rect;
    }
  }

  return nullptr;
}

void renderObjectPlacer(BasicNode* parent)
{
  Camera* cam = parent->parentScene->camera;
  parent->textureMap["main"]->render((parent->var["x"]-cam->cameraRect.x)*cam->scale, (parent->var["y"]-cam->cameraRect.y)*cam->scale, gameWindow->renderer, cam->scale, cam->scale);

  for(auto& rect : objList)
  {
    rect->texture->render((rect->bounds.x-cam->cameraRect.x)*cam->scale, (rect->bounds.y-cam->cameraRect.y)*cam->scale, gameWindow->renderer, cam->scale*rect->wStretch, cam->scale*rect->hStretch);
  }

}

void logicObjectPlacer(Component<BasicNode*>* host)
{
  BasicNode* self = host->parent;
  Camera* cam = self->parentScene->camera;

  SDL_FRect mouseRect = {(mouse.x-5), (mouse.y-5), 10, 10};
  static bool moveCamera = false;

  for(auto& mouseInput : mouseInputs)
  {
    if(mouseInput.type == SDL_MOUSEBUTTONDOWN)
    {
      if(mouseInput.button.button == SDL_BUTTON_RIGHT)
        continue;

      SDL_FRect tmp = {0, 0, SCREENW, SCREENH};
      if(mouseInput.button.button == SDL_BUTTON_LEFT)
      {
        if(SDL_HasIntersectionF(&tmp, &mouseRect))
        {
          selectedObj = returnSelectedObject(&mouseRect);
          moveCamera = false;
          isHoldingObj = true;
        }
        continue;
      }
      

      
      if(SDL_HasIntersectionF(&tmp, &mouseRect))
      {
        moveCamera = true;
        isHoldingObj = false;
        selectedObj = nullptr;
      }
        
    }

    if(mouseInput.type == SDL_MOUSEWHEEL)
    { //so ugly lmao
      self->parentScene->camera->scale += (mouseInput.wheel.y * 0.25f);
    }

    if(mouseInput.type == SDL_MOUSEBUTTONUP)
    {
      switch(mouseInput.button.button)
      {
        case SDL_BUTTON_LEFT:
          isHoldingObj = false;
        case SDL_BUTTON_MIDDLE:
          moveCamera = false;
      }
    }
  }
  
  for(auto& keyInput : keyboardInputs)
  {
    if(keyInput.type == SDL_KEYDOWN)
    {
      if((keyInput.key.keysym.sym == SDLK_DELETE || keyInput.key.keysym.sym == SDLK_BACKSPACE) && selectedObj != nullptr)
      {
        objList.remove(selectedObj);
        delete selectedObj;
        selectedObj = nullptr;
      }
    }
  }



  if(moveCamera)
  {
    SDL_FRect* tmp = self->parentScene->getCameraRect();
    tmp->x -= (mouse.x - mouse.prevX)/cam->scale;
    tmp->y -= (mouse.y - mouse.prevY)/cam->scale;
  }

  else if(selectedObj != nullptr && isHoldingObj)
  {
    selectedObj->bounds.x += (mouse.x - mouse.prevX)/cam->scale;
    selectedObj->bounds.y += (mouse.y - mouse.prevY)/cam->scale;
    objList.remove(selectedObj);
    objList.push_back(selectedObj);
  }


}



Scene* exampleScene()
{
  Scene* newScene = new Scene(0, 0, 1580, 720);
  newScene->setCamera(0,0,1580, 720);
  
//objectPlacer
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
  sideBar->var["ntextY"] = 10;

  sideBar->textureMap["textureText"] = new AdamTexture;
  sideBar->textureMap["textureText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["ttextX"] = 150+SCREENW;
  sideBar->var["ttextY"] = 41;

  sideBar->textureMap["xcoordText"] = new AdamTexture;
  sideBar->textureMap["xcoordText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["xtextX"] = 150+SCREENW;
  sideBar->var["xtextY"] = 77;

  sideBar->textureMap["ycoordText"] = new AdamTexture;
  sideBar->textureMap["ycoordText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["ytextX"] = 150+SCREENW;
  sideBar->var["ytextY"] = 116;

  sideBar->textureMap["heightText"] = new AdamTexture;
  sideBar->textureMap["heightText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["htextX"] = 150+SCREENW;
  sideBar->var["htextY"] = 154;
  
  sideBar->textureMap["widthText"] = new AdamTexture;
  sideBar->textureMap["widthText"]->loadFromText(" ", {0, 0, 0, 0}, gameWindow->renderer, gameWindow->font);
  sideBar->var["wtextX"] = 150+SCREENW;
  sideBar->var["wtextY"] = 195;

  sideBar->textureMap["heightwidth"] = new AdamTexture;
  sideBar->textureMap["heightwidth"]->loadFromFile("assets/hw.png", gameWindow->renderer);
  sideBar->textureMap["heightwidth"]->setAlphaLevel(0);
  sideBar->var["hwtextX"] = 14+SCREENW;
  sideBar->var["hwtextY"] = 157;

  sideBar->addComponent("sideBar", logicSideBar);
  newScene->sceneNodes.push_back(sideBar);
}

  

  
  return newScene;
}