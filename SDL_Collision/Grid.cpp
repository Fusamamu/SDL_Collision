//
//  Grid.cpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 26/12/2563 BE.
//

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
            Tile* t = new Tile(m_ge->GetRenderer());
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



