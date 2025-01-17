#include "../include/sprite.hpp"
#include "../include/gameobject.hpp"
#include "../include/global.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../include/vector_math.hpp"
#include "../include/timer.hpp"
#define FRAME_RATE_MOD 1000.0f
#define CUTOFF 0.05f




Sprite::Sprite(sf::Shape *s, float xoff, float yoff, float m, SPRITE_TYPE type):GameObject()
{
    printf("offsets %f %f %f %f\n",xoffset, yoffset, xoff, yoff);
    texture = s;
    velocity = sf::Vector2f(0.0f, 0.0f);
    force = sf::Vector2f(0.0f, 0.0f);
    gravity_enabled = false;
    pos = texture->getPosition();
    xoffset = xoff;
    yoffset = yoff;
    create_default_collider();
    printf("offsets %f %f %f %f\n",xoffset, yoffset, xoff, yoff);
    offset = sf::Vector3i(rand() % 256, rand() % 256, rand() % 256);
    mass = m;
    sprite_type = type;
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
        //printf("%f %f %f %f\n", vx, vy, fx, fy);
        float dropmult = vy > 0.0f ? 2.0f : 1.0f;
        //printf("%f\n", dropmult);
        vx = vx + fx/FRAME_RATE_MOD;
        vy = vy + fy/FRAME_RATE_MOD;
        velocity = sf::Vector2f(vx, vy);
        
        
    }
    (*texture).move(vx, vy);
}

void Sprite::update_collider_pos(){
    collider->left = pos.x-xoffset;
    collider->top = pos.y-yoffset;
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
    //printf("collider left top %f %f\n", collider->left, collider->top);
    //printf("texture left top %f %f\n", texture->getPosition().x, texture->getPosition().y);
    gravity();
    pos = texture->getPosition();
    update_collider_pos();
    //printf("%d\n", (int)((85 + timer()/50000)%256));
    //texture->setFillColor(sf::Color(bounce_between(255, offset.x),  bounce_between(255, offset.y), bounce_between(255, offset.z)));
    texture->setFillColor(sf::Color(offset.x, offset.y, offset.z));

}

void Sprite::create_default_collider()
{
    collider = new sf::FloatRect(pos.x -xoffset, pos.y-yoffset, xoffset*2, yoffset*2);
    //printf("%f %f %f %f\n",xoffset, yoffset, collider->width, collider->height);
    //exit(1);
}

void Sprite::set_custom_collider(float left, float top, float width, float height)
{
    collider = new sf::FloatRect(left, top,width,height);
}

sf::Vector2f *compute_mults(sf::Vector2f pos1, sf::Vector2f pos2)
{
    sf::Vector2f *mults = new sf::Vector2f(pos1.x > pos2.x ? 1 : -1, pos1.y > pos2.y ? 1 : -1);
    return mults;
}

bool Sprite::resolve_collider(Sprite *other)
{
    sf::FloatRect coll_box;
    //if (sprite_type == PLAYER_T) printf("prev %f\n", velocity.y);
    bool b = collider->intersects(*(other->collider), coll_box);
    if (b) 
    {
        sf::Vector2f coll_move(coll_box.width, coll_box.height);
        //char *s = to_string(unit_vector);
        //printf("%s", s);
        //free(s);

        sf::Vector2f *mults = compute_mults(pos, other->pos);

        float total_mass = mass + other->mass;
        float percent_ours = mass < 0.0f ? 0 : mass/total_mass;
        float percent_theirs = other->mass < 0.0f ? 0 : 1 - percent_ours;
        if(coll_box.width < coll_box.height)
        {
            texture->move(mults->x* coll_move.x*percent_ours, 0);
            other->get_texture()->move(-1*mults->x*coll_move.x*percent_theirs,0);
            //printf("elast%f\n", elasticity);
            float newvel = -1 * elasticity * velocity.x;
            velocity.x = 0;
            if (!contact && abs(newvel) >= CUTOFF) velocity.x = newvel;
        }
        else
        {
            texture->move(0, mults->y*coll_move.y*percent_ours);
            other->get_texture()->move(0, -1 * mults->y* coll_move.y * percent_theirs);
            //printf("hit\n");
            float newvel = -1 * elasticity * velocity.y;
            //printf("newvelhit %f\n", newvel);
            velocity.y = 0;
            if (!contact && abs(newvel) >= CUTOFF) velocity.y = newvel;
            //printf("newvelhit %f\n", velocity.y);
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