#pragma once
#include "Rendering.hpp"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>


namespace adamLib {
  struct Tile{

    unsigned int ID = 0;
    int x, y;
    int layer;
    float opacity;

  }typedef Tile;

  /*
  struct TileLayer{

    std::vector<Tile> tiles;

    float opacity = 1;
    bool doCollision = true;

  }typedef TileLayer;*/

  struct TileSet{
    
    tmx::Tileset tSet;

    tmx::Vector2u getGIDs();
    tmx::Vector2u getTilePos(int id);
    SDL_Rect getTileRect(int id);


    AdamTexture* tileSetTexture;


  }typedef TileSet;

  //TileLayer convertToAdamTileLayer(tmx::TileLayer oldTileLayer);
  TileSet convertToAdamTileSet(tmx::Tileset oldTileSet);

}