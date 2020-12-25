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
#include "SDL2/SDL.h"
#include "Vector2D.hpp"
#include "Frame.h"



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
    float& Pos_X() { return m_position.x; }
    float& Pos_Y() { return m_position.y; }
    
    
    void SetSpeed(float speed) { m_speed = speed; }
    const float GetSpeed() const { return m_speed; }
    
    void SetDirection(const Vector2D& dir) { m_direction = dir; }
    Vector2D GetDirection() { return m_direction.Normalized(); }
    
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
    
    bool& IsCollided() { return isCollided; }
    
private:
    SDL_Renderer* m_renderer;
    
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
    
    SDL_Rect m_desRect;
    SDL_Rect m_srcRect;
    
    bool isCollided;
};

#endif /* GameObject_hpp */
