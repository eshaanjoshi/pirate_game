#include "../include/sprite.hpp"
#include "../include/gameobject.hpp"
#include "../include/global.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../include/vector_math.hpp"
#include "../include/timer.hpp"
#include "../include/window_settings.hpp"
#define FRAME_RATE_MOD 1000.0f
#define CUTOFF 0.05f


void default_interact(Sprite *a, Sprite *b)
{
}

void default_additional_interact(Sprite *a)
{
    
}


Sprite::Sprite(sf::Shape *s, float width, float height, float m, SPRITE_TYPE type, string str):GameObject()
{
    printf("offsets %f %f %f %f\n", xoffset, yoffset, width, height);
    texture = s;
    velocity = sf::Vector2f(0.0f, 0.0f);
    force = sf::Vector2f(0.0f, 0.0f);
    gravity_enabled = false;
    pos = texture->getPosition();
    xoffset = width;
    yoffset = height;
    create_default_collider();
    offset = sf::Vector3i(0,0,255);
    color = sf::Color(offset.x, offset.y, offset.z);
    mass = m;
    sprite_type = type;
    this->interact = default_interact;
    frame_counter = 0;
    this->api_update = default_additional_interact;
    enabled = true;
    staged_move = sf::Vector2f(0.0f, 0.0f);
    sprite_unique_id = rand();
    is_interacting = false;
    interactive_string = str;
}




sf::Shape *Sprite::get_texture()
{
    return texture;
}

void Sprite::set_gravity(bool g)
{
    gravity_enabled = g;
}

void Sprite::set_velocity(float x, float y)
{
    velocity = sf::Vector2f(1000*x/FIXED_UPDATE_LENGTH, 1000*y/FIXED_UPDATE_LENGTH);
}

void Sprite::set_force(float x, float y)
{
    force = sf::Vector2f(x, y);
}

void Sprite::gravity()
{
    float vx = velocity.x;
    float vy = velocity.y;
    if(gravity_enabled)
    {
        
        float fx = force.x;
        float fy = force.y;
        float dropmult = vy > 0.0f ? 2.0f : 1.0f;
        vx =  vx + fx/FRAME_RATE_MOD;
        vy = vy + fy/FRAME_RATE_MOD;
        velocity = sf::Vector2f(vx, vy);
    }
    (*texture).move(staged_move.x + vx,staged_move.y +  vy);
    staged_move = sf::Vector2f(0.0f, 0.0f);
}

void Sprite::update_collider_pos(){
    collider->left = pos.x-(xoffset/2.0f);
    //printf("%f %f\n", pos.y + texture->getSize()/2.0f, );
    collider->top = pos.y-((yoffset/2.0f));
    collider->width = xoffset;
    collider->height = yoffset;
    interactive_collider->left = -5.0f + pos.x-(xoffset/2.0f);
    //printf("%f %f\n", pos.y + texture->getSize()/2.0f, );
    interactive_collider->top = -5.0f + pos.y-((yoffset/2.0f));
    interactive_collider->width = 10.0f + xoffset;
    interactive_collider->height = 10.0f + yoffset;
    //sf::IntRect t = texture->getTextureRect();
    //printf("interactivespace%f %f %f %f\n", interactive_collider->top, interactive_collider->left, interactive_collider->height, interactive_collider->width);

}

int bounce_between(int num, int offset)
{
    int d = (offset + timer()/50000) % (num * 2);
    if (d - num > 0)
    {
        return (num * 2) -d;
    }
    return d;
}

void Sprite::FixedUpdate()
{
    
    gravity();
    this->api_update(this);
    pos = texture->getPosition();
    update_collider_pos();
    texture->setFillColor(color);
    frame_counter++;
}

void Sprite::create_default_collider()
{
    collider = new sf::FloatRect(pos.x -xoffset/2.0f, pos.y-yoffset/2.0f, xoffset, yoffset);
    interactive_collider = new sf::FloatRect(-5 +pos.x -xoffset/2.0f, -5+pos.y-yoffset/2.0f, xoffset+10, yoffset+10);
}

void Sprite::set_custom_collider(float left, float top, float width, float height)
{
    collider = new sf::FloatRect(left, top, width, height);
    interactive_collider = new sf::FloatRect(left - 5, top - 5, width + 10, height + 10);
}

