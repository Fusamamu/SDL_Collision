//
//  BoxCollider.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 31/12/2563 BE.
//

#ifndef BoxCollider_hpp
#define BoxCollider_hpp

#include <stdio.h>
#include "Component.hpp"
#include "Frame.h"

class BoxCollider: public Component{
public:
    BoxCollider(class GameObject* owner);
    ~BoxCollider();
    
    const Frame& Frame(){ return m_frame; }
    
    void ResolveOverlap();
    
private:
    struct Frame m_frame;
};

#endif /* BoxCollider_hpp */
