#include "headers/Scene.hpp"
#include "headers/Grid.hpp"


Scene::Scene(float x, float y, float w, float h, int tileDim, int ammountTilesWide, int ammountTilesTall)
{
  tileLayers.reserve(3);

  width = w; height = h;

  camera = new Camera(x, y, gameWindow->screenW, gameWindow->screenH);
  tileGrid.initialize(w, h, tileDim, tileDim);
  objectGrid.initialize(w, h);
}

//implement
Scene::~Scene()
{
  for(auto node : sceneNodes)
  {
    
  }

  delete camera;
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

void Scene::setCamera(float x, float y, float w, float h)
{
  camera->cameraRect = {x, y, w, h};
}

//wtf
SDL_FRect Scene::checkIfTileCollision(SDL_FRect* const obj)
{
  return {0,0,0,0};
}

// ------------------------------------------------------------

BasicNode::BasicNode(Scene* sceneParent, void (*renderptr)(BasicNode* parent))
{
  var["x"] = 0;
  var["y"] = 0;
  var["w"] = 0;
  var["h"] = 0;
  
  renderfuncptr = renderptr;
  parentScene = sceneParent;
}

BasicNode::~BasicNode()
{
  for(auto [key, component] : componentMap)
    delete component;
  componentMap.clear();

  for(auto [key, texture] : textureMap)
    delete texture;
  textureMap.clear();

  var.clear();
}

void BasicNode::render()
{
  if(renderfuncptr != nullptr)
  {
    renderfuncptr(this);
    return;
  } 
}

void BasicNode::setTexture(std::string path)
{
  textureMap["main"]->loadFromFile(path, gameWindow->renderer);
}

void BasicNode::setTexture(AdamTexture* newTexture)
{
  textureMap["main"]->replaceTexture(newTexture);
}

void BasicNode::performLogic()
{
  for(auto [key, component] : componentMap)
  {
    component->performLogic();
  }

}

void BasicNode::setPos(int x, int y)
{
  var["x"] = x;
  var["y"] = y;
}

void BasicNode::setDim(int w, int h)
{
  var["w"] = w;
  var["h"] = h;
}

void BasicNode::addComponent(std::string key, void (*newFunc)(Component<BasicNode*>* host))
{
  componentMap[key] = new Component<BasicNode*>(this, newFunc);
}

// ------------------------------------------------------------

TileNode::TileNode(Scene* _parent, tmx::Tileset tSet)
{
  parentScene = _parent;
  tileSet = new adamLib::TileSet(adamLib::convertToAdamTileSet(tSet));
  setTexture(tSet.getImagePath());
}

TileNode::~TileNode()
{
  delete tileSet;
}

void TileNode::render()
{
  for(auto& tileLayer : parentScene->tileLayers)
  {
    int i = -1;
    for(auto& tile : tileLayer.tiles)
    {
      ++i;
      if(!isTileInSet(tile.ID))
        continue;

      SDL_Rect clip;
      clip = tileSet->getTileRect(tile.ID);
      int adj = i*clip.w;
      tileSet->tileSetTexture.setAlphaLevel(tileLayer.opacity*255);
      tileSet->tileSetTexture.render(gameWindow->renderer, {(adj)%parentScene->width, (adj/parentScene->width)*clip.h}, &clip);
    }

  } 
}

void TileNode::performLogic()
{

}

void TileNode::setTexture(std::string path)
{
  tileSet->tileSetTexture.loadFromFile(path, gameWindow->renderer);
}

bool TileNode::isTileInSet(int id)
{
  return tileSet->tSet.hasTile(id);
}
// ------------------------------------------------------------

Camera::Camera() : Camera(0, 0, gameWindow->screenW, gameWindow->screenH)
{

}

Camera::Camera(float x, float y, float w, float h)
{
  cameraRect = {x, y, w, h};
  scale = 1.0f;
}

Camera::~Camera()
{

}

// ------------------------------------------------------------



