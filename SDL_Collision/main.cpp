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

#include "Vector2D.hpp"
#include "GameObject.hpp"
#include "AABBCollision.hpp"


float tickCounts = 0;

float GetDeltaTime(){
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), tickCounts + 16));
    
    float deltaTime = (SDL_GetTicks() - tickCounts / 1000.0f);
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    tickCounts = SDL_GetTicks();
    
    return deltaTime;
}

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


void ProcessInput(GameObject* go, const Uint8* keyStates){
    if(keyStates[SDL_SCANCODE_LEFT]){
        go->SetDirection(Vector2D(-1,0));
        go->SetSpeed(100);
        go->Move(GetDeltaTime());
        
    }
    if(keyStates[SDL_SCANCODE_RIGHT]){
        go->SetDirection(Vector2D(1,0));
        go->SetSpeed(100);
        go->Move(GetDeltaTime());
    }
    if(keyStates[SDL_SCANCODE_UP]){
        go->SetDirection(Vector2D(0,-1));
        go->SetSpeed(100);
        go->Move(GetDeltaTime());
    }
    if(keyStates[SDL_SCANCODE_DOWN]){
        go->SetDirection(Vector2D(0,1));
        go->SetSpeed(100);
        go->Move(GetDeltaTime());
    }
}

int main(int argc, const char * argv[]) {
    
    if(!SDL_Init(SDL_INIT_VIDEO))
        std::cout<< "Failed to init SDL_Init!" << std::endl;
    
    const int SCREEN_WIDTH  = 640;
    const int SCREEN_HEIGHT = 480;
    
    SDL_Window* window = SDL_CreateWindow("Collision Engine", NULL, NULL, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    
    AABBCollision aabbCollision;
    
    std::vector<GameObject*> gameObjectPool;
    
    GameObject* go_A = new GameObject(renderer);
    go_A->SetSize(20, 20);
    go_A->SetPosition(Vector2D(50, 100));
    go_A->SetDirection(Vector2D(1, 1));
    go_A->SetSpeed(120);
    
    GameObject* go_B = new GameObject(renderer);
    go_B->SetSize(150, 150);
    go_B->SetPosition(Vector2D(250, 140));
    go_B->SetDirection(Vector2D(-1, 1));
    go_B->SetSpeed(0);
    
    GameObject* go_C = new GameObject(renderer);
    go_C->SetSize(100, 100);
    go_C->SetPosition(Vector2D(200, 200));
    go_C->SetSpeed(0);

    
    
    gameObjectPool.push_back(go_A);
    gameObjectPool.push_back(go_B);
    gameObjectPool.push_back(go_C);
    

    bool GameRunning = true;
    while (GameRunning) {
        SDL_Event ev;
        SDL_PollEvent(&ev);
        
        switch (ev.type) {
            case SDL_QUIT:
                GameRunning = false;
                break;
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                break;
        }
        
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        ProcessInput(go_C, keystates);
        
        aabbCollision.GetFrameConstraint(go_C, {0, 480, 0, 640});
//        bool isCollided = aabbCollision.OverlapCollisionCheck(go_C, go_B);
//        bool isCollidedWithA = aabbCollision.OverlapCollisionCheck(go_C, go_A);
//        if (isCollided) {
//            aabbCollision.DiscreteResolution(go_C, go_B);
//        }
        Vector2D v;
        aabbCollision.MinkowskiCollisionCheck(go_C, go_B, &v);
        std::cout<< "petnetration:" << v.x << ";" << v.y << std::endl;
        Vector2D newPos = go_C->GetPosition() + v;
        go_C->SetPosition(newPos);
        
//        if (isCollidedWithA) {
//            aabbCollision.DiscreteResolution(go_C, go_A);
//        }
        
        SDL_SetRenderDrawColor(renderer, 255, 198, 84, 255);
        SDL_RenderClear(renderer);
        
        for(auto go: gameObjectPool){
            go->Render();
        }
        
        SDL_RenderPresent(renderer);
    }
    
    delete go_A;
    delete go_B;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
