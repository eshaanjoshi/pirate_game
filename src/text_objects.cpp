#include "../include/text_objects.hpp"
using namespace std;




TextObject::TextObject(sf::Font *font, string a, sf::Vector2f *pos, sf::Vector2f *offsetr)
{
    text = new sf::Text();
    (*text).setCharacterSize(10);
    (*text).setFont(*font);
    (*text).setFillColor(sf::Color(255, 255, 255, 255));
    posit = pos;
    (*text).setString(a);
    exists = true;
    enabled = DISABLED;
    id = rand() % 10;
    backdrop = new sf::RectangleShape();
    offset = offsetr;
    if(offsetr == NULL)
    {
        offset = new sf::Vector2f(0.0f, 0.0f);
    }
    set = false;
}

TextObject::TextObject()
{
    exists = false;
    enabled = DISABLED;
}

void TextObject::set_text_state(text_state t)
{
    if(t==DISABLED)
    {
        set = false;
    }
    if(t==ENABLED)
    {
        set = true;
    }
    enabled = t;
}

sf::Text *TextObject::get_text()
{
    (*text).setPosition(sf::Vector2f(posit->x + offset->x, posit->y + offset->y));
    return text;
}

void TextObject::change_string(string s){
    //printf("%s\n", set ? "true" : "false");
    if (set) return;
    (*text).setString(s);
}

sf::RectangleShape *TextObject::get_texture(){
    return backdrop;
}

void TextObject::set_texture(sf::Color color, sf::Color out_color, float x, float y, float xloc, float yloc){
    backdrop = new sf::RectangleShape(sf::Vector2f(x, y));
    backdrop->setFillColor(color);
    backdrop->setOutlineColor(out_color);
    backdrop->setOutlineThickness(5);
    backdrop->setPosition(sf::Vector2f(xloc, yloc));
    posit = new sf::Vector2f(posit->x + xloc, posit->y + yloc);
}