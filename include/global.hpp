#ifndef GLOBAL
#define GLOBAL

#include <list>
#include <SFML/Graphics.hpp>
#include <thread>
#include "text_objects.hpp"
using namespace std;
class Sprite;

class Global{
public:
    Global(int i);  
    void Run();
    void Draw(sf::RenderWindow *w, sf::Font *font);
    void Instantiate(Sprite *g);
    void InstantiateText(TextObject *g);
    void print_id_list();
protected:
    unsigned long checker;
    void Collider();
    void init_buckets();
    void FixedUpdate();  
    int add_to_list(Sprite *g);   
    list<Sprite*> InstantiatedObjects;
    list<TextObject*> TextObjects;
    list<Sprite*> BucketedObjects[8][8];
    void do_collision(list<Sprite*> bucket, int idx);
    std::thread T[8][8];
    int run_in_thread();
};
#endif