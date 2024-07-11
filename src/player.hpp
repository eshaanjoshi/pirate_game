
#ifndef PLAYER
#define PLAYER


#include <time.h>
#include "Sprite.hpp"
#include <SFML/Graphics.hpp>

class Player:public Sprite{

public:
    Player(sf::RenderWindow *wi, sf::RectangleShape *p);
    void FixedUpdate() override;    
private:
    int player_move_mouse();
    int player_controller(sf::Event *evnt);

};
#endif