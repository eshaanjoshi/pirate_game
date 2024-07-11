#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/event_handler.cpp"
#include "src/GameObject.cpp"
#include "src/Sprite.cpp"
#include "src/player.cpp"
#include <X11/Xlib.h> 
    
int main()
{
    XInitThreads();
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Close | sf::Style::Titlebar);
    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    player.setFillColor(sf::Color::Red);
    player.setOrigin(50.0f, 50.0f);
    Player p(&window, &player);
    sf::RectangleShape g(sf::Vector2f(300.0f, 50.0f));
    Sprite ground(&window, &g);
    ground.Instantiate();
    ground.has_gravity_enabled = false;
    p.has_gravity_enabled = true;
    p.Instantiate();
    p.set_force(0.0f, 1.0f);
    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            event_handler(&window, &evnt);
        }

        
        window.clear(); 
        window.draw(*(p.p));
        //g = *(ground.p);
        //window.draw(*ground.get_object());
        window.display();
    }


}