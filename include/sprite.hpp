
#ifndef SPRITE
#define SPRITE
#include <SFML/Graphics.hpp>
#include "gameobject.hpp"

class Global;
enum SPRITE_TYPE{
    NONE_T,
    GROUND_T,
    PLAYER_T,
    CLEAN_T,
    INFECTED_T, 
    DEAD_T,
    RECOVERED_T
};
static const char * EnumStrings[] = { "none", "ground", "player", "clean", "infected", "dead", "recovered"};

class Sprite:public GameObject{
public:
    Sprite(sf::Shape *s, float xoffset, float yoffset, float m, SPRITE_TYPE type);
    sf::Shape *get_texture();
    void set_gravity(bool g);
    void set_force(float x, float y);
    void set_velocity(float x, float y);
    virtual void FixedUpdate();
    bool resolve_collider(Sprite *other);
    sf::FloatRect *collider;
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
protected:
    sf::Shape *texture;
    bool gravity_enabled;
    void gravity();
    sf::Vector2f velocity;
    sf::Vector2f force;
    float xoffset;
    float yoffset;
    void create_default_collider();
    void update_collider_pos();
    
    sf::Vector3i offset;
    uint64_t frame_counter;

};

#endif