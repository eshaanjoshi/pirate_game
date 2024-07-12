#include "../include/sprite.hpp"
#include "../include/gameobject.hpp"
#include "../include/global.hpp"
#include <SFML/Graphics.hpp>
#define FRAME_RATE_MOD 1000.0f

Sprite::Sprite(sf::Shape *s):GameObject()
{
    texture = s;
    velocity = sf::Vector2f(0.0f, 0.0f);
    force = sf::Vector2f(0.0f, 0.0f);
    gravity_enabled = false;
}

sf::Shape *Sprite::get_texture()
{
    return texture;
}

void Sprite::set_gravity(bool g)
{
    gravity_enabled = g;
}

void Sprite::set_velocity(float x, float y)
{
    velocity = sf::Vector2f(x/FRAME_RATE_MOD, y/FRAME_RATE_MOD);
}

void Sprite::set_force(float x, float y)
{
    force = sf::Vector2f(x, y);
}

void Sprite::gravity()
{
    if(gravity_enabled)
    {
        float vx = velocity.x;
        float vy = velocity.y;
        float fx = force.x;
        float fy = force.y;
        //printf("%f %f %f %f\n", vx, vy, fx, fy);
        vx = vx + (fx/FRAME_RATE_MOD);
        vy = vy + (fy/FRAME_RATE_MOD);
        velocity = sf::Vector2f(vx, vy);
        (*texture).move(vx, vy);
    }
}

void Sprite::FixedUpdate()
{
    gravity();
}