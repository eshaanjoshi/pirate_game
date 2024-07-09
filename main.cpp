#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/player.hpp"
#include "src/event_handler.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Default);
    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    player.setFillColor(sf::Color::Red);
    player.setOrigin(50.0f, 50.0f);
    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            event_handler(&window, &evnt);
        }

        player_move_mouse(&window, &player);
        window.clear(); 
        window.draw(player);
        window.display();
    }


}