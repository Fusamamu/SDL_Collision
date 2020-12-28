//
//  QuadTree.cpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 27/12/2563 BE.
//

#include "QuadTree.hpp"

QuadTree::QuadTree(int level, SDL_Rect bound):
m_level(level),
m_bound(bound){
    for(int i = 0; i < 4; ++i){
        m_nodes = (QuadTree*)malloc(sizeof(QuadTree));
        m_nodes++;
    }
}

void QuadTree::Clear(){
    m_Objects.clear();
    
    
   
}
