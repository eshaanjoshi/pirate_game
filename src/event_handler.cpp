#include <SFML/Graphics.hpp>
#include <iostream>
int event_handler(sf::RenderWindow *window, sf::Event *e){
    sf::Event evnt = *e;
    switch(evnt.type){
                    case sf::Event::Closed:
                        (*window).close();
                        break;
                    case sf::Event::Resized:
                        printf("W: %d H: %d \n", evnt.size.width, evnt.size.height);
                        break;
                    case sf::Event::TextEntered:
                        if(evnt.text.unicode < 128){
                            printf("%c", evnt.text.unicode);
                        }
                        break;
                
                }
    return 0;
}