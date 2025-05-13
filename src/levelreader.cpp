#include "headers/AdamLib.hpp"
#include "headers/Grid.hpp"
#include "headers/Tiles.hpp"
#include <stdio.h>
#include <stdint.h>


#define SCREENW 750
#define SCREENH 500


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
  if(!map.load("../src/levels/map.tmx"))
    return nullptr;


  Scene* newScene = new Scene(0, 0, SCREENW, SCREENH, 25, 0, 0);
  newScene->setCamera(0,0,SCREENW, SCREENH);

  std::vector<TileNode*> tNodesTMP;

  for(auto tSet : map.getTilesets())
  {
    TileNode* newNode = new TileNode(newScene, tSet);
    newScene->sceneNodes.push_back(newNode);
    tNodesTMP.push_back(newNode);

    AdamTexture* newTexture = new AdamTexture(tSet.getImagePath(), gameWindow->renderer);
    newScene->activeTextures.push_back(newTexture);
    newNode->setTexture(newTexture);

  }



  //place objects and tiles into their nodes
  const auto& layers = map.getLayers();
  int layerNum = -1;
  for(const auto& layer : layers)
  {
    if(layer->getType() == tmx::Layer::Type::Object)
    {
      ++layerNum;
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
      ++layerNum;
      auto tmp = layer->getLayerAs<tmx::TileLayer>();

      int i=-1;
      for(auto tile : tmp.getTiles())
      {
        ++i;
        for(auto tileNode: tNodesTMP)
        {
          if(!tileNode->isTileInSet(tile.ID))
            continue;

          SDL_Rect clip;
          clip = tileNode->tileSet->getTileRect(tile.ID);
          int adj = i*clip.w;
          tileNode->tileVector.push_back(adamLib::Tile{tile.ID, (adj)%newScene->width, (adj/newScene->width)*clip.h, layerNum, tmp.getOpacity()});
          break;
        }
        
      }

    }
  }

  //place tiles into tileGrid
  for(auto& tileNode : tNodesTMP)
  {
    for(auto& tile : tileNode->tileVector)
    {
      SDL_Rect tmp = tileNode->tileSet->getTileRect(tile.ID);
      tmp.x = tile.x;
      tmp.y = tile.y;

      newScene->tileGrid.placeObj(&tile, tmp);
    }

  }

  return newScene;
}