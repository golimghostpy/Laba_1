#ifndef OLIST_H_INCLUDED
#define OLIST_H_INCLUDED

#include "libs.h"

struct ONode{
    string data;
    ONode* next;

    ONode(string val) : data(val), next(nullptr){}
};

struct OList{
    int size;
    ONode* first;
    ONode* last;

    OList() : size(0), first(nullptr), last(nullptr){}

    bool is_empty();
    void push_front(string);
    void push_back(string);
    void delete_front();
    void delete_back();
    void delete_value(string);
    int find_value(string);
    void print(string);
    ONode* find_at(int);
    string join(const char);
};

void olist_do(const string&, OList&);
OList split(const string&, const string&);

#endif // OLIST_H_INCLUDED
