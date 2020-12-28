//
//  Tile.cpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 27/12/2563 BE.
//

#include "Tile.hpp"

Tile::Tile(SDL_Renderer* render):
GameObject(render),
m_tileType(FLOOR){
    
}

Tile::~Tile(){
    
}
