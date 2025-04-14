#pragma once
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <forward_list>
#include <SDL2/SDL.h>



template<typename T>
class GridNode
{
public:

  std::forward_list<T*> listObjs;
};


template<typename T>
class ObjGrid
{
public:

  ObjGrid() {};
  ObjGrid(int32_t _width, int32_t _height, int32_t _widthNode, int32_t _heightNode)
  {
    initialize(_width, _height, _widthNode, _heightNode);
  }
  ~ObjGrid()
  {
    for(int i=0; i<ammNodeHeight; ++i)
    {
      delete[] arrNodes[i];
    }

    delete[] arrNodes;
  }

  //if dimension of grid is not evenly divisible by dimension of node, good luck buddy
  void initialize(int32_t _width, int32_t _height, int32_t _widthNode = 10, int32_t _heightNode = 10)
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


  bool placeObj(T* objPtr, const SDL_Rect bounds)
  {
    SDL_Rect tmp = {0,0, width, height};
    if(objPtr == nullptr || !SDL_HasIntersection(&tmp, &bounds))
      return false;

    int xIndex = bounds.x/widthNode;
    int yIndex = bounds.y/heightNode;
    int nodesWide = (bounds.x + bounds.w)/widthNode;
    int nodesTall = (bounds.y + bounds.h)/heightNode;


    
    for(int i=yIndex; i<ammNodeHeight && i <= nodesTall; ++i)
    {
      if(i < 0)
      continue;
      
      for(int j=xIndex; j<ammNodeWidth && j <= nodesWide; ++j)
      {
        if(j < 0)
        continue;

        //std::cout << "Placing Object at Index: " << i << " " << j << std::endl;
        arrNodes[i][j].listObjs.push_front(objPtr);
      }
    }
    

    return true;
  }

  //unoptimized if the compiler isn't doing return value optimization
  std::forward_list<T*> getObjsInArea(SDL_Rect bounds)
  {
    SDL_Rect tmp = {0,0, width, height};

    std::forward_list<T*> retVal;

    if(!SDL_HasIntersection(&tmp, &bounds))
      return retVal;


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

        if(!arrNodes[i][j].listObjs.empty())
        {
          retVal.merge(arrNodes[i][j].listObjs);
        }
      }
    }

    retVal.sort();
    retVal.unique();
    return retVal;
  }


  GridNode<T>** arrNodes;

  int32_t width;
  int32_t height;

  int32_t widthNode;
  int32_t heightNode;

  int32_t ammNodeWidth;
  int32_t ammNodeHeight;
};
