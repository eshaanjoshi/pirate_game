#include <SFML/Graphics.hpp>
#include "sprite.hpp"
#ifndef PLAYER
#define PLAYER

class Player:public Sprite{
public:
    Player(sf::Shape *s, float xoff, float yoff, float m);
    void FixedUpdate();
    void set_event(sf::Event *evnt);
    
protected:
    sf::Event *e;
    int player_controller();
private:
    sf::Vector2f prev;
    bool out_of_bounds();
};

#endif