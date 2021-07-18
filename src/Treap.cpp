#include "Treap.h"


Treap::Treap(string d)
    {
        this->data = d;
        this->priority = rand() % 100;
        this->l= this->r = nullptr;
    }


Treap::~Treap()
{
    //dtor
}
