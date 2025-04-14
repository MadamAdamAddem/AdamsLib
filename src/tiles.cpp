#include "headers/Tiles.hpp"




adamLib::TileLayer adamLib::convertToAdamTileLayer(tmx::TileLayer oldTileLayer)
{
  TileLayer newLayer;

  for(auto tile : oldTileLayer.getTiles())
  {
    newLayer.tiles.push_back({(int)tile.ID});
  }
  newLayer.opacity = oldTileLayer.getOpacity();

  return newLayer;
}


adamLib::TileSet adamLib::convertToAdamTileSet(tmx::Tileset oldTileSet)
{
  return {oldTileSet};
}




tmx::Vector2u adamLib::TileSet::getGIDs() {return {tSet.getFirstGID(), tSet.getLastGID()};}
tmx::Vector2u adamLib::TileSet::getTilePos(int id) {return tSet.getTile(id)->imagePosition;}
SDL_Rect adamLib::TileSet::getTileRect(int id) 
{
  tmx::Vector2u pos = tSet.getTile(id)->imagePosition;
  return {pos.x, pos.y, tSet.getTileSize().x, tSet.getTileSize().y};
}