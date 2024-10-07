#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "libs.h"
#include "OList.h"
#include "Array.h"

struct HashBlock{
    string key;
    string value;
    HashBlock* next;

    HashBlock(string val1, string val2) : key(val1), value(val2), next(nullptr){}
};

struct HashList{
    HashBlock* first;

    HashList() : first(nullptr){}

    bool is_empty();
    void push_back(string, string);
    void delete_value(string);
    void print(string);
};

struct HashBucket{
    int key;
    HashList data;

    HashBucket() : key(0) {}
    HashBucket(int val) : key(val){}
};

struct HashTable{
    HashBucket* data;
    int size;
    int capacity;

    HashTable(int initialCapacity = 30) : size(0), capacity(initialCapacity){
        data = new HashBucket[capacity];
    }

    void push_back(HashBucket&);
    void insert_at(int, HashBucket&);
    void remove_at(int);
    void set_at(int, HashBucket&);

    void add(int);
    int hash(const string&);
    void set(string, string);
    string get_values(string);
    void delete_value(const string&);
    void print();
};

void hash_do(const string&, OList&);

#endif // HASHTABLE_H_INCLUDED
