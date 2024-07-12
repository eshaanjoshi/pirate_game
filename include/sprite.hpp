
#ifndef SPRITE
#define SPRITE
#include <SFML/Graphics.hpp>
#include "gameobject.hpp"

class Global;

class Sprite:public GameObject{
public:
    Sprite(sf::Shape *s);
    sf::Shape *get_texture();
    void set_gravity(bool g);
    void set_force(float x, float y);
    void set_velocity(float x, float y);
    virtual void FixedUpdate();
protected:
    sf::Shape *texture;
    bool gravity_enabled;
    void gravity();
    sf::Vector2f velocity;
    sf::Vector2f force;
};

#endif