#include <SFML/Graphics.hpp>
#include "../include/global.hpp"
#include <chrono>



#include <list>
using namespace std;
#include <csignal>
#include "../include/sprite.hpp"
#include <thread>
#include "../include/timer.hpp"
#include <mutex>


std::mutex m;

Global::Global(int i)
{
    InstantiatedObjects = {};
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            BucketedObjects[i][j] = {};
        }
    }
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

int Global::run_in_thread()
{
    int count = 0;
    uint64_t init_time = timer();
    while(1)
    {
        uint64_t start_time = timer();
        uint64_t next_iter = start_time + FIXED_UPDATE_LENGTH;
        FixedUpdate();
        while(checker !=0){
            usleep(100);
        }
        Collider();
        int64_t time_remaining = next_iter - timer(); 
        if(count == 0){
            float delta = stopwatch(&init_time);
            printf("%d %f\n", FRAME_RATE, delta);
        }
        count = (count + 1) % FRAME_RATE;
        if(time_remaining > 0){
            usleep(time_remaining);
        }
    }
    return 0;
    
}

int faulty(std::size_t element)
{
    static std::vector<int> shortOne{1,2,3,4,5};
    return shortOne.at(element); // This will throw.
}
int Global::add_to_list(Sprite *g)
{
    InstantiatedObjects.push_back(g);

    return InstantiatedObjects.size();
}
#include <future>
#include <iostream>
void Global::Run()
{
    printf("Running Global!\n");
    //std::thread t(&Global::run_in_thread, this);
    //t.detach();
    try {
        std::packaged_task<int(Global*)> parallel_run{&Global::run_in_thread};
        auto result = parallel_run.get_future();
        auto thread = std::thread{std::move(parallel_run), this};
        thread.detach();
        //result.get();

        std::cout << "countTo was completed\n";
        //return 0;
    }
    catch(const std::exception& error) {
        std::cout << "The thread died unexpectedly with error: " << error.what() << '\n';
        //return 1;
    }  
}
#include <bitset>
#include <iostream>
void Global::do_collision(list<Sprite*> bucket, int idx)
{
    //printf("Started Thread %d\n", idx);
    for(auto sprite: bucket)
        {
            //printf("here!%d\n %lu", (int)BucketedObjects[1].size(), timer());
            //printf("x%f y%f\n", sprite->get_texture()->getPosition().x,sprite->get_texture()->getPosition().y );
            if((sprite)->sprite_type != GROUND_T){
                for (auto other: bucket)
                {
                    if ((other)!=sprite)
                    {
                        //printf("%f %f %f %f\n", sprite->collider->left, sprite->collider->top, sprite->collider->width, sprite->collider->height);
                        //printf("%f %f %f %f\n", other->collider->left, other->collider->top, other->collider->width, other->collider->height);
                        bool b = (sprite)->resolve_collider(other);
                        //if (b) printf("collision!\n");
                    }
                }
            }
        }
    m.lock();
    unsigned long mask = ~(0x1L << idx);
    checker &= mask;
    m.unlock();

}

void Global::Collider()
{
    checker = ~0;
    for(auto sprite : InstantiatedObjects)
    {
        int d = static_cast<int>(sprite->pos.x)/80;
        if (d>7) { d = 7;}
        if (d<0) { d = 0;}
        int e = static_cast<int>(sprite->pos.y)/80;
        if (e>7) { e = 7;}
        if (e<0) { e = 0;}
        BucketedObjects[d][e].push_back(sprite);
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            T[i][j] = std::thread(&Global::do_collision, this, BucketedObjects[i][j], i*8+j);
            T[i][j].detach();
        }
    }
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            BucketedObjects[i][j].clear();
        }
    }
}

void Global::Draw(sf::RenderWindow *w)
{
    for(auto sprite: InstantiatedObjects)
        {
            (*w).draw(*sprite->get_texture());
            //printf("Drawn here %d\n", (int)InstantiatedObjects.size());
        }
}