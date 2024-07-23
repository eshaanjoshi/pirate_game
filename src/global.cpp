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
#include "../include/window_settings.hpp"


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
}

void Global::InstantiateText(TextObject *g)
{
    g->enabled = DISABLED;
    TextObjects.push_back(g);
    printf("instantiaged%d \n", (int)(g->enabled == DISABLED));
}

void Global::FixedUpdate()
{
    //while(checker!=0);
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
        Collider();
        while(checker!=0);
        FixedUpdate();
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
    for(auto sprite: bucket)
    {
        sprite->is_interacting = false;
        if((sprite)->sprite_type != GROUND_T){
            for (auto other: bucket)
            {
                if ((other)!=sprite)
                {
                    bool b = (sprite)->resolve_collider(other);
                }
            }
        }
    }
    m.lock();
    unsigned long mask = ~(0x1L << idx);
    checker &= mask;
    m.unlock();

}

void Global::init_buckets()
{
    checker = ~0;
    for(auto sprite : InstantiatedObjects)
    {
        if(sprite->enabled == false) continue;
        int bucket_width = WIDTH/8 + BUCKET_OFFSET;
        int bucket_height = HEIGHT/8 + BUCKET_OFFSET;
        int64_t t_i = static_cast<int64_t>(sprite->collider->top)/bucket_height;
        int64_t l_i = static_cast<int64_t>(sprite->collider->left)/bucket_width;
        int64_t w_i = static_cast<int64_t>(sprite->collider->width)/bucket_width;
        int64_t h_i = static_cast<int64_t>(sprite->collider->height)/bucket_height;
        for(int i = t_i-1; i < t_i+1 + h_i; i++)
        {
            for(int j = l_i-1; j < l_i+1 + w_i; j++)
            {
                int ni = i;
                int nj = j;
                if (i>7) { ni = 7;}
                if (i<0) { ni = 0;}
                if (j>7) { nj = 7;}
                if (j<0) { nj = 0;}
                //printf("%d %d\n", i, j);
                BucketedObjects[ni][nj].push_back(sprite);
                //BucketedObjects[0][0].push_back(sprite);
                //printf("20\n");
            }
            //printf("19\n");
        }
        //printf("18\n");
    }
}

void Global::Collider()
{
    init_buckets();
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
    //while(checker!=0);
}

void Global::print_id_list()
{
    for (auto sprite: InstantiatedObjects)
    {
        printf("Object ID: %d\n", sprite->sprite_unique_id);
    }
}

void Global::Draw(sf::RenderWindow *w, sf::Font *font)
{
    while(1)
    {
        (*w).clear(sf::Color(0, 0, 0, 255));
        int count = 0;
        for(auto sprite: InstantiatedObjects)
        {
            if(sprite->enabled)(*w).draw(*sprite->get_texture());
            //printf("Sprite!");
        } 
        for(auto text:TextObjects)
        {
            if(text->enabled==ENABLED)
            {
                //printf("text enabled objid %p\n", (void*)text);
                (*w).draw(*text->get_texture());
                (*w).draw(*text->get_text());
            }
        }
        (*w).display();
        break;
    }
}