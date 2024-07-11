
#include "Sprite.hpp"

#define FORCE_MODIFIER 100000.0f 
Sprite::Sprite(sf::RenderWindow *wi, sf::RectangleShape *p)
{
    w = wi;
    p = p;
    sf::RectangleShape s = *p;
    printf("%p\n", p);
    fx = 0.0f;
    fy = 0.0f;
    vx = 0.0f;
    vy = 0.0f;
    has_gravity_enabled = false;
}

sf::RectangleShape *Sprite::get_object()
{
    return p;
}

void Sprite::set_velocity(float x, float y)
{
    vx = (x/FORCE_MODIFIER);
    vy = (y/FORCE_MODIFIER);
}

void Sprite::set_force(float x, float y)
{
    fx = x;
    fy = y;
}


void Sprite::gravity()
{
    vx = vx + (fx/FORCE_MODIFIER);
    vy = vy + (fy/FORCE_MODIFIER);
    (*p).move(vx, vy);
}

void Sprite::FixedUpdate()
{
    if(has_gravity_enabled)
    {
        gravity();
    }
}