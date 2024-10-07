#include "HashTable.h"

void HashTable::push_back(HashBucket& element) {
    if (size == capacity) {
        capacity *= 2;
        HashBucket* newData = new HashBucket[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[size++] = element;
}

void HashTable::insert_at(int index, HashBucket& element) {
    if (index < 0 || index > size) {
        throw out_of_range("Index out of range");
    }
    if (size == capacity) {
        capacity *= 2;
        HashBucket* newData = new HashBucket[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = element;
    ++size;
}

void HashTable::remove_at(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    --size;
}

void HashTable::set_at(int index, HashBucket& element) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    data[index] = element;
}

bool HashList::is_empty(){
    return first == nullptr;
}

void HashList::push_back(string key, string value){
    HashBlock* new_elem = new HashBlock(key, value);

    if(is_empty()){
        first = new_elem;
        return;
    }

    new_elem->next = first;
    first = new_elem;
}

void HashList::delete_value(string key) {
    if (is_empty()){
        cout << "No such a key" << endl;
        return;
    }

    HashBlock* curr = first;
    HashBlock* prev = nullptr;

    while (curr != nullptr && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        cout << "No such a key" << endl;
        return;
    }

    prev->next = curr->next;
    delete curr;
}

void HashList::print(string delimiter){
    if(is_empty()){
        cout << endl;
        return;
    }

    HashBlock* curr = first;

    while(curr->next != nullptr){
        cout << curr->key << ":" << curr->value << delimiter;
        curr = curr->next;
    }
    cout << curr->key << ":" << curr->value << endl;
}

int HashTable::hash(const string& key){
    int summ = 0;
    for (auto i: key){
        summ += static_cast<int>(i);
    }

    return summ % 30;
}

void HashTable::set(string key, string value){
    int valKey = hash(key);
    for (auto i = (data[valKey].data).first; i != nullptr; i = i->next){
        if (i->key == key){
            cerr << "There is same key" << endl;
            return;
        }
    }
    (data[valKey].data).push_back(key, value);
}

string HashTable::get_values(string key){
    int hashKey = hash(key);

    auto i = (data[hashKey].data).first;
    for (i; i != nullptr; i = i->next){
        if (i->key == key){
            return i->value;
        }
    }

    return "No such a key";
}

void HashTable::delete_value(const string& key){
    int hashKey = hash(key);

    for (auto i = (data[hashKey].data).first; i != nullptr; i = i->next){
        if (i->key == key) delete_value(key); return;
    }
    cout << "No such a key" << endl;
}

void HashTable::print(){
    for (int i = 0; i < 30; ++i){
        cout << i << ": ";
        (data[i].data).print(", ");
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
            string key = split(i->data, ":").find_at(0)->data;
            string value = split(i->data, ":").find_at(1)->data;
            toWork.set(key, value);
        }
    }

    string token = query.find_at(0)->data;
    string key = "";
    string value = "";
    if (query.size == 2){
        key = query.find_at(1)->data;
    }
    else if (query.size == 3){
        key = query.find_at(1)->data;
        value = query.find_at(2)->data;
    }

    if (token == "HSET"){
        if (key == ""){
            cerr << "Can't set empty key" << endl;
            return;
        }
        toWork.set(key, value);
    } else if (token == "HGET"){
        if (key == ""){
            cerr << "Can't get empty key" << endl;
            return;
        }

        cout << "Got item: " << toWork.get_values(key) << endl;
    } else if (token == "HDEL"){
        if (key == ""){
            cerr << "Can't delete empty key" << endl;
            return;
        }

        toWork.delete_value(key);
    } else if (token == "HPRINT"){
        toWork.print();
    } else{
        cerr << "No such a command" << endl;
    }

    ofstream writeFile(path);
    for (auto i = 0; i < 30; ++i){
        OList temp;
        for (auto j = (toWork.data[i].data).first; j != nullptr; j = j->next){
            temp.push_back(j->key + ":" + j->value);
        }
        writeFile << (temp).join(',') << endl;
    }
    writeFile.close();
}
