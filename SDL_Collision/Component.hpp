//
//  Component.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 28/12/2563 BE.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>
#include "SDL2/SDL.h"
class Component{
public:
    Component(class GameObject* owner): m_owner(owner){}
    ~Component(){}
    
    virtual void Awake(){}
    virtual void Start(){}
    
    virtual void Update(float deltaTime){}
    virtual void LateUpdate(float deltaTime){}
    
    virtual void Render(SDL_Renderer* render);
protected:
    class GameObject* m_owner;
};

#endif /* Component_hpp */
