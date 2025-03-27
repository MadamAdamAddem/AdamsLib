#include "headers/AdamLib.hpp"

#include <stdio.h>
#include <stdint.h>
#include <forward_list>



template<typename T>
class GridNode
{
public:

  std::forward_list<T*> listObjs;
};


template<typename T>
class CollisionGrid
{
public:

  //if dimension of grid is not evenly divisible by dimension of node, good luck buddy
  CollisionGrid(int32_t _width, int32_t _height, int32_t _widthNode, int32_t _heightNode)
  {
    width = _width;
    height = _height;
    widthNode = _widthNode;
    heightNode = _heightNode;
    ammNodeWidth = (width / widthNode);
    ammNodeHeight = (height / heightNode);


    arrNodes = new GridNode<T>*[ammNodeHeight];

    for(int i=0; i<ammNodeHeight; ++i)
    {
      arrNodes[i] = new GridNode<T>[ammNodeWidth];
    }
  }
  ~CollisionGrid()
  {
    for(int i=0; i<ammNodeHeight; ++i)
    {
      delete[] arrNodes[i];
    }

    delete[] arrNodes;
  }

  bool placeObj(T* objPtr, SDL_Rect bounds)
  {
    SDL_Rect tmp = {0,0, width, height};
    //if(objPtr == nullptr || !SDL_HasIntersection(&tmp, &bounds))
      //return false;

    int xIndex = bounds.x/widthNode;
    int yIndex = bounds.y/heightNode;
    int nodesWide = (bounds.x + bounds.w)/widthNode;
    int nodesTall = (bounds.y + bounds.h)/heightNode;

    
    for(int i=yIndex; i<ammNodeHeight && i <= nodesTall; ++i)
    {
      if(i < 0)
      continue;
      
      for(int j=xIndex; j<ammNodeWidth && j<= nodesWide; ++j)
      {
        if(j < 0)
        continue;

        std::cout << "Accessing index " << i << " " << j << std::endl;
      }
    }
    

    return false;
  }

  GridNode<T>** arrNodes;

  int32_t width;
  int32_t height;

  int32_t widthNode;
  int32_t heightNode;

  int32_t ammNodeWidth;
  int32_t ammNodeHeight;
};

#define SCREENW 1280
#define SCREENH 720


void renderXmlReader(BasicNode* parent)
{

}

void logicXmlReader(Component<BasicNode*>* host)
{

}

//-----------------------------------------------------------------------------------------

Scene* newScene()
{
  tmx::Map map;
  if(!map.load("levels/map.tmx"))
    return nullptr;


  Scene* newScene = new Scene(0, 0, SCREENW, SCREENH, map.getTileSize().x, map.getTileCount().x, map.getTileCount().y);
  newScene->setCamera(0,0,SCREENW, SCREENH);

  
  const auto& layers = map.getLayers();
  const auto& tileSets = map.getTilesets();
  int vSize = tileSets.size();

  for(int i=0; i<vSize; ++i)
  {
    tmx::Tileset* newTileset = new tmx::Tileset(tileSets[i]);
    newScene->tileSets[i].first = newTileset;
    newScene->tileSets[i].second = new AdamTexture(newTileset->getImagePath(), gameWindow->renderer);
  }

  for(const auto& layer : layers)
  {
    if(layer->getType() == tmx::Layer::Type::Object)
    {
      /*
      const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
      const auto& objects = objectLayer.getObjects();
      for(const auto& object : objects)
      {
        object.getProperties().at(0).getName();
      }
      */
    }
    else if(layer->getType() == tmx::Layer::Type::Tile)
    {
      newScene->tileLayers.push_back(new tmx::TileLayer(layer->getLayerAs<tmx::TileLayer>()));
      for(const auto tmp2 : newScene->tileLayers)
      {
        //std::cout << tmp2.ID << std::endl;
      }
    }
  }


  CollisionGrid<int> test(50, 30, 10, 10);
  //sometimes seg fault when neg?
  
  test.placeObj(nullptr, { -10, 15, 15, 10});




  return newScene;
}