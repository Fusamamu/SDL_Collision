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

struct Vector2D{
public:
    float x, y;
    
    Vector2D():x(0), y(0){}
    Vector2D(int xx, int yy):x(xx), y(yy){}
    ~Vector2D(){}
    
    Vector2D operator+ (Vector2D rhs) const {
        return Vector2D(x + rhs.x, y + rhs.y);
    }
    
    
    Vector2D operator- (Vector2D rhs) const {
        return Vector2D(x - rhs.x, y - rhs.y);
    }
    
    Vector2D& operator+= (Vector2D rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    
    Vector2D& operator-= (Vector2D rhs){
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    
    Vector2D& operator= (const Vector2D& rhs) {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
    
    Vector2D& operator* (float k) {
        x *= k;
        y *= k;
        return *this;
    }
    
    Vector2D& Normalized() {
        int denom = sqrt(x*x + y*y);
        x = x/denom;
        y = y/denom;
        return *this;
    }
};

struct GameObject{
public:
    GameObject(SDL_Renderer* rend):
        m_renderer(rend),
        m_width(20),
        m_height(20),
        m_position(Vector2D(50,50)),
        m_center(Vector2D(m_width/2, m_height/2)),
        m_scale(1),
        m_angle(0),
        m_color({255, 255, 255, 255}),
        m_speed(50),
        m_direction(Vector2D(1,1))
    {
        m_srcRect = {0, 0, 20, 20};
        m_desRect = {static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_width, m_height};
    }
    ~GameObject(){ std::cout<< "Game Object Destroyed" << std::endl; }
    
    void Render(){
        int x = m_position.x - m_center.x;
        int y = m_position.y - m_center.y;
        m_desRect = {x, y, m_width, m_height};
        
        SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, 255);
        SDL_RenderFillRect(m_renderer, &m_desRect);
    }
    
    void Move(float deltaTime){
        m_position += GetDirection() * GetSpeed() * deltaTime;
    }
    
    void OnCollided(){
        if(isCollided){
            m_color = {235, 64, 52, 255};
        }else{
            m_color = {255, 255, 255, 255};
        }
    }
    

    void SetWidth(int w) { m_width = w; }
    void SetHeight(int h) { m_height = h; }
    void SetSize(int w, int h) {
        m_width = w;
        m_height = h;
        SetCenter(m_width/2, m_height/2); }
    void SetCenter(int x, int y) { m_center = Vector2D(x, y); }
    
    void SetPosition(const Vector2D& pos) { m_position = pos; }
    const Vector2D& GetPosition() { return m_position; }
    void SetSpeed(float speed) { m_speed = speed; }
    const float GetSpeed() const { return m_speed; }
    
    void SetDirection(const Vector2D& dir) { m_direction = dir; }
    Vector2D GetDirection() { return m_direction.Normalized(); }
    
    float GetMin_X() { return  m_position.x - m_width/2; }
    float GetMax_X() { return  m_position.x + m_width/2; }
    float GetMin_Y() { return  m_position.y + m_height/2; }
    float GetMax_Y() { return  m_position.y - m_height/2; }
    
    bool& IsCollided() { return isCollided; }
    
private:
    SDL_Renderer* m_renderer;
    
    int m_width;
    int m_height;
    Vector2D m_position;
    Vector2D m_center;
    float m_scale;
    float m_angle;
    SDL_Color m_color;
    
    float m_speed;
    Vector2D m_direction;
    
    SDL_Rect m_desRect;
    SDL_Rect m_srcRect;
    
    bool isCollided;
    
};


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

bool CheckCollision(GameObject* A, GameObject* B)
{
    bool isCollided;
    
    bool overlap_x;
    bool overlap_y;
    
    if(A->GetMax_X() < B->GetMin_X() || A->GetMin_X() > B->GetMax_X()){
        overlap_x = false;
    }else{
        overlap_x = true;
    }
    
    if(A->GetMax_Y() > B->GetMin_Y() || A->GetMin_Y() < B->GetMax_Y()){
        overlap_y = false;
    }else{
        overlap_y = true;
    }
    
    if(overlap_x && overlap_y){
        isCollided = true;
        A->IsCollided() = true;
        B->IsCollided() = true;
        return isCollided;
    }else{
        isCollided = false;
        A->IsCollided() = false;
        B->IsCollided() = false;
        return isCollided;
    }
    

}

void OnCollisionResponse(GameObject* A, GameObject* B){
    if(CheckCollision(A, B)){
        if(A->IsCollided()){

            if(A->GetMax_X() > B->GetMin_X() &&
               A->GetMin_X() < B->GetMax_X() &&
               A->GetPosition().y < B->GetMin_Y() &&
               A->GetPosition().y > B->GetMax_Y()
               ){
                
                Vector2D dir = A->GetDirection();
                dir.x *= -1;
                A->SetDirection(dir);
            }
                
            if(A->GetMax_Y() < B->GetMin_Y() &&
               A->GetMin_Y() > B->GetMax_Y() &&
               A->GetPosition().x > B->GetMin_X()&&
               A->GetPosition().x < B->GetMax_X()
               ){

                Vector2D dir = A->GetDirection();
                dir.y *= -1;
                A->SetDirection(dir);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    if(!SDL_Init(SDL_INIT_VIDEO))
        std::cout<< "Failed to init SDL_Init!" << std::endl;
    
    const int SCREEN_WIDTH  = 640;
    const int SCREEN_HEIGHT = 480;
    
    SDL_Window* window = SDL_CreateWindow("Collision Engine", NULL, NULL, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    
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
    
    gameObjectPool.push_back(go_A);
    gameObjectPool.push_back(go_B);
    
    bool GameRunning = true;
    while (GameRunning) {
        SDL_Event ev;
        SDL_PollEvent(&ev);
        
        switch (ev.type) {
            case SDL_QUIT:
                GameRunning = false;
                break;
        }
        
        for(auto go: gameObjectPool){
            go->Move(GetDeltaTime());
            StayWithinFrame(go, 0, 640, 0, 480);
        }
           
        OnCollisionResponse(go_A, go_B);
        OnCollisionResponse(go_B, go_A);
        
        go_A->OnCollided();
        go_B->OnCollided();
        
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
