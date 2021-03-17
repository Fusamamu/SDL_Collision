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
    
    Tile(int i, int j, SDL_Renderer* render);
    ~Tile();
    
    void SetType(TILETYPE t){ m_tileType = t; }
    
    std::vector<Tile*> GetChilds() { return m_childs; }
    
    Tile* GetParent() const { return m_parent; }
    void SetParent(Tile* tile) { m_parent = tile; }
    
    int& G() { return g; }
    int& H() { return h; }
    int F() { return g + h; }
    
    const int& Row_i()      const { return m_i; }
    const int& Coloum_j()   const { return m_j; }
    
private:
    TILETYPE m_tileType;
    
    Tile* m_parent;
    
    std::vector<Tile*> m_childs;
   
    int g;
    int h;
    int f;
    
    int m_i;
    int m_j;
};

#endif /* Tile_hpp */
