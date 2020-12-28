//
//  Tile.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 27/12/2563 BE.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <stdio.h>
#include "GameObject.hpp"

class Tile:public GameObject{
public:
    enum TILETYPE{
        WALL,
        FLOOR
    };
    
    Tile(SDL_Renderer* render);
    ~Tile();
    
    void SetType(TILETYPE t){ m_tileType = t; }
    
private:
    TILETYPE m_tileType;
};

#endif /* Tile_hpp */
