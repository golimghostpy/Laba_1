#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "libs.h"
#include "OList.h"

enum class HashCommands{
    HSET, HGET, HDEL, HPRINT
};

struct HashBucket{
    int key;
    OList data;
    HashBucket* nextBucket;

    HashBucket(int val) : key(val), nextBucket(nullptr){}
};

struct HashTable{
    HashBucket* first;
    HashBucket* last;

    HashTable() : first(nullptr), last(nullptr){}

    void add(int);
    int hash(const string&);
    void set(string value);
    OList get_values(int);
    void delete_value(const string&);
    void print();
};

void hash_do(const string&, OList&);

#endif // HASHTABLE_H_INCLUDED
