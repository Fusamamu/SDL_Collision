//
//  GameEngine.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 26/12/2563 BE.
//

#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <iostream>
#include <vector>

#include "SDL2/SDL.h"


class GameEngine{
public:
    GameEngine();
    ~GameEngine();
    void Init();
    void LoadAssets();
    void RunLoop();
    void ProcessInput();
    void Update();
    void Render();
    void ShutDown();
    
//    SDL_Texture* LoadTexture(const char* filePath);
//    SDL_Texture* LoadText(const char* text, const char* font, SDL_Color c);
    
    void AddGameObject(class GameObject* go);
    void RemoveGameObject(class GameObject* go);
    
    SDL_Renderer* GetRenderer() const { return m_renderer; }
    SDL_Window* GetWindow() const { return m_window; }
    
    float GetDeltaTime();
    
    std::vector<class GameObject*>& Get_POOL() { return m_gameobject_POOL; }
    
private:
    SDL_Renderer* m_renderer;
    SDL_Window* m_window;
    const float SCREEN_WIDTH  = 640;
    const float SCREEN_HEIGHT = 480;
    bool isRunning = true;
    
    float m_tickCounts = 0;
    
    std::vector<class GameObject*> m_gameobject_POOL;
    
    class AABBCollision* aabbCollision;
    GameObject* go_A;
    GameObject* go_B;
    GameObject* go_C;
    
    class Grid* m_grid;
    
};


#endif /* GameEngine_hpp */
