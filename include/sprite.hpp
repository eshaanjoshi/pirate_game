
#ifndef SPRITE
#define SPRITE
#include <SFML/Graphics.hpp>
#include "gameobject.hpp"
#include "text_objects.hpp"
#include "window_settings.hpp"
class Global;
enum SPRITE_TYPE{
    NONE_T = 0b11111111,
    GROUND_T = 0b1,
    PLAYER_T = 0b10,
    INTERACTABLE_T = 0b100
};
static const char * EnumStrings[] = { "none", "ground", "player", "interactable"};

class Sprite:public GameObject{
public:
    Sprite(sf::Shape *s, float xoffset, float yoffset, float m, SPRITE_TYPE type, float xpos = (WIDTH/2), float ypos = (HEIGHT/2), string str = "");
    sf::Shape *get_texture();
    void set_gravity(bool g);
    void set_force(float x, float y);
    void set_velocity(float x, float y);
    virtual void FixedUpdate();
    
    bool resolve_collider(Sprite *other);
    sf::FloatRect *collider;
    sf::FloatRect *interactive_collider;
    void set_custom_collider(float left, float top, float width, float height);
    float mass;
    float elasticity;
    SPRITE_TYPE sprite_type;
    bool contact;
    bool touch_ground;
    sf::Vector2f pos;
    sf::Color color;
    void (*interact)(Sprite *a, Sprite *b);
    void (*api_update)(Sprite *a);
    uint64_t get_frame_count();
    uint64_t reset_frame_count();
    bool enabled;
    sf::Vector2f staged_move;
    TextObject **get_text(string s);
    void add_text(string s, TextObject **t);
    uint32_t sprite_unique_id;
    bool is_interacting;
    string interactive_string;
protected:
    virtual void BasicInteract(Sprite *other);
    sf::Shape *texture;
    bool gravity_enabled;
    void gravity();
    sf::Vector2f velocity;
    sf::Vector2f force;
    float xoffset;
    float yoffset;
    void create_default_collider();
    void update_collider_pos();
    int collide_x;
    int collide_y;
    sf::Vector3i offset;
    uint64_t frame_counter;
    map<string, TextObject**> associated_text;

};

#endif