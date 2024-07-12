#include <SFML/Graphics.hpp>
#include "../include/global.hpp"
#include <chrono>

#define FRAME_RATE 60
#define FIXED_UPDATE_LENGTH (static_cast<uint64_t>(1000000.0f/FRAME_RATE))
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

void Global::Draw(sf::RenderWindow *w)
{
    for(auto sprite: InstantiatedObjects)
        {
            (*w).draw(*sprite->get_texture());
        }
}