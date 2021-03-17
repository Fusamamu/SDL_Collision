//
//  QuadTree.cpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 27/12/2563 BE.
//

#include "QuadTree.hpp"

QuadTree::QuadTree(){
    
}

QuadTree::QuadTree(int maxObjects, int maxLevels, int level, SDL_Rect bound, QuadTree* parent):
MAXOBJECTS(maxObjects),
MAXLEVELS(maxLevels),
m_level(level),
m_bound(bound),
m_parent(parent){
    
}

QuadTree::~QuadTree(){
    
}

void QuadTree::Insert(GameObject* go){
    
    if (!SDL_HasIntersection(&m_bound, &go->GetDestRect())) {
        return;
    }
    
    if (m_children[0] != nullptr) {
        int indexToPlaceObject = GetChildIndexForObject(go);
        
        if (indexToPlaceObject != thisTree) {
            m_children[indexToPlaceObject]->Insert(go);
            return;
        }
    }
    
    m_objects.push_back(go);
    
    if (m_objects.size() > MAXOBJECTS && m_level < MAXLEVELS && m_children[0] == nullptr) {
        
        Split();
        
        auto objIter = m_objects.begin();
        
        while (objIter != m_objects.end()) {
            auto obj = *objIter;
            
            int indexToPlaceObject = GetChildIndexForObject(go);
            
            if (indexToPlaceObject != thisTree) {
                m_children[indexToPlaceObject]->Insert(obj);
                objIter = m_objects.erase(objIter);
            }else{
                ++objIter;
            }
        }
    }
}


void QuadTree::Remove(GameObject* go){
    
}

void QuadTree::Clear(){
    
}

int QuadTree::GetChildIndexForObject(GameObject* go){
    
    int index = -1;
    
    double verticalDividingLine     = m_bound.x + m_bound.w * 0.5f;
    double horizontalDividingLine   = m_bound.y + m_bound.h * 0.5f;

    bool north  = go->Frame().bottom < horizontalDividingLine;
    bool south  = go->Frame().top > horizontalDividingLine;
    bool west   = go->Frame().right < verticalDividingLine;
    bool east   = go->Frame().left > verticalDividingLine;
        
    if(east)
    {
        if(north)
        {
            index = childNE;
        }
        else if(south)
        {
            index = childSE;
        }
    }
    else if(west)
    {
        if(north)
        {
            index = childNW;
        }
        else if(south)
        {
            index = childSW;
        }
    }
    
    return index;
}

void QuadTree::Split(){
    int childWidth = m_bound.w /2;
    int childHeight = m_bound.h /2;

    m_children[childNE] = new QuadTree (MAXOBJECTS, MAXLEVELS, m_level+1, {m_bound.x + childWidth, m_bound.y, childWidth, childHeight}, this);
    m_children[childNW] = new QuadTree (MAXOBJECTS, MAXLEVELS, m_level+1, {m_bound.x, m_bound.y, childWidth, childHeight}, this);
    m_children[childSW] = new QuadTree (MAXOBJECTS, MAXLEVELS, m_level+1, {m_bound.x, m_bound.y + childHeight, childWidth, childHeight}, this);
    m_children[childSW] = new QuadTree (MAXOBJECTS, MAXLEVELS, m_level+1, {m_bound.x + childWidth, m_bound.y + childHeight, childWidth, childHeight}, this);
}


