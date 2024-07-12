

#ifndef GAME_OBJECT
#define GAME_OBJECT


class GameObject{
public:
    GameObject();
    virtual void FixedUpdate();
protected: 
    void run_in_thread();
};

#endif