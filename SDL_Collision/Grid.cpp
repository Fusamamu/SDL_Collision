//
//  Grid.cpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 26/12/2563 BE.
//

#include <iostream>
#include <algorithm>
#include <math.h>
#include "Grid.hpp"
#include "GameEngine.hpp"
#include "Tile.hpp"


Grid::Grid(int row, int column, GameEngine* ge):
m_row(row),
m_column(column),
m_tileWidth(10),
m_ge(ge){
    
    GenerateTiles();
}

Grid::~Grid(){
    
}

void Grid::GenerateTiles(){
    for(int i = 0; i < m_row; ++i){
        for (int j = 0; j < m_column; ++j) {
            Tile* t = new Tile(i, j, m_ge->GetRenderer());
            t->SetSize(40, 40);
            t->SetPosition(Vector2D(i * t->GetWidth(), j * t->GetHeight()));
            t->Pos_X() += t->GetWidth()/2;
            t->Pos_Y() += t->GetHeight()/2;
            m_tileArray.push_back(t);
        }
    }
}

void Grid::Render(){
    for(auto t : m_tileArray){
        t->Render();
    }
}

void Grid::SetColor(SDL_Color c){
    for(auto t : m_tileArray){
        t->SetColor(c);
    }
}

void Grid::ProcessInput() {
    SDL_Point p;
    SDL_GetMouseState(&p.x, &p.y);
}

Tile* Grid::GetTile(int row, int column) const {
//    Tile tile (row, column, m_ge->GetRenderer());
//    auto iter = std::find(m_tileArray.begin(), m_tileArray.end(), tile);
//    return *iter;
    for(auto tile: m_tileArray){
        if (tile->Row_i() == row && tile->Coloum_j() == column) {
            return tile;
        }
    }
    
    return NULL;
}

Tile* Grid::GetAdjacent_top(Tile* selectedTile) const {
    int i = selectedTile->Row_i() + 1;
    int j = selectedTile->Coloum_j();
    return GetTile(i, j);
}

Tile* Grid::GetAdjacent_bottom(Tile* selectedTile) const {
    int i = selectedTile->Row_i() - 1;
    int j = selectedTile->Coloum_j();
    return GetTile(i, j);
}

Tile* Grid::GetAdjacent_left(Tile* selectedTile) const {
    int i = selectedTile->Row_i();
    int j = selectedTile->Coloum_j() - 1;
    return GetTile(i, j);
}

Tile* Grid::GetAdjacent_right(Tile* selectedTile) const {
    int i = selectedTile->Row_i();
    int j = selectedTile->Coloum_j() + 1;
    return GetTile(i, j);
}

int Grid::CalculateMahattanDistance(Tile* startNode, Tile* targetNode) const {
    int horizontal_cost = abs(startNode->Coloum_j() - targetNode->Coloum_j());
    int vertical_cost   = abs(startNode->Row_i()    - targetNode->Row_i());
    return horizontal_cost + vertical_cost;
}


