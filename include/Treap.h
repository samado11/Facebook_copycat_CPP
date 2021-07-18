#ifndef TREAP_H
#define TREAP_H
#include <string>

using namespace std;

class Treap
{
    public:
     string data;
    int priority;
    Treap* l, *r;
    virtual ~Treap();
    Treap(string d);




    protected:

    private:
};

#endif // TREAP_H
