#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/sprite.hpp"
#include "include/event_handler.hpp"
#include "include/player.hpp"
#include <X11/Xlib.h> 
#include "include/global.hpp"
#include "include/timer.hpp"
#include "include/window_settings.hpp"
#include <cmath>
#include <csignal>

Global* CreateGlobal()
{
    Global *g = new Global(1);
    return g;
}

int infected;
int killed;

void interact(Sprite *a, Sprite *b){
    if(a->sprite_type==INFECTED_T && b->sprite_type==CLEAN_T)
    {
        if(rand() % 100 == 0)
        {
            b->sprite_type = INFECTED_T;
            b->color = sf::Color::Red;
            b->reset_frame_count();
        }
    }
    if(a->sprite_type==CLEAN_T && b->sprite_type==INFECTED_T)
    {
        if(rand() % 100 == 0)
        {
            a->sprite_type = INFECTED_T;
            a->color = sf::Color::Red;
            a->reset_frame_count();
        }
    }
    if(a->sprite_type==RECOVERED_T && b->sprite_type==CLEAN_T)
    {
        if(rand() % 500 == 0)
        {
            b->sprite_type = INFECTED_T;
            b->color = sf::Color::Red;
            b->reset_frame_count();
        }
    }
    if(a->sprite_type==RECOVERED_T && b->sprite_type==INFECTED_T)
    {
        if(rand() % 500 == 0)
        {
            a->sprite_type = INFECTED_T;
            a->color = sf::Color::Red;
            a->reset_frame_count();
        }
    }

}

void update(Sprite *a)
{
    if(a->get_frame_count() > 180 && a->sprite_type == INFECTED_T)
    {
        if(rand() % 5 != 0){
            a->sprite_type = RECOVERED_T;
            a->reset_frame_count();
            a->color = sf::Color::Magenta;
        }
        else{
            a->sprite_type = DEAD_T;
            a->color = sf::Color::Black;
            a->set_velocity(0.0f, 0.0f);
            a->mass = -1.0f;
        }
    }
    if(a->get_frame_count() > 180 && a->sprite_type == RECOVERED_T)
    {
        if(rand() % 10 != 0){
            a->sprite_type = CLEAN_T;
            a->color = sf::Color::Green;
            a->reset_frame_count();
        }
    }
}

Player *create_player(Global *g, float x, float y)
{
    sf::RectangleShape *player = new sf::RectangleShape(sf::Vector2f(x, y));
    player->setFillColor(sf::Color::Red);
    player->setOrigin(x/2, y/2);
    player->setPosition(50.0f, 50.0f);
    Player *p = new Player(player, x, y, 20.0f);
    p->set_gravity(false);
    p->set_force(0.0f, 10.0f);
    g->Instantiate(p);
    p->elasticity = 0.5f;
    p->set_custom_collider(50.0f - (x/2), 50.0f - (y/2), x, y);
    //p->collider = new sf::FloatRect(100.0f, 100.0f, 50.0f, 50.0f);
    return p;
}

Sprite *create_block(Global *g, float x, float y, float xpos, float ypos, float vx, float vy, float e)
{
    sf::RectangleShape *player = new sf::RectangleShape(sf::Vector2f(x, y));
    player->setFillColor(sf::Color::Blue);
    player->setOrigin(x/2, y/2);
    player->setPosition(xpos, ypos);
    Sprite *p = new Sprite(player, x, x, 20.0f, NONE_T);
    p->set_gravity(false);
    p->set_velocity(vx, vy);
    p->set_force(0.0f, 10.0f);
    g->Instantiate(p);
    p->elasticity = sqrt(e);
    p->interact = &interact;
    // p->sprite_type = CLEAN_T;
    // p->color = sf::Color::Green;
    // if (rand() % 10 == 0){
    //     p->sprite_type = INFECTED_T;
    //     p->color = sf::Color::Red;
    // }
    p->api_update = &update;
    return p;
}

Sprite* create_platform(Global *g, float x, float y, float xpos, float ypos)
{
    sf::RectangleShape *sprite = new sf::RectangleShape(sf::Vector2f(x, y));
    sprite->setFillColor(sf::Color::Green);
    sprite->setOrigin(x/2, y/2);
    sprite->setPosition(xpos, ypos);
    Sprite *p = new Sprite(sprite, x, y, -1.0f, GROUND_T);
    p->set_gravity(false);
    p->set_force(0.0f, 0.0f);
    g->Instantiate(p);
    return p;
}

void multi_block_create(Global *g)
{
    int locx = 10 + rand() % 480;
    int locy = 10 + rand() % 480;
    int velx = -10 + rand() % 100;
    int vely = -10 + rand() % 100;
    create_block(g, 50.0f, 50.0f, locx, locy, velx, vely, 1.0f);
}

void multi_block_create_2(Global *g, int i, int j)
{
    int locx = 10 + i*8;
    int locy = 10 + j*8;;
    int velx = -10 + rand() % 40;
    int vely = -10 + rand() % 40;
    create_block(g, 5.0f, 5.0f, locx, locy, velx, vely, 0.99f);
}

int main()
{
    XInitThreads();
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Tutorial", sf::Style::Close|sf::Style::Titlebar);
    

    Global *g = CreateGlobal();
    create_player(g, 50.0f, 50.0f);
    // multi_block_create(g);
    // multi_block_create(g);
    // multi_block_create(g);
    // multi_block_create(g);
    // multi_block_create(g);
    // multi_block_create(g);
    // for(int i = 0; i < 40; i++)
    // {
    //     for(int j = 0; j < 40; j++)
    //     {
    //         multi_block_create_2(g, i, j);
    //     }
    // }
    uint64_t init_time = timer();
    create_platform(g, 512.0f, 10.0f, 256.0f, 512.0f);
    create_platform(g, 512.0f, 10.0f, 256.0f, 0.0f);
    create_platform(g, 10.0f, 512.0f, 0.0f, 256.0f);
    create_platform(g, 10.0f, 512.0f, 512.0f, 256.0f);
    int count = 0;
    g->Run();
    while(window.isOpen())
    {
        //multi_block_create(g);
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            handle(&window, &evnt);
        }
        
        g->Draw(&window);
        //if(count > 1000000 && count % 100 == 0) multi_block_create(g);
        count++;
        //window.display();
    }
}