#include <SFML/Graphics.hpp>
#include "../include/global.hpp"
#include <chrono>



#include <list>
using namespace std;
#include <csignal>
#include "../include/sprite.hpp"
#include <thread>
#include "../include/timer.hpp"


Global::Global(int i)
{
    InstantiatedObjects = {};
}


void Global::Instantiate(Sprite *g)
{
    add_to_list(g);
    //std::thread t(&GameObject::run_in_thread, this);
    //t.detach();
}

void Global::FixedUpdate()
{
    for(auto gameobject: InstantiatedObjects)
    {
        (*gameobject).FixedUpdate();
    }
}

void Global::run_in_thread()
        {
            int count = 0;
            uint64_t init_time = timer();
            while(1)
            {
                uint64_t start_time = timer();
                uint64_t next_iter = start_time + FIXED_UPDATE_LENGTH;
                FixedUpdate();
                Collider();
                uint64_t time_remaining = next_iter - timer(); 
                if(count == 0){
                    float delta = stopwatch(&init_time);
                    printf("60 %f\n", delta);
                }
                count = (count + 1) % 60;
                usleep(time_remaining);
            }
        }

int Global::add_to_list(Sprite *g)
{
    InstantiatedObjects.push_back(g);

    return InstantiatedObjects.size();
}

void Global::Run()
{
    printf("Running Global!\n");
    std::thread t(&Global::run_in_thread, this);
    t.detach();
}

void Global::Collider()
{
    for(auto sprite: InstantiatedObjects)
        {
            //printf("x%f y%f\n", sprite->get_texture()->getPosition().x,sprite->get_texture()->getPosition().y );
            if(sprite->sprite_type != GROUND_T){
                for (auto other: InstantiatedObjects)
                {
                    if (other!=sprite)
                    {
                        //printf("%f %f %f %f\n", sprite->collider->left, sprite->collider->top, sprite->collider->width, sprite->collider->height);
                        //printf("%f %f %f %f\n", other->collider->left, other->collider->top, other->collider->width, other->collider->height);
                        bool b = sprite->resolve_collider(other);
                        //if (b) printf("collision!\n");
                    }
                }
            }
        }
}

void Global::Draw(sf::RenderWindow *w)
{
    for(auto sprite: InstantiatedObjects)
        {
            (*w).draw(*sprite->get_texture());
        }
}