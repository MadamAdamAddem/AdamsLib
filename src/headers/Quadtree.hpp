#pragma once
#include <vector>
#include <iostream>
#include <stdint.h>
#include <forward_list>
#include <SDL2/SDL.h>


template<typename T>
class QuadTreeNode
{
public:

  QuadTreeNode(int depth, SDL_FRect _bounds)
  {
    topLeft = nullptr;
    topRight = nullptr;
    bttmLeft = nullptr;
    bttmRight = nullptr;
    bounds = _bounds;

    if(depth <= 1)
    {
      isDeepest = true;
      std::cout << "Leaf Node Made. Bounds: " << bounds.x << " " << bounds.y << std::endl;
      return;
    }
  
    isDeepest = false;
    std::cout << "Non-Leaf Node Made. Bounds: " << bounds.x << " " << bounds.y << std::endl;

    topLeft = new QuadTreeNode<T>(depth - 1, {bounds.x, bounds.y, bounds.w/2, bounds.h/2});
    topRight = new QuadTreeNode<T>(depth - 1, {bounds.x + bounds.w/2, bounds.y, bounds.w/2, bounds.h/2});
    bttmLeft = new QuadTreeNode<T>(depth - 1, {bounds.x, bounds.y + bounds.h/2, bounds.w/2, bounds.h/2});
    bttmRight = new QuadTreeNode<T>(depth - 1, {bounds.x + bounds.w/2, bounds.y + bounds.h/2, bounds.w/2, bounds.h/2});
  
    
  }
  ~QuadTreeNode()
  {
    delete topLeft;
    delete topRight;
    delete bttmLeft;
    delete bttmRight;
  }

  void mergeWithDeepestList(SDL_FRect* const objRect, std::forward_list<T*>* objList)
  {
    if(isDeepest)
    {
      if(!list.empty())
        objList->merge(&list);
  
      return;
    }
  
    
    if(SDL_HasIntersectionF(&topLeft->bounds, objRect))
    {
      topLeft->mergeWithDeepestList(objRect, objList);
    }
  
    if(SDL_HasIntersectionF(&topRight->bounds, objRect))
    {
      topRight->mergeWithDeepestList(objRect, objList);
    }
  
    if(SDL_HasIntersectionF(&bttmLeft->bounds, objRect))
    {
      bttmLeft->mergeWithDeepestList(objRect, objList);
    }
  
    if(SDL_HasIntersectionF(&bttmRight->bounds, objRect))
    {
      bttmRight->mergeWithDeepestList(objRect, objList);
    }
    
  }
  
  bool addObjectToTree(T* const object, SDL_FRect* const objRect)
  {
    if(isDeepest)
    {
      list.push_front(object);
      return true;
    }
  
  
    bool foundPlace = false;
    if(SDL_HasIntersectionF(&topLeft->bounds, objRect))
    {
      foundPlace += topLeft->addObjectToTree(object, objRect);
    }
  
    if(SDL_HasIntersectionF(&topRight->bounds, objRect))
    {
      foundPlace += topRight->addObjectToTree(object, objRect);
    }
  
    if(SDL_HasIntersectionF(&bttmLeft->bounds, objRect))
    {
      foundPlace += bttmLeft->addObjectToTree(object, objRect);
    }
  
    if(SDL_HasIntersectionF(&bttmRight->bounds, objRect))
    {
      foundPlace += bttmRight->addObjectToTree(object, objRect);
    }
  
    return foundPlace;
  
  }

  QuadTreeNode<T>* topLeft;
  QuadTreeNode<T>* topRight;
  QuadTreeNode<T>* bttmLeft;
  QuadTreeNode<T>* bttmRight;

  bool isDeepest;
  SDL_FRect bounds;

  std::forward_list<T*> list;

};

template<typename T>
class QuadTree
{
public:

  QuadTree(int depth, int _areaW, int _areaH)
  {
    headNode = new QuadTreeNode<T>(depth, {0, 0, _areaW, _areaH});
    areaW = _areaW;
    areaH = _areaH;
  }
  ~QuadTree() {delete headNode;}
  QuadTreeNode<T>* headNode;

  int areaW;
  int areaH;

  std::forward_list<T*> getObjsThatCollide(SDL_FRect* const objRect)
  {
    std::forward_list<T*> list;
    if(SDL_HasIntersectionF(&headNode->bounds, objRect))
    {
      headNode->mergeWithDeepestList(objRect, &list);
    }
  
    return list;
  }

  bool addObjectToTree(T* const object, SDL_FRect* const objRect)
  {
    if(SDL_HasIntersectionF(&headNode->bounds, objRect))
    {
      headNode->addObjectToTree(object, objRect);
      return true;
    }
  
    return false;
  }
};
