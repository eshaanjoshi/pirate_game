#include "../include/player.hpp"
#include "../include/text_objects.hpp"
#define STEP 1.5f

Player::Player(sf::Shape *s, float xoff, float yoff, float m):Sprite(s, xoff, yoff, m, PLAYER_T)
{
    in_conversation = false;
}

void Player::set_event(sf::Event *evnt)
{
    e = evnt;
}

void Player::generate_text(string s)
{
    //printf("Called once\n");
    TextObject **t = get_text("talker");
    //printf("frame count : %lu\n", get_frame_count());
    if((t!=NULL))
    {
        //printf("thing\n");
        (*t)->change_string(s);
    }
}

int Player::player_controller() 
{
    //float slowed_move = (touch_ground ? 1.0 : 0.5)*STEP;
    float slowed_move = STEP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && collide_x != -1 && !in_conversation)
    {
        //(*texture).move(-slowed_move, 0.0f);
        staged_move = sf::Vector2f(-slowed_move, staged_move.y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)&&collide_x != 1&& !in_conversation)
    {
        //(*texture).move(slowed_move, 0.0f);
        staged_move = sf::Vector2f(slowed_move, staged_move.y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)&&collide_y != -1&& !in_conversation)
    {
        //(*texture).move(0.0f, -slowed_move);
        staged_move = sf::Vector2f(staged_move.x, -slowed_move);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)&&collide_y != 1&& !in_conversation)
    {
        //(*texture).move(0.0f, slowed_move);
        staged_move = sf::Vector2f(staged_move.x, slowed_move);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)&&is_interacting)
    {
        TextObject **t = get_text("talker");
        printf("frame count : %lu\n", get_frame_count());
        if((t!=NULL)&&get_frame_count()>15)
        {
            printf("HERE!\n");
            switch((*t)->enabled)
            {
                case ENABLED:
                    //(*t)->enabled = DISABLED;
                    (*t)->set_text_state(DISABLED);
                    reset_frame_count();
                    in_conversation = false;
                    break;   
                case DISABLED:
                    //(*t)->enabled = ENABLED;
                    (*t)->set_text_state(ENABLED);
                    reset_frame_count();
                    in_conversation = true;
                    printf("begin\n");
                    break;
            }
        }
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
    update_collider_pos();
    gravity();
    collide_x = 0;
    collide_y = 0;
    pos = texture->getPosition();
    //printf("texture %f %f\n", texture->getPosition().x, texture->getPosition().y);
    //printf("position %f %f\n", pos.x, pos.y);
    //printf("player collider %f %f\n", collider->left, collider->top);
    
    if (out_of_bounds())
    {
        texture->setPosition(10.0f, 10.0f);
        velocity = sf::Vector2f(0.0f, 0.0f);
    }
    frame_counter++;
}

