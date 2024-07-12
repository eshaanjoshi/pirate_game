#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/sprite.hpp"
#include "include/event_handler.hpp"
#include "include/player.hpp"
#include <X11/Xlib.h> 
#include "include/global.hpp"
#include "include/timer.hpp"
    

Global* CreateGlobal()
{
    Global *g = new Global(1);
    g->Run();
    return g;
}



int main()
{
    XInitThreads();
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Close);
    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    player.setFillColor(sf::Color::Red);
    player.setOrigin(50.0f, 50.0f);
    Player s(&player);
    s.set_gravity(true);
    s.set_force(0.0f, 10.0f);


    sf::RectangleShape player2(sf::Vector2f(100.0f, 100.0f));
    player2.setFillColor(sf::Color::Blue);
    player2.setOrigin(50.0f, 50.0f);
    Player p2(&player2);
    p2.set_gravity(true);
    p2.set_force(0.0f, 20.0f);

    Global *g = CreateGlobal();
    g->Instantiate(&s);
    g->Instantiate(&p2);
    int count = 0;
    float init_time = timer_seconds();
    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            handle(&window, &evnt);
        }

        window.clear(); 
        
        count = (count + 1) % 60;
        g->Draw(&window);
        window.display();
        
    }
    


}