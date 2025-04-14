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
  if(!map.load("levels/map.tmx"))
    return nullptr;


  Scene* newScene = new Scene(0, 0, SCREENW, SCREENH, 25, 0, 0);
  newScene->setCamera(0,0,SCREENW, SCREENH);

  for(auto tSet : map.getTilesets())
  {
    TileNode* newNode = new TileNode(newScene, tSet);
    newScene->sceneNodes.push_back(newNode);
  }

  const auto& layers = map.getLayers();
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
      adamLib::TileLayer tLayer = adamLib::convertToAdamTileLayer(layer->getLayerAs<tmx::TileLayer>());
      newScene->tileLayers.push_back(tLayer);
    }
  }

  int i = -1;
  for(auto& tileLayer : newScene->tileLayers)
  {
    for(auto& tile : tileLayer.tiles)
    {
      ++i;
      if(!tile.ID)
        continue;

      SDL_Rect tmp = {(i%newScene->tileGrid.ammNodeWidth)*newScene->tileGrid.widthNode, 
                      (i/newScene->tileGrid.ammNodeWidth)*newScene->tileGrid.heightNode, 
                      newScene->tileGrid.widthNode, newScene->tileGrid.heightNode
                     };

      newScene->tileGrid.placeObj(&tile, tmp);

    }

  }


  return newScene;
}