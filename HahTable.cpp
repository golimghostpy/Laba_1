#include "HashTable.h"

void HashTable::add(int key){
    HashBucket* newBucket = new HashBucket(key);

    if (first == nullptr){
        first = newBucket;
        last = newBucket;
        return;
    }

    last->nextBucket = newBucket;
    last = newBucket;
}

int HashTable::hash(const string& value){
    int summ = 0;
    for (auto i: value){
        summ += static_cast<int>(i);
    }

    return summ % 30;
}

void HashTable::set(string value){
    int valKey = hash(value);

    HashBucket* currBucket = first;
    for (int i = 0; i != valKey; ++i){
        currBucket = currBucket->nextBucket;
    }

    (currBucket->data).push_back(value);
}

OList HashTable::get_values(int key){
    if (key < 0 || key >= 30){
        cout << "No such a key" << endl;
        OList empty;
        return empty;
    }

    HashBucket* currBucket = first;
    for (int i = 0; i != key; ++i){
        currBucket = currBucket->nextBucket;
    }

    return currBucket->data;
}

void HashTable::delete_value(const string& value){
    int valKey = hash(value);

    HashBucket* currBucket = first;
    for (int i = 0; i != valKey; ++i){
        currBucket = currBucket->nextBucket;
    }

    (currBucket->data).delete_value(value);
}

void HashTable::print(){
    HashBucket* currBucket = first;
    for (int i = 0; i < 30; ++i){
        cout << i << ": ";
        (currBucket->data).print(", ");
        currBucket = currBucket->nextBucket;
    }
    cout << endl;
}

void hash_do(const string& path, OList& query){
    ifstream readFile(path);
    HashTable toWork;
    string line;
    while (readFile >> line){
        OList splited = split(line, ",");
        for (auto i = splited.first; i != nullptr; i = i->next){
            toWork.set(i->data);
        }
    }

    string token = query.find_at(0)->data;
    string item = "";
    if (query.size == 2){
        item = query.find_at(1)->data;
    }

    if (token == "HSET"){
        toWork.set(item);
    } else if (token == "HGET"){
        if (item == ""){
            cerr << "Can't get items with no index" << endl;
            return;
        }

        cout << "Got items: ";
        toWork.get_values(stoi(item)).print(" ");
    } else if (token == "HDEL"){
        if (item == ""){
            cerr << "Can't delete empty value" << endl;
            return;
        }

        toWork.delete_value(item);
    } else if (token == "HPRINT"){
        toWork.print();
    } else{
        cerr << "No such a command" << endl;
    }

    ofstream writeFile(path);
    for (auto i = toWork.first; i != nullptr; i = i->nextBucket){
        writeFile << (i->data).join(',') << endl;
    }
    writeFile.close();
}
