#include <iostream>
#include <thread>
#ifndef GAME_OBJECT
#define GAME_OBJECT
class GameObject{
public:
    virtual void FixedUpdate();
    void Instantiate();
//private:
    void run_fixed_update_step();

protected:
    float fx;
    float fy;
    float vx;
    float vy;
};

#endif