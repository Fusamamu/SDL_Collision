//
//  GameObject.cpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 24/12/2563 BE.
//

#include "GameObject.hpp"


GameObject::GameObject(SDL_Renderer* rend):
    m_renderer(rend),
    m_renderType(WIREFRAME),
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

GameObject::~GameObject(){
    std::cout<< "Game Object Destroyed" << std::endl;
}

void GameObject::Awake(){
    for(unsigned long i = m_components.size() - 1; i >= 0; i--){
        m_components[i]->Awake();
    }
}

void GameObject::Start(){
    for (unsigned long i = m_components.size() - 1 ; i >= 0; i-- ) {
        m_components[i]->Start();
    }
}

void GameObject::Update(float deltaTime){
    for (unsigned long i = m_components.size() - 1; i >= 0; i--) {
        m_components[i]->Update(deltaTime);
    }
}

void GameObject::LateUpdate(float deltaTime){
    for (unsigned long i = m_components.size() - 1; i >= 0; i--){
        m_components[i]->LateUpdate(deltaTime);
    }
}

void GameObject::Render(){
    int x = m_position.x - m_center.x;
    int y = m_position.y - m_center.y;
    m_desRect = {x, y, m_width, m_height};
    
    SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, 255);
    if(m_renderType == WIREFRAME)
        SDL_RenderDrawRect(m_renderer, &m_desRect);
    if(m_renderType == SOLID){
        SDL_RenderFillRect(m_renderer, &m_desRect);
    }
    
//    for (unsigned long i = m_components.size() - 1; i >= 0; i--){
//        m_components[i]->Render(m_renderer);
//    }
}

template<typename T>
std::shared_ptr<T> GameObject::AddComponent(){
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    
    for(auto& existingComp: m_components){
        if (std::dynamic_pointer_cast<T>(existingComp)) {
            return std::dynamic_pointer_cast<T>(existingComp);
        }
    }
    
    std::shared_ptr<T> newComp = std::make_shared<T>(this);
    m_components.push_back(newComp);
    
    return newComp;
}

template<typename T>
std::shared_ptr<T> GameObject::GetComponent(){
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    
    for (auto& existingComp: m_components) {
        if (std::dynamic_pointer_cast<T>(existingComp)) {
            return existingComp;
        }
    }
    
    return nullptr;
}


void GameObject::Move(float deltaTime){
    m_position += GetDirection() * GetSpeed() * deltaTime;
}


void GameObject::OnCollided(){
    if(isCollided){
        m_color = {235, 64, 52, 255};
    }else{
        m_color = {255, 255, 255, 255};
    }
}
