#ifndef TIMER
#define TIMER
#define FRAME_RATE 60
#define FIXED_UPDATE_LENGTH (static_cast<uint64_t>(1000000.0f/FRAME_RATE))
uint64_t timer();
float timer_seconds();
float stopwatch(uint64_t *prev_time);

#endif