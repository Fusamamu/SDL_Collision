//
//  Tile.cpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 27/12/2563 BE.
//

#include "Tile.hpp"

Tile::Tile(int i, int j, SDL_Renderer* render):
m_i(i),
m_j(j),
GameObject(render),
m_tileType(FLOOR){
    
}

Tile::~Tile(){
    
}
