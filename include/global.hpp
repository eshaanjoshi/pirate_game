#ifndef GLOBAL
#define GLOBAL
#define FRAME_RATE 60
#include <list>
#include <SFML/Graphics.hpp>
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
protected:
    list<Sprite*> InstantiatedObjects;
    void run_in_thread();
    
};
#endif