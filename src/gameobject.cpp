#include "../include/gameobject.hpp"
#include <thread>
#include <chrono>
#define FIXED_UPDATE_LENTH 14000
#include <time.h>
#include <csignal>
#include "../include/timer.hpp"



GameObject::GameObject(){

}

void GameObject::run_in_thread()
        {
            while(1)
            {
                uint64_t start_time = timer();
                uint64_t next_iter = start_time + FIXED_UPDATE_LENTH;
                
                FixedUpdate();
                uint64_t time_remaining = next_iter - timer(); 
                
                usleep(time_remaining);
            }
        }
void GameObject::FixedUpdate()
{

}

