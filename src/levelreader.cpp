#include "headers/AdamLib.hpp"
#include "headers/Grid.hpp"
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
  newScene->tileGrid.placeObj(nullptr, {21, 5, 15, 10});

  const auto& layers = map.getLayers();
  const auto& tileSets = map.getTilesets();
  int ammTileSets = tileSets.size();

  for(int i=0; i<ammTileSets; ++i)
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
      int i = 0;
      for(auto tmp2 : newScene->tileLayers[0]->getTiles())
      {
        if(tmp2.ID)
        {
          SDL_Rect tmp = {(i%newScene->tileGrid.ammNodeWidth)*newScene->tileGrid.widthNode, (i/newScene->tileGrid.ammNodeWidth)*newScene->tileGrid.heightNode, newScene->tileGrid.widthNode, newScene->tileGrid.heightNode};
          newScene->tileGrid.placeObj(&tmp2, tmp);
          //printf("TILE ID %d\n", tmp2.ID);
        }

        ++i;
      }
    }
  }


  return newScene;
}