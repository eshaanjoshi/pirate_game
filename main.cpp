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
#include "include/text_objects.hpp"
using namespace std;
Global* CreateGlobal()
{
    Global *g = new Global(1);
    return g;
}

int infected;
int killed;

void interact(Sprite *a, Sprite *b){
    //cout << "string values" << (a->interactive_string) << b->interactive_string << endl;
    if(a->sprite_type == PLAYER_T && b->sprite_type == INTERACTABLE_T)
    {
        Player *p = (Player*)a;
        p->generate_text(b->interactive_string);
        //printf("interact!\n");
    }
    if(b->sprite_type == PLAYER_T && a->sprite_type == INTERACTABLE_T)
    {
        Player *p = (Player*)b;
        p->generate_text(a->interactive_string);
        //printf("interact!\n");
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
    Player *p = new Player(player, x, y, -1);
    p->set_gravity(false);
    p->set_force(0.0f, 10.0f);
    g->Instantiate(p);
    p->elasticity = 0.5f;
    p->set_custom_collider(50.0f - (x/2), 50.0f - (y/2), x, y);
    p->interact = &interact;
    p->sprite_type=PLAYER_T;
    return p;
}

Sprite *create_block(Global *g, float x, float y, float xpos, float ypos, float vx, float vy, float e)
{
    sf::RectangleShape *player = new sf::RectangleShape(sf::Vector2f(x, y));
    player->setFillColor(sf::Color::Blue);
    player->setOrigin(x/2, y/2);
    player->setPosition(xpos, ypos);
    Sprite *p = new Sprite(player, x, y, 20.0f, NONE_T);
    p->set_gravity(false);
    p->set_velocity(vx, vy);
    p->set_force(0.0f, 10.0f);
    g->Instantiate(p);
    p->elasticity = sqrt(e);
    p->interact = &interact;
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
    create_block(g, 50.0f, 50.0f, locx, locy, velx, vely, 0.99f);
}

Sprite *multi_block_create_3(Global *g)
{
    int locx = 10 + rand() % 450;
    int locy = 10 + rand() % 450;
    sf::RectangleShape *player = new sf::RectangleShape(sf::Vector2f(50.0f, 50.f));
    player->setFillColor(sf::Color::Blue);
    player->setOrigin(25.0f, 25.0f);
    player->setPosition(locx, locy);
    Sprite *p = new Sprite(player, 50.0f, 50.0f, -1.0f, NONE_T);
    g->Instantiate(p);
    p->interact = &interact;
    p->api_update = &update;
    p->sprite_type = INTERACTABLE_T;
    return p;
}

int main()
{
    XInitThreads();
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Tutorial", sf::Style::Close|sf::Style::Titlebar);
    

    Global *g = CreateGlobal();
    Player *p = create_player(g, 50.0f, 50.0f);
    //Sprite *s = multi_block_create_3(g);
    Sprite *s2 = multi_block_create_3(g);
    Sprite *s3 = multi_block_create_3(g);
    uint64_t init_time = timer();
    create_platform(g, 512.0f, 10.0f, 256.0f, 512.0f);
    create_platform(g, 512.0f, 10.0f, 256.0f, 0.0f);
    create_platform(g, 10.0f, 512.0f, 0.0f, 256.0f);
    create_platform(g, 10.0f, 512.0f, 512.0f, 256.0f);
    int count = 0;
    
    sf::Font *font = new sf::Font();
    if (!(*font).loadFromFile("ARIBLK.TTF"))
    {
        printf("font ded :(");
    }
    //TextObject *t = new TextObject(font, std::string("Interact"), &s->pos, new sf::Vector2f(-25.0f, 0.0f));
    TextObject *t2 = new TextObject(font, std::string("Interact"), &s2->pos, new sf::Vector2f(-25.0f, 0.0f));
    TextObject *t3 = new TextObject(font, std::string("Interact"), &s3->pos, new sf::Vector2f(-25.0f, 0.0f));
    TextObject *inter = new TextObject(font, std::string("<default text>"), new sf::Vector2f(10.0f, 10.0f), NULL);
    inter->set_texture(sf::Color(192, 192, 192, 128), sf::Color(113, 112, 110, 255), 512, 256, 0.0f, 256.0f);
    inter->get_text()->setCharacterSize(15);
    //t->enabled = DISABLED;
    t2->enabled = DISABLED;
    t3->enabled = DISABLED;
    //g->InstantiateText(t);
    g->InstantiateText(t2);
    g->InstantiateText(t3);
    g->InstantiateText(inter);
    //s->add_text("Interact", &t);
    s2->add_text("Interact", &t2);
    s3->add_text("Interact", &t3);
    p->add_text("talker", &inter);
    //s->interactive_string = "Hello World";
    s2->interactive_string = "Goodbye World";
    s3->interactive_string = "WTF World";
    g->print_id_list();
    g->Run();
    
    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            handle(&window, &evnt);
        }
        
        
        g->Draw(&window, font);
        count++;
    }
}