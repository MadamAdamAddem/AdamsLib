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


    arrNodes = new GridNode<T>[ammNodeWidth * ammNodeHeight];
  }
  ~CollisionGrid()
  {
    delete[] arrNodes;
  }

  bool emplaceObj(T* objPtr, SDL_Rect bounds)
  {
    //if(objPtr == nullptr)
      //return false;

    int topLeftIndex = bounds.x/widthNode + (bounds.y/heightNode)*ammNodeWidth;
    int nodesWide = (bounds.x + bounds.w)/widthNode - bounds.x/widthNode;
    int nodesTall = (bounds.y + bounds.h)/heightNode - bounds.y/heightNode;

    int botRightIndex = bounds.w/widthNode + (bounds.h/heightNode)*ammNodeWidth + topLeftIndex;
    
    for(int i=topLeftIndex; i<=nodesWide; ++i)
    {
      arrNodes[i].listObjs.push_front();
    }
    
    printf("%d %d %d\n", topLeftIndex, nodesWide, nodesTall);

    return false;
  }

  GridNode<T>* arrNodes;
  int32_t width;
  int32_t height;

  int32_t widthNode;
  int32_t heightNode;

  int32_t ammNodeWidth;
  int32_t ammNodeHeight;
};