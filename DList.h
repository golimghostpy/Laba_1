#ifndef TLIST_H_INCLUDED
#define TLIST_H_INCLUDED

#include "libs.h"
#include "OList.h"

struct TNode{
    string data;
    TNode* next;
    TNode* prev;

    TNode(string val) : data(val), next(nullptr), prev(nullptr){}
};

struct TList{
    int size;
    TNode* first;
    TNode* last;

    TList() : size(0), first(nullptr), last(nullptr){}

    bool is_empty();
    void push_front(string);
    void push_back(string);
    void delete_front();
    void delete_back();
    void delete_value(string);
    int find_value(string);
    void print(string);
};

void tlist_do(const string&, OList&);

#endif // TLIST_H_INCLUDED
