//
//  GameEngine.cpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 26/12/2563 BE.
//

#include "GameEngine.hpp"
#include "AABBCollision.hpp"
#include "Grid.hpp"

GameEngine::GameEngine():isRunning(true), m_tickCounts(0){
   
}

GameEngine::~GameEngine(){
    
}

void GameEngine::Init(){
    SDL_Init(SDL_INIT_VIDEO);
    
    m_window = SDL_CreateWindow("TopdownShooter(pending title)", NULL, NULL, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

void GameEngine::LoadAssets(){
    
    aabbCollision = new AABBCollision;
    
    go_A = new GameObject(m_renderer);
    go_A->SetSize(20, 20);
    go_A->SetPosition(Vector2D(50, 100));
    go_A->SetDirection(Vector2D(1, 1));
    go_A->SetSpeed(120);
    
    go_B = new GameObject(m_renderer);
    go_B->SetSize(20, 20);
    go_B->SetPosition(Vector2D(250, 140));
    go_B->SetDirection(Vector2D(-1, 1));
    go_B->SetSpeed(0);
    
    go_C = new GameObject(m_renderer);
    go_C->SetSize(20, 20);
    go_C->SetPosition(Vector2D(200, 200));
    go_C->SetSpeed(0);

    m_gameobject_POOL.push_back(go_A);
    m_gameobject_POOL.push_back(go_B);
    m_gameobject_POOL.push_back(go_C);
    
    m_grid = new Grid(25, 15, this);
    m_grid->SetColor({255, 100, 50, 100});
    
    m_quadTree = new QuadTree(1, 5, 0, {0, 0, static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)}, NULL);
}

void GameEngine::RunLoop(){
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void GameEngine::ProcessInput(){
    SDL_Event ev;
    SDL_PollEvent(&ev);
    
    switch (ev.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
            
        default:
            break;
    }
    
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if(keystates[SDL_SCANCODE_LEFT]){
        go_C->SetDirection(Vector2D(-1,0));
        go_C->SetSpeed(100);
        go_C->Move(GetDeltaTime());
    }
    if(keystates[SDL_SCANCODE_RIGHT]){
        go_C->SetDirection(Vector2D(1,0));
        go_C->SetSpeed(100);
        go_C->Move(GetDeltaTime());
    }
    if(keystates[SDL_SCANCODE_UP]){
        go_C->SetDirection(Vector2D(0,-1));
        go_C->SetSpeed(100);
        go_C->Move(GetDeltaTime());
    }
    if(keystates[SDL_SCANCODE_DOWN]){
        go_C->SetDirection(Vector2D(0,1));
        go_C->SetSpeed(100);
        go_C->Move(GetDeltaTime());
    }
}

void GameEngine::Update(){
    aabbCollision->GetFrameConstraint(go_C, {0, 480, 0, 640});

    Vector2D penetration;
    
    if(aabbCollision->MinkowskiCollisionCheck(go_C, go_B, &penetration)){
        Vector2D newPos = go_C->GetPosition() + penetration;
        go_C->IsCollided() = true;
        go_C->SetPosition(newPos);
        
    }else{
        go_C->IsCollided() = false;
    }
    
    go_C->OnCollided();
}

void GameEngine::Render(){
    SDL_SetRenderDrawColor(m_renderer, 255, 198, 84, 255);
    SDL_RenderClear(m_renderer);
    
    m_grid->Render();
    
    for(auto go: m_gameobject_POOL){
        go->Render();
    }
    
    SDL_RenderPresent(m_renderer);
}

void GameEngine::ShutDown(){
    for(auto go: m_gameobject_POOL){
        delete go;
    }
    
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void GameEngine::AddGameObject(class GameObject* go)
{
    
}

void GameEngine::RemoveGameObject(class GameObject* go){
    
}

float GameEngine::GetDeltaTime(){
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_tickCounts + 16));
    
    float deltaTime = (SDL_GetTicks() - m_tickCounts / 1000.0f);
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    m_tickCounts = SDL_GetTicks();
    
    return deltaTime;
}

GameObject* GameEngine::CreateGameObject(){
    GameObject* go = new GameObject(m_renderer);
    go->SetSize(20, 20);
    go->SetPosition(Vector2D(50,50));
    go->SetDirection(Vector2D(1,1));
    go->SetSpeed(20);
    return go;
}

