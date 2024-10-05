#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include "libs.h"
#include "OList.h"

struct Array {
    string* data;
    int size;
    int capacity;

    Array(int initialCapacity = 10) : size(0), capacity(initialCapacity){
        data = new string[capacity];
    }

    void push_back(string);
    void insert_at(int, string);
    string get_at(int);
    void remove_at(int);
    void set_at(int, string);
    void print();
};

void array_do(const string&, OList&);

#endif // ARRAY_H_INCLUDED
