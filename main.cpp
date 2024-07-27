#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <csignal>
#include <X11/Xlib.h> 


#include "unity.hpp"

using namespace std;
Global* CreateGlobal()
{
    Global *g = new Global(1);
    return g;
}


void interact(Sprite *a, Sprite *b)
{
    //cout << "string values" << (a->interactive_string) << b->interactive_string << endl;

}

void update(Sprite *a)
{

}

Player *create_player(Global *g, float x, float y)
{
    sf::RectangleShape *player = new sf::RectangleShape(sf::Vector2f(x, y));
    player->setFillColor(sf::Color::Red);
    Player *p = new Player(player, x, y, -1, 50.0f,  50.0f);
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
    Sprite *p = new Sprite(player, x, y, -1.0f, NONE_T, xpos, ypos);
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
    Sprite *p = new Sprite(sprite, x, y, -1.0f, GROUND_T, xpos, ypos);
    p->set_gravity(false);
    p->set_force(0.0f, 0.0f);
    g->Instantiate(p);
    return p;
}

Sprite *multi_block_create_3(Global *g)
{
    int locx = 10 + rand() % 450;
    int locy = 10 + rand() % 450;
    sf::RectangleShape *player = new sf::RectangleShape(sf::Vector2f(50.0f, 50.f));
    player->setFillColor(sf::Color::Blue);
    Sprite *p = create_block(g, 50.0f, 50.0f, locx, locy, 0.0f, 0.0f, 1.0f);
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
    Sprite *s = multi_block_create_3(g);
    Sprite *s2 = multi_block_create_3(g);
    Sprite *s3 = multi_block_create_3(g);
    uint64_t init_time = timer();
    // create_platform(g, 512.0f, 10.0f, 256.0f, 512.0f);
    // create_platform(g, 512.0f, 10.0f, 256.0f, 0.0f);
    // create_platform(g, 10.0f, 512.0f, 0.0f, 256.0f);
    // create_platform(g, 10.0f, 512.0f, 512.0f, 256.0f);
    int count = 0;
    
    sf::Font *font = new sf::Font();
    if (!(*font).loadFromFile("ARIBLK.TTF"))
    {
        printf("font ded :(");
    }
    TextObject *t = new TextObject(font, std::string("Interact"), &s->pos, new sf::Vector2f(-25.0f, 0.0f));
    TextObject *t2 = new TextObject(font, std::string("Interact"), &s2->pos, new sf::Vector2f(-25.0f, 0.0f));
    TextObject *t3 = new TextObject(font, std::string("Interact"), &s3->pos, new sf::Vector2f(-25.0f, 0.0f));
    TextObject *inter = new TextObject(font, std::string("<default text>"), new sf::Vector2f(10.0f, 10.0f), NULL);
    inter->set_texture(sf::Color(192, 192, 192, 128), sf::Color(113, 112, 110, 255), WIDTH, HEIGHT/3, 0.0f, 2 * WIDTH/3);
    inter->get_text()->setCharacterSize(15);
    t->enabled = DISABLED;
    t2->enabled = DISABLED;
    t3->enabled = DISABLED;
    g->InstantiateText(t);
    g->InstantiateText(t2);
    g->InstantiateText(t3);
    g->InstantiateText(inter);
    s->add_text("Interact", &t);
    s2->add_text("Interact", &t2);
    s3->add_text("Interact", &t3);
    p->add_text("talker", &inter);
    s->interactive_string = "Hello World";
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