sf::Vector2f *compute_mults(sf::Vector2f pos1, sf::Vector2f pos2)
{
    sf::Vector2f *mults = new sf::Vector2f(pos1.x > pos2.x ? 1 : -1, pos1.y > pos2.y ? 1 : -1);
    return mults;
}


bool Sprite::resolve_collider(Sprite *other)
{
    
    sf::FloatRect coll_box;
    collider->top = collider->top + staged_move.y;
    collider->left = collider->left + staged_move.x;
    // sf::FloatRect *collider2 = (other->collider);
    // collider2->top = collider2->top + other->staged_move.y;
    // collider2->left = collider2->left + other->staged_move.x;
    bool b = collider->intersects(*other->interactive_collider, coll_box);
    if(sprite_type== INTERACTABLE_T && other->sprite_type==PLAYER_T)
    {
        //printf("HERE!\n");
       
        if(b)
        {
            interact(other, this);
            TextObject **t = get_text("Interact");
            if(t!=NULL)
            {
                //printf("enabling text!!\n");
                //(*t)->enabled=ENABLED;
                (*t)->set_text_state(ENABLED);
                is_interacting = true;

                other->is_interacting = true;
            }
        }
        else{
            TextObject **t = get_text("Interact");
            if(t!=NULL)
            {
                //printf("disabling text!!\n");
                //(*t)->enabled=DISABLED;
                (*t)->set_text_state(DISABLED);
                //is_interacting = false;
                //other->is_interacting = false;
            }
        }
    }
    if (sprite_type != GROUND_T && b) 
    {
        //interact(this, other);
        sf::Vector2f coll_move(coll_box.width, coll_box.height);
        sf::Vector2f *mults = compute_mults(pos, other->pos);
        float total_mass = mass + other->mass;
        float percent_ours = mass < 0.0f ? 0 : mass/total_mass;
        float percent_theirs = other->mass < 0.0f ? 0 : 1 - percent_ours;
        if(coll_box.width < coll_box.height)
        {
            staged_move = sf::Vector2f(mults->x* coll_move.x*percent_ours, staged_move.y);
            other->staged_move = sf::Vector2f(-1*mults->x*coll_move.x*percent_theirs, other->staged_move.y);
            float newvel = elasticity * velocity.x;
            if(pos.x < other->pos.x && velocity.x > 0.0f)
            {
                newvel = newvel * -1;
            }
            if(pos.x > other->pos.x && velocity.x < 0.0f)
            {
                newvel = newvel * -1;
                collide_x = -1;
            }
            if(pos.x < other->pos.x)
            {
                collide_x = 1;
            }
            if(pos.x > other->pos.x)
            {
                collide_x = -1;
            }
            velocity.x = 0;
            if (!contact && abs(newvel) >= CUTOFF) velocity.x = newvel;
        }
        else
        {
            staged_move = sf::Vector2f(staged_move.x, mults->y*coll_move.y*percent_ours);
            other->staged_move = sf::Vector2f(other->staged_move.y, -1 * mults->y* coll_move.y * percent_theirs);
            float newvel = elasticity * velocity.y;
            if(pos.y < other->pos.y && velocity.y > 0.0f)
            {
                newvel = newvel * -1;
                collide_y = 1;
            }
            if(pos.y > other->pos.y && velocity.y < 0.0f)
            {
                newvel = newvel * -1;
                collide_y = -1;
            }
            if(pos.y < other->pos.y)
            {
                collide_y = 1;
            }
            if(pos.y > other->pos.y)
            {
                collide_y = -1;
            }
            velocity.y = 0;
            
            if (!contact && abs(newvel) >= CUTOFF) velocity.y = newvel;
        }
        contact = true;
        if (sprite_type == PLAYER_T && pos.y < coll_box.top)
        {
            touch_ground = true;
        }
    }
    contact = false;
    return b;
}

TextObject **Sprite::get_text(string s)
{
    TextObject **t;
    try{
        t = associated_text.at(s);
    }
    catch(std::out_of_range)
    {
        return NULL;
    }
    return t;
}

void Sprite::add_text(string s, TextObject **t){
    (*t)->enabled = DISABLED;
    associated_text[s] = t;
}

uint64_t Sprite::get_frame_count(){
    return frame_counter;
}
uint64_t Sprite::reset_frame_count()
{
    frame_counter = 0;
    return 0;
}