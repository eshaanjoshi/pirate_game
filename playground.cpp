#include <time.h>
#include <stdio.h>
#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>
using namespace std;

#define FIXED_UPDATE_LENTH 14000

float sum_loop_time;
uint64_t num_iter;
uint64_t orig_time =0;
uint64_t timer()
{
    using namespace std::chrono;
    uint64_t ms = duration_cast<microseconds>(
    system_clock::now().time_since_epoch()
    ).count();  
    //printf("%lx\n", (uint64_t)ms);
    return ms;
}

void testing()
{
    printf("blablabla\n");
}

void Fixed_Update(void (*funcptr)())
{
    uint64_t start_time = timer();
    uint64_t next_iter = start_time + FIXED_UPDATE_LENTH;
    
    funcptr();
    
    
    uint64_t time_remaining = next_iter - timer(); 
    
    usleep(time_remaining);
}


void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";
    printf("%f %lu %f", sum_loop_time, num_iter, sum_loop_time/num_iter);
   // cleanup and close up stuff here  
   // terminate program  

   exit(signum);  
}


void run_fixed_update_step(void (*funcptr)(), int tid)
{
    while(1)
    {
        printf("tid: %d  ", tid);
        Fixed_Update(funcptr);
    }
}

int main()
{
    signal(SIGINT, signalHandler); 
    
    for(int i =0; i < 15; i++)
    {
        std::thread t(run_fixed_update_step, &testing, i);
        t.detach();
    }
    while(1){}
    return 0;
}