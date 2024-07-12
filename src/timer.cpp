#include <chrono>
#include <time.h>
#include <iostream>
#include <stdio.h>

uint64_t timer()
{
    using namespace std::chrono;
    uint64_t ms = duration_cast<microseconds>(
    system_clock::now().time_since_epoch()
    ).count();  
    return ms;
}

float timer_seconds()
{
    using namespace std::chrono;
    uint64_t ms = duration_cast<milliseconds>(
    system_clock::now().time_since_epoch()
    ).count();  
    return (static_cast<float>(ms));
}

float stopwatch(uint64_t *prev_time)
{
    uint64_t temp = timer();
    
    uint64_t delta = temp-*prev_time;
    float d = (static_cast<float>(delta));
    *prev_time = temp;
    return d/(1000000.0f);
}