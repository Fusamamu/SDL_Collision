//
//  AABBCollision.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 24/12/2563 BE.
//

#ifndef AABBCollision_hpp
#define AABBCollision_hpp

#include <stdio.h>
#include <math.h>
#include "GameObject.hpp"
#include "Frame.h"

class AABBCollision{
public:
    AABBCollision(){};
    ~AABBCollision(){};
    
    enum type{
      SAT,
      MINKOWSKI,
    };
    
    void GetFrameConstraint(class GameObject* go, const Frame& frame){
        if(go->GetMax_X() > frame.right){
            go->Pos_X() = frame.right - go->GetWidth()/2;
        }
        if (go->GetMin_X() < frame.left) {
            go->Pos_X() = frame.left + go->GetWidth()/2;
        }
        if(go->GetMax_Y() < frame.top){
            go->Pos_Y() = frame.top + go->GetHeight()/2;
        }
        if(go->GetMin_Y() > frame.bottom){
            go->Pos_Y() = frame.bottom - go->GetHeight()/2;
        }
    }
    
    bool OverlapCollisionCheck(GameObject* A, GameObject* B){
        bool isCollided = false;
        
        if(A->Frame().right > B->Frame().left &&
           A->Frame().left < B->Frame().right &&
           A->Frame().bottom > B->Frame().top &&
           A->Frame().top < B->Frame().bottom){
            isCollided = true;
        }
        
        A->IsCollided() = isCollided;
        B->IsCollided() = isCollided;
        A->OnCollided();
        B->OnCollided();
        
        return isCollided;
    }
    
    void DiscreteResolution(GameObject* A, GameObject* B){
        if (A->GetDirection().x > 0) {
            A->Pos_X() = B->Frame().left - A->GetWidth()/2;
            return;
        }
        if (A->GetDirection().x < 0) {
            A->Pos_X() = B->Frame().right + A->GetWidth()/2;
            return;
        }
        if(A->GetDirection().y > 0) {
            A->Pos_Y() = B->Frame().top - A->GetHeight()/2;
            return;
        }
        if(A->GetDirection().y < 0) {
            A->Pos_Y() = B->Frame().bottom + A->GetHeight()/2;
            return;
        }
    }
    
    bool MinkowskiCollisionCheck(GameObject* A, GameObject* B, Vector2D* penetration){
        Frame minkowskiFrame;
        minkowskiFrame.bottom   = A->Frame().bottom - B->Frame().top;
        minkowskiFrame.top      = A->Frame().top    - B->Frame().bottom;
        minkowskiFrame.left     = A->Frame().left   - B->Frame().right;
        minkowskiFrame.right    = A->Frame().right  - B->Frame().left;
        
        if (minkowskiFrame.left <= 0 && minkowskiFrame.right >= 0 &&
            minkowskiFrame.top <=0 && minkowskiFrame.bottom >= 0) {
            
            A->IsCollided() = true;
            B->IsCollided() = true;
            A->OnCollided();
            B->OnCollided();
            
            float min = abs(minkowskiFrame.left);
            Vector2D tempPenetration (min, 0);
            
            if (abs(minkowskiFrame.right) < min) {
                min = abs(minkowskiFrame.right);
                tempPenetration = Vector2D(-min, 0);
            }
            
            if (abs(minkowskiFrame.top) < min) {
                min = abs(minkowskiFrame.top);
                tempPenetration = Vector2D(0, min);
            }

            if(abs(minkowskiFrame.bottom) < min){
                min = abs(minkowskiFrame.bottom);
                tempPenetration = Vector2D(0, -min);
            }
            
            *penetration = tempPenetration;
           
            
            return true;
        }
        
        A->IsCollided() = false;
        B->IsCollided() = false;
        
        A->OnCollided();
        B->OnCollided();
        
        
        return false;
    }
};

#endif /* AABBCollision_hpp */
