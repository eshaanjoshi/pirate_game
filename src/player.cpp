#include "../include/player.hpp"
#define STEP 1.0f

Player::Player(sf::Shape *s):Sprite(s)
{

}

void Player::set_event(sf::Event *evnt)
{
    e = evnt;
}

int Player::player_controller()
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        (*texture).move(-STEP, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        (*texture).move(STEP, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        (*texture).move(0.0f, -STEP);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        (*texture).move(0.0f, STEP);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
        prev = force;
        force = sf::Vector2f(0.0f, 0.0f);
        gravity_enabled = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
    {
        force = prev;
        gravity_enabled = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        velocity = sf::Vector2f(0.0f, -0.5f);
    }
    return 0;
}

void Player::FixedUpdate(){
    player_controller();
    gravity();
}

