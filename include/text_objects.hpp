#ifndef TEXT_OBJECT
#define TEXT_OBJECT
#include <SFML/Graphics.hpp>
using namespace std;

enum text_state{
    DISABLED,
    ENABLED,
    FLICKER
};

class TextObject{
public:
    TextObject(sf::Font *font, string a, sf::Vector2f *pos,  sf::Vector2f *offset);
    TextObject();
    sf::Text *get_text();
    sf::RectangleShape *get_texture();
    void set_texture(sf::Color color, sf::Color out_color, float x, float y , float xloc, float yloc);
    void change_string(string s);
    text_state enabled;
    bool exists;
    int id;
    bool animated;
    void set_text_state(text_state t);
private:
    sf::Text *text;
    sf::Vector2f *posit;
    sf::Vector2f *offset;
    sf::RectangleShape *backdrop;
    bool set;
};

#endif