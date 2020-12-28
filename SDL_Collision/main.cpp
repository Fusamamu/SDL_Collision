//
//  main.cpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 22/12/2563 BE.
//

#include <iostream>
#include <vector>
#include <math.h>
#include "SDL2/SDL.h"

#include "GameEngine.hpp"
#include "Vector2D.hpp"
#include "GameObject.hpp"
#include "AABBCollision.hpp"



void StayWithinFrame(GameObject* go, float left, float right, float top, float bottom){
    if(go->GetMax_X() > right || go->GetMin_X() < left){
        Vector2D vec = go->GetDirection();
        vec.x *= -1;
        go->SetDirection(vec);
    }

    if(go->GetMin_Y() > bottom || go->GetMax_Y() < top ){
        Vector2D vec = go->GetDirection();
        vec.y *= -1;
        go->SetDirection(vec);
    }
}


void OnCollisionResponse(GameObject* A, GameObject* B){
    Vector2D previousPos;
    
//    if(CheckCollision(A, B, &previousPos)){
//        if(A->IsCollided()){
//
//            if(A->GetMax_X() > B->GetMin_X() &&
//               A->GetMin_X() < B->GetMax_X() &&
//               A->GetPosition().y < B->GetMin_Y() &&
//               A->GetPosition().y > B->GetMax_Y()
//               ){
//
//                Vector2D dir = A->GetDirection();
//                dir.x *= -1;
//                A->SetDirection(dir);
//            }
//
//            if(A->GetMax_Y() < B->GetMin_Y() &&
//               A->GetMin_Y() > B->GetMax_Y() &&
//               A->GetPosition().x > B->GetMin_X()&&
//               A->GetPosition().x < B->GetMax_X()
//               ){
//
//                Vector2D dir = A->GetDirection();
//                dir.y *= -1;
//                A->SetDirection(dir);
//            }
//        }
//    }
}




int main(int argc, const char * argv[]) {
    
    GameEngine* GE = new GameEngine;
    GE->Init();
    GE->LoadAssets();
    GE->RunLoop();
    GE->ShutDown();
    
    return 0;
}
