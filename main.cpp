#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/sprite.hpp"
#include "include/event_handler.hpp"
#include "include/player.hpp"
#include <X11/Xlib.h> 
#include "include/global.hpp"
#include "include/timer.hpp"
#include <cmath>
#include <csignal>

Global* CreateGlobal()
{
    Global *g = new Global(1);
    //g->Run();
    return g;
}



Player *create_player(Global *g, float x, float y)
{
    sf::RectangleShape *player = new sf::RectangleShape(sf::Vector2f(x, y));
    player->setFillColor(sf::Color::Red);
    player->setOrigin(x/2, y/2);
    player->setPosition(50.0f, 50.0f);
    Player *p = new Player(player, x/2, y/2, 20.0f);
    p->set_gravity(true);
    //p->set_velocity(0.0f, 00.0f);
    p->set_force(0.0f, 10.0f);
    g->Instantiate(p);
    p->elasticity = 0.5f;
    return p;
}

Sprite *create_block(Global *g, float x, float y, float xpos, float ypos, float vx, float vy, float e)
{
    sf::RectangleShape *player = new sf::RectangleShape(sf::Vector2f(x, y));
    player->setFillColor(sf::Color::Blue);
    player->setOrigin(x/2, y/2);
    player->setPosition(xpos, ypos);
    Sprite *p = new Sprite(player, x/2, y/2, 20.0f, NONE_T);
    p->set_gravity(false);
    p->set_velocity(vx, vy);
    p->set_force(0.0f, 10.0f);
    g->Instantiate(p);
    p->elasticity = sqrt(e);
    return p;
}

Sprite* create_platform(Global *g, float x, float y, float xpos, float ypos)
{
    sf::RectangleShape *sprite = new sf::RectangleShape(sf::Vector2f(x, y));
    sprite->setFillColor(sf::Color::Green);
    sprite->setOrigin(x/2, y/2);
    sprite->setPosition(xpos, ypos);
    Sprite *p = new Sprite(sprite, x/2, y/2, -1.0f, GROUND_T);
    p->set_gravity(false);
    p->set_force(0.0f, 0.0f);
    g->Instantiate(p);
    return p;
}

void multi_block_create(Global *g)
{
    int locx = 10 + rand() % 480;
    int locy = 10 + rand() % 480;
    int velx = -10 + rand() % 40;
    int vely = -10 + rand() % 40;
    create_block(g, 5.0f, 5.0f, locx, locy, velx, vely, 1.0f);
}

int main()
{
    XInitThreads();
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Close|sf::Style::Titlebar);

    

    Global *g = CreateGlobal();
    //create_player(g, 10.0f, 10.0f);
    for(int i = 0; i < 1; i++)
    {
        multi_block_create(g);
    }
    uint64_t init_time = timer();
    create_platform(g, 512.0f, 10.0f, 256.0f, 512.0f);
    create_platform(g, 512.0f, 10.0f, 256.0f, 0.0f);
    create_platform(g, 10.0f, 512.0f, 0.0f, 256.0f);
    create_platform(g, 10.0f, 512.0f, 512.0f, 256.0f);
    int count = 0;
    g->Run();
    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            handle(&window, &evnt);
        }
        window.clear();
        g->Draw(&window);
        window.display();
    }
}