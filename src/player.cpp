

#include "player.hpp"

Player::Player(sf::RenderWindow *wi, sf::RectangleShape *pl) : Sprite(wi, pl)
{
    p = pl;
    w = wi;
    evnt = *evnt;
    fx = 0.0f;
    fy = 0.0f;
    vx = 0.0f;
    vy = 0.0f;
}




int Player::player_controller(sf::Event *evnt)
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            (*p).move(-0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            (*p).move(0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            (*p).move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            (*p).move(0.0f, 0.1f);
        }
        if ((*evnt).type == sf::Event::KeyPressed)
        {
            printf(":(\n");
            if ((*evnt).key.code == sf::Keyboard::R)
            {
                set_velocity(0.0f, 0.0f);
                has_gravity_enabled = !has_gravity_enabled;
            }
        }
    return 0;
}


int Player::player_move_mouse()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*w);
        (*p).setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }
    return 0;
}

void Player::FixedUpdate() {
    
    //printf("%f %f %f %f\n", fx, fy, vx, vy);
    gravity();
    player_controller(&evnt);
    player_move_mouse();
}
