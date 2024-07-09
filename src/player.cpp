#include <SFML/Graphics.hpp>



int player_controller(sf::RectangleShape *p)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            (*p).move(-0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            (*p).move(0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            (*p).move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            (*p).move(0.0f, 0.1f);
        }
    return 0;
}


int player_move_mouse(sf::RenderWindow *w, sf::RectangleShape *p)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*w);
        (*p).setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }
    return 0;
}