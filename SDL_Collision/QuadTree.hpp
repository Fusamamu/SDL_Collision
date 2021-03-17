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
#include "GameObject.hpp"

class QuadTree{
public:
    QuadTree();
    QuadTree(int maxObjects, int maxLevels, int level, SDL_Rect bound, QuadTree* parent);
    ~QuadTree();
    
    void Insert(GameObject* go);
    void Remove(GameObject* go);
    void Clear();
    
    std::vector<GameObject*> Search(const SDL_Rect& area);
    
    const SDL_Rect& GetBound() const { return m_bound; }
    
private:
    
    void Search(const SDL_Rect& area, std::vector<GameObject*>& overlappedObjects);
    
    int GetChildIndexForObject(GameObject* go);
    void Split();
    
    static const int thisTree = -1;
    static const int childNE = 0;
    static const int childNW = 1;
    static const int childSW = 2;
    static const int childSE = 3;
    
    int MAXOBJECTS;
    int MAXLEVELS;
    
    int m_level;
    
    SDL_Rect m_bound;
    
    QuadTree* m_parent;
    QuadTree* m_children[4];
    
    std::vector<GameObject*> m_objects;
};

#endif /* QuadTree_hpp */
