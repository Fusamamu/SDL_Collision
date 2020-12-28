//
//  QuadTree.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 27/12/2563 BE.
//

#ifndef QuadTree_hpp
#define QuadTree_hpp

#include <stdio.h>
#include <vector>
#include "SDL2/SDL.h"


class QuadTree{
public:
    QuadTree(int level, SDL_Rect bound);
    ~QuadTree();
    
    void Clear();
    
private:
    const int MAXOBJECTS = 10;
    const int MAXLEVELS  = 5;
    
    int m_level;
    std::vector<class GameObject*> m_Objects;
    SDL_Rect m_bound;
    QuadTree* m_nodes;
    
};

#endif /* QuadTree_hpp */
