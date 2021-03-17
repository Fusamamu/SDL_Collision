//
//  GameObject.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 24/12/2563 BE.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "Vector2D.hpp"
#include "Frame.h"
#include "Component.hpp"

struct GameObject{
public:
    GameObject(SDL_Renderer* rend);
    ~GameObject();
    
    enum RENDERTYPE{
        SOLID,
        WIREFRAME,
    };
    
    void Awake();
    void Start();
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Render();
    
    template<typename T> std::shared_ptr<T> AddComponent();
    template<typename T> std::shared_ptr<T> GetComponent();
    
    void Move(float deltaTime);
    void OnCollided();
    
    void SetWidth(int w) { m_width = w; }
    void SetHeight(int h) { m_height = h; }
    void SetSize(int w, int h) { m_width = w; m_height = h; SetCenter(m_width/2, m_height/2); }
    void SetCenter(int x, int y) { m_center = Vector2D(x, y); }
    
    void SetPosition(const Vector2D& pos) { m_position = pos; }
    const Vector2D& GetPosition() { return m_position; }
    float& Pos_X() { return m_position.x; }
    float& Pos_Y() { return m_position.y; }
    
    
    void SetSpeed(float speed) { m_speed = speed; }
    const float& GetSpeed() const { return m_speed; }
    
    void SetDirection(const Vector2D& dir) { m_direction = dir; }
    Vector2D GetDirection() { return m_direction.Normalized(); }
    
    void SetColor(SDL_Color c) { m_color = c; }
    
    float GetWidth() { return m_width;}
    float GetHeight() {return m_height;}
    
    float GetMin_X() { return  m_position.x - m_width/2; }
    float GetMax_X() { return  m_position.x + m_width/2; }
    float GetMin_Y() { return  m_position.y + m_height/2; }
    float GetMax_Y() { return  m_position.y - m_height/2; }
    
    const Frame& Frame() {
        m_frame = { m_position.y - m_height/2,
                    m_position.y + m_height/2,
                    m_position.x - m_width/2,
                    m_position.x + m_width/2
        };
        return m_frame;
    }
    
    const SDL_Rect& GetDestRect() const { return m_desRect; }
    
    bool& IsCollided() { return isCollided; }
    
private:

    SDL_Renderer* m_renderer;
    RENDERTYPE m_renderType;
    
    int m_width;
    int m_height;
    
    struct Frame m_frame;
    
    Vector2D m_position;
    Vector2D m_center;
    
    float m_scale;
    float m_angle;
    
    SDL_Color m_color;
    
    float m_speed;
    Vector2D m_direction;
    Vector2D m_velocity;
    
    SDL_Rect m_desRect;
    SDL_Rect m_srcRect;
    
    bool isCollided;
    
    std::vector<std::shared_ptr<Component>> m_components;
};

#endif /* GameObject_hpp */
