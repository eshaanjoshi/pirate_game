#ifndef GLOBAL
#define GLOBAL

#include <list>
#include <SFML/Graphics.hpp>
#include <thread>
using namespace std;
class Sprite;

class Global{
public:
    Global(int i);
    void FixedUpdate();
    int add_to_list(Sprite *g);
    void Run();
    void Draw(sf::RenderWindow *w);
    void Instantiate(Sprite *g);
    void Collider();
    unsigned long checker;
protected:
    list<Sprite*> InstantiatedObjects;
    list<Sprite*> BucketedObjects[8][8];
    void do_collision(list<Sprite*> bucket, int idx);
    std::thread T[8][8];
    int run_in_thread();
    
};
#endif