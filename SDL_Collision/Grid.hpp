//
//  Grid.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 26/12/2563 BE.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include <vector>
#include "SDL2/SDL.h"
#include "Vector2D.hpp"

class Grid{
public:
    Grid(int row, int column, class GameEngine* ge);
    ~Grid();
    
    void GenerateTiles();
    void Render();
    
    class Tile* GetTile(int row, int column) const;
    class Tile* GetTile(float posX, float posY) const;
    
    class Tile* GetAdjacent_top(Tile* selectedTile) const;
    class Tile* GetAdjacent_bottom(Tile* selectedTile) const;
    class Tile* GetAdjacent_left(Tile* selectedTile) const;
    class Tile* GetAdjacent_right(Tile* selectedTile) const;
    
    int CalculateMahattanDistance(Tile* startNode, Tile* targetNode) const;
    
    void SetColor(SDL_Color c);
    
    void ProcessInput();
    
private:
    int m_row;
    int m_column;
    
    float m_tileWidth;
    
    struct Vector2D m_origin;
    struct Vector2D m_center;
    
    std::vector<class Tile*> m_tileArray;
    
    class GameEngine* m_ge;
    
};

#endif /* Grid_hpp */
