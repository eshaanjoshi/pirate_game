
#include "GameObject.hpp"


void GameObject::run_fixed_update_step()
        {
            while(1)
            {
                FixedUpdate();
            }
        }
void GameObject::FixedUpdate()
{

}

void GameObject::Instantiate()
{
    std::thread t(&GameObject::run_fixed_update_step, this);
    t.detach();
}


