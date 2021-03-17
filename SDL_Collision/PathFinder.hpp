//
//  PathFinder.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 20/1/2564 BE.
//

#ifndef PathFinder_hpp
#define PathFinder_hpp

#include <stdio.h>
#include <vector>

#include "Grid.hpp"
#include "Tile.hpp"

class PathFinder{
private:
    Grid* m_grid;
public:
    PathFinder();
    ~PathFinder();
    
    void GetPath(Tile* startNode, Tile* targetNode){
        
        std::vector<class Tile*> openlist;
        std::vector<class Tile*> closedlist;
        
        openlist.push_back(startNode);
        
        Tile* currentNode = startNode;
        currentNode->G() = 0;
        currentNode->H() = 0;
        
        while (!openlist.empty()) {
            //Set Current Node to Node having least F cost//
            for(auto node: openlist){
                if(node->F() < currentNode->F())
                    currentNode = node;
            }
            
            openlist.erase(std::remove(openlist.begin(), openlist.end(), currentNode), openlist.end());
            closedlist.push_back(currentNode);
            
            if(currentNode == targetNode){
                //found path
                break;
            }
            
            currentNode->GetChilds().push_back(m_grid->GetAdjacent_top(currentNode));
            currentNode->GetChilds().push_back(m_grid->GetAdjacent_bottom(currentNode));
            currentNode->GetChilds().push_back(m_grid->GetAdjacent_left(currentNode));
            currentNode->GetChilds().push_back(m_grid->GetAdjacent_right(currentNode));
            
            for(auto child: currentNode->GetChilds()){
                child->SetParent(currentNode);
                
                //if child is in close loop return to for loop//
                for(auto tile: closedlist){
                    if(child->Row_i() == tile->Row_i() && child->Coloum_j() == tile->Coloum_j()){
                        return;
                    }
                }
                //calculate cost//
                child->G() = child->GetParent()->G() + 1;
                child->H() = m_grid->CalculateMahattanDistance(child, targetNode);
                
                //Child is already in openList
                //if child.position is in the openList's nodes positions
                //if the child.g is higher than the openList node's g
                //continue to beginning of for loop

                openlist.push_back(child);
            }
        }
    }
};

#endif /* PathFinder_hpp */
