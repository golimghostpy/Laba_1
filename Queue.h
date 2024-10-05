#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "libs.h"
#include "OList.h"

struct Queue{
    ONode* head;
    ONode* tail;

    Queue() : head(nullptr), tail(nullptr){}

    bool is_empty();
    void push(string);
    void pop();
    void print();
};

void queue_do(const string&, OList&);

#endif // QUEUE_H_INCLUDED
