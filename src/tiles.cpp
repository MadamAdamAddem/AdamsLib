#include "headers/Tiles.hpp"





adamLib::Tile adamLib::convertToAdamTile(tmx::TileLayer::Tile oldTile)
{
  return {(int)oldTile.ID, (int)oldTile.flipFlags};
}

adamLib::TileLayer adamLib::convertToAdamTileLayer(tmx::TileLayer oldTileLayer)
{
  TileLayer newLayer;

  for(auto tile : oldTileLayer.getTiles())
  {
    newLayer.tiles.push_back(convertToAdamTile(tile));
  }
  newLayer.opacity = oldTileLayer.getOpacity();
  newLayer.isVisible = oldTileLayer.getVisible();

  return newLayer;
}

//does not load texture, do it manually after calling
adamLib::TileSet adamLib::convertToAdamTileSet(tmx::Tileset oldTileSet)
{
  return {oldTileSet};
}




bool adamLib::TileSet::hasTile(int id) 
{
  return tSet.hasTile(id);
}

tmx::Vector2u adamLib::TileSet::getGIDs() {return {tSet.getFirstGID(), tSet.getLastGID()};}
tmx::Vector2u adamLib::TileSet::getTilePos(int id) {return tSet.getTile(id)->imagePosition;}
SDL_Rect adamLib::TileSet::getTileRect(int id) 
{
  tmx::Vector2u pos = tSet.getTile(id)->imagePosition;
  return {pos.x, pos.y, tSet.getTileSize().x, tSet.getTileSize().y};
}