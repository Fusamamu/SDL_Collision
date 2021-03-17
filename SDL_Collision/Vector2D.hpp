//
//  Vector2D.hpp
//  SDL_Collision
//
//  Created by Sukum Duangpattra  on 24/12/2563 BE.
//

#ifndef Vector2D_hpp
#define Vector2D_hpp

#include <stdio.h>

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

#endif /* Vector2D_hpp */
