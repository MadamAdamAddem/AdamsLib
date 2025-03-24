#include "headers/AdamLib.hpp"
#include "headers/Quadtree.hpp"


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


  QuadTree<int> tree(2, 640, 360);




  return newScene;
}