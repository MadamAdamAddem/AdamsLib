#include "headers/Quadtree.hpp"

/*
template<typename T>
QuadTreeNode<T>::QuadTreeNode(int depth, SDL_FRect _bounds)
{
  topLeft = nullptr;
  topRight = nullptr;
  bttmLeft = nullptr;
  bttmRight = nullptr;

  if(depth <= 1)
  {
    isDeepest = true;
    return;
  }

  isDeepest = false;
  bounds = _bounds;

  topLeft = new QuadTreeNode<T>(depth - 1, {bounds.x, bounds.y, bounds.w/2, bounds.h/2});
  topRight = new QuadTreeNode<T>(depth - 1, {bounds.x + bounds.w/2, bounds.y, bounds.w/2, bounds.h/2});
  bttmLeft = new QuadTreeNode<T>(depth - 1, {bounds.x, bounds.y + bounds.h/2, bounds.w/2, bounds.h/2});
  bttmRight = new QuadTreeNode<T>(depth - 1, {bounds.x + bounds.w/2, bounds.y + bounds.h/2, bounds.w/2, bounds.h/2});

}

template<typename T>
QuadTreeNode<T>::~QuadTreeNode()
{
  delete topLeft;
  delete topRight;
  delete bttmLeft;
  delete bttmRight;
}

//will cause problems if there somehow exists a non-left node that has a nullptr
template<typename T>
void QuadTreeNode<T>::mergeWithDeepestList(SDL_FRect* const objRect, std::forward_list<T*>* objList)
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

template<typename T>
bool QuadTreeNode<T>::addObjectToTree(T* const object, SDL_FRect* const objRect)
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

} */

// ------------------------------------------------------------

/*
template<typename T>
QuadTree<T>::QuadTree(int depth, int _areaW, int _areaH)
{
  headNode = new QuadTreeNode<T>(depth, {0, 0, _areaW, _areaH});
  areaW = _areaW;
  areaH = _areaH;
}

template<typename T>
QuadTree<T>::~QuadTree()
{
  delete headNode;
}

template<typename T>
std::forward_list<T*> QuadTree<T>::getObjsThatCollide(SDL_FRect* const objRect)
{
  std::forward_list<T*> list;
  if(SDL_HasIntersectionF(&headNode->bounds, objRect))
  {
    headNode->mergeWithDeepestList(objRect, &list);
  }

  return list;
}

template<typename T>
bool QuadTree<T>::addObjectToTree(T* const object, SDL_FRect* const objRect)
{
  if(SDL_HasIntersectionF(&headNode->bounds, objRect))
  {
    headNode->addObjectToTree(object, objRect);
    return true;
  }

  return false;
}

template<typename T>
void QuadTree<T>::doThing()
{
  std::cout << "ASDAD" << std::endl;
} */