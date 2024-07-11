#ifndef SPRITE
#define SPRITE
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class Sprite:public GameObject{

public:
    Sprite(sf::RenderWindow *wi, sf::RectangleShape *p);
    void FixedUpdate() override;
    sf::RectangleShape *get_object();
    sf::RectangleShape *p;
    sf::RenderWindow *w;
    bool has_gravity_enabled;
    void set_force(float x, float y);
    void set_velocity(float x, float y);
    void gravity();

};

#endif