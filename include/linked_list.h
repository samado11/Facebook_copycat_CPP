#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Node.h>
#include <Treap.h>
#include <User.h>
using namespace std;

class linked_list
{
    public:
    Node *head,*tail;
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(User n)
    {
        Node *tmp = new Node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
};

#endif // LINKED_LIST_H
