#pragma once
#include "Rendering.hpp"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>






namespace adamLib {
  struct Tile{

    int ID = 0;
    int flipFlag = 0;
    bool doCollison = true;

  }typedef Tile;

  struct TileLayer{

    std::vector<Tile> tiles;

    float opacity = 1;
    bool isVisible = true;

  }typedef TileLayer;

  struct TileSet{

    tmx::Tileset tSet;


    bool hasTile(int id);
    tmx::Vector2u getGIDs();
    tmx::Vector2u getTilePos(int id);
    SDL_Rect getTileRect(int id);


    AdamTexture tileSetTexture;


  }typedef TileSet;


  Tile convertToAdamTile(tmx::TileLayer::Tile oldTile);
  TileLayer convertToAdamTileLayer(tmx::TileLayer oldTileLayer);

  //does not load texture, do it manually after calling
  TileSet convertToAdamTileSet(tmx::Tileset oldTileSet);
}