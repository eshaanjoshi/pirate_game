#include "../include/player.hpp"
#define STEP 1.0f

Player::Player(sf::Shape *s, float xoff, float yoff, float m):Sprite(s, xoff, yoff, m, PLAYER_T)
{

}

void Player::set_event(sf::Event *evnt)
{
    e = evnt;
}

int Player::player_controller() 
{
    //float slowed_move = (touch_ground ? 1.0 : 0.5)*STEP;
    float slowed_move = STEP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        (*texture).move(-slowed_move, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        (*texture).move(slowed_move, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        (*texture).move(0.0f, -slowed_move);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        (*texture).move(0.0f, slowed_move);
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
    if (touch_ground && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        velocity = sf::Vector2f(0.0f, -1.0f);
        touch_ground = false;
    }
    return 0;
}

bool Player::out_of_bounds()
{
    bool b =  (pos.x > 512.0f || pos.y > 512.0f);
    b = b ||  (pos.x < 0.0f);
    if (b) printf("OFF SCREEN!\n");
    return b;
}

void Player::FixedUpdate(){
    player_controller();
    gravity();
    pos = texture->getPosition();
    //printf("texture %f %f\n", texture->getPosition().x, texture->getPosition().y);
    //printf("position %f %f\n", pos.x, pos.y);
    //printf("player collider %f %f\n", collider->left, collider->top);
    update_collider_pos();
    if (out_of_bounds())
    {
        texture->setPosition(10.0f, 10.0f);
        velocity = sf::Vector2f(0.0f, 0.0f);
    }
}

