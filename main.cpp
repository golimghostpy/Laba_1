#include <iostream>

using namespace std;

struct ONode{
    string data;
    ONode* next;

    ONode(string val) : data(val), next(nullptr){}
};

struct TNode{
    string data;
    TNode* next;
    TNode* prev;

    TNode(string val) : data(val), next(nullptr), prev(nullptr){}
};

struct OList{
    ONode* first;
    ONode* last;

    OList() : first(nullptr), last(nullptr){}

    bool is_empty(){
        return first == nullptr;
    }

    void push_front(string value){
        ONode* new_elem = new ONode(value);

        if(is_empty()){
            first = new_elem;
            last = new_elem;
            return;
        }

        new_elem->next = first;
        first = new_elem;
    }

    void push_back(string value){
        ONode* new_elem = new ONode(value);

        if(is_empty()){
            first = new_elem;
            last = new_elem;
            return;
        }

        last->next = new_elem;
        last = new_elem;
    }

    void delete_front(){
        if(is_empty()){
            cout << "List is empty" << endl;
            return;
        }

        ONode* toDel = first;
        first = first->next;
        delete toDel;
    }

    void delete_back(){
        if(is_empty()){
            cout << "List is empty" << endl;
            return;
        }

        ONode* curr = first;
        while (curr->next != last){
            curr = curr->next;
        }

        last = curr;
        delete curr->next;
    }

    void delete_value(string value) {
        if (is_empty()){
            cout << "No such a value" << endl;
            return;
        }

        if (first->data == value) {
            delete_front();
            return;
        }

        ONode* curr = first;
        ONode* prev = nullptr;

        while (curr != nullptr && curr->data != value) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "No such a value" << endl;
            return;
        }

        if (curr == last) {
            delete_back();
            return;
        }

        prev->next = curr->next;
        delete curr;
    }

    ONode* find_value(string value){
        ONode* curr = first;

        while (curr->data != value && curr != nullptr){
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "No such a value" << endl;
            return nullptr;
        }
        return curr;
    }

    void print(string delimiter){
        if(is_empty()){
            cout << endl;
            return;
        }

        ONode* curr = first;

        while(curr->next != nullptr){
            cout << curr->data << delimiter;
            curr = curr->next;
        }
        cout << curr->data << endl;
    }
};

struct TList{
    TNode* first;
    TNode* last;

    TList() : first(nullptr), last(nullptr){}

    bool is_empty(){
        return first == nullptr;
    }

    void push_front(string value){
        TNode* new_elem = new TNode(value);

        if(is_empty()){
            first = new_elem;
            last = new_elem;
            return;
        }

        new_elem->next = first;
        first->prev = new_elem;
        first = new_elem;
    }

    void push_back(string value){
        TNode* new_elem = new TNode(value);

        if(is_empty()){
            first = new_elem;
            last = new_elem;
            return;
        }

        last->next = new_elem;
        new_elem->prev = last;
        last = new_elem;
    }

    void delete_front(){
        if(is_empty()){
            cout << "List is empty" << endl;
            return;
        }

        TNode* toDel = first;
        first = first->next;
        delete toDel;
    }

    void delete_back(){
        if(is_empty()){
            cout << "List is empty" << endl;
            return;
        }

        TNode* toDel = last;
        last = last->prev;
        delete toDel;
    }

    void delete_value(string value){
        if (first->data == value){
            delete_front();
            return;
        } else if(last->data == value){
            delete_back();
            return;
        }

        TNode* curr = first;

        while (curr->next->data != value && curr->next != nullptr){
            curr = curr->next;
        }

        if(curr->next == nullptr){
            cout << "No such a value" << endl;
            return;
        }

        TNode* toDel = curr->next;
        curr->next = toDel->next;
        delete toDel;
    }

    TNode* find_value(string value){
        TNode* curr = first;

        while (curr->data != value && curr != nullptr){
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "No such a value" << endl;
            return nullptr;
        }
        return curr;
    }

    void print(string delimiter){
        TNode* curr = first;
        while(curr->next != nullptr){
            cout << curr->data << delimiter;
            curr = curr->next;
        }
        cout << curr->data << endl;
    }
};

struct Stack{
    ONode* head;
    ONode* tail;

    Stack() : head(nullptr), tail(nullptr){}

    bool is_empty(){
        return head == nullptr;
    }

    void push(string value){
        ONode* new_elem = new ONode(value);

        if(is_empty()){
            head = new_elem;
            tail = new_elem;
        }

        new_elem->next = head;
        head = new_elem;
    }

    void pop(){
        if (is_empty()){
            cout << "Stack is empty" << endl;
            return;
        }

        ONode* new_head = head->next;
        cout << "Popped value: " << head->data << endl;
        delete head;
        head = new_head;
    }

    void print(){
        ONode* curr = head;

        while(curr != tail){
            cout << curr->data << "->";
            curr = curr->next;
        }

        cout << curr->data << endl;
    }
};

struct Queue{
    ONode* head;
    ONode* tail;

    Queue() : head(nullptr), tail(nullptr){}

    bool is_empty(){
        return head == nullptr;
    }

    void push(string value){
        ONode* new_elem = new ONode(value);

        if (is_empty()){
            head = new_elem;
            tail = new_elem;
            return;
        }

        tail->next = new_elem;
        tail = new_elem;
    }

    void pop(){
        if (is_empty()){
            cout << "Queue is empty" << endl;
            return;
        }

        ONode* new_head = head->next;
        cout << "Popped value: " << head->data << endl;
        delete head;
        head = new_head;
    }

    void print(){
        ONode* curr = head;

        while (curr->next != nullptr){
            cout << curr->data << "<-";
            curr = curr->next;
        }
        cout << curr->data << endl;
    }
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

    void add(int key){
        HashBucket* newBucket = new HashBucket(key);

        if (first == nullptr){
            first = newBucket;
            last = newBucket;
            return;
        }

        last->nextBucket = newBucket;
        last = newBucket;
    }

    int hash(const string& value){
        int summ = 0;
        for (auto i: value){
            summ += static_cast<int>(i);
        }

        return summ % 30;
    }

    void set(string value){
        int valKey = hash(value);

        HashBucket* currBucket = first;
        for (int i = 0; i != valKey; ++i){
            currBucket = currBucket->nextBucket;
        }

        (currBucket->data).push_back(value);
    }

    OList get_values(int key){
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

    void delete_value(const string& value){
        int valKey = hash(value);

        HashBucket* currBucket = first;
        for (int i = 0; i != valKey; ++i){
            currBucket = currBucket->nextBucket;
        }

        (currBucket->data).delete_value(value);
    }

    void print(){
        HashBucket* currBucket = first;
        for (int i = 0; i < 30; ++i){
            cout << i << ": ";
            (currBucket->data).print(", ");
            currBucket = currBucket->nextBucket;
        }
        cout << endl;
    }
};

struct Array {
    int* data;
    int size;
    int capacity;

    Array(int initialCapacity = 10) : size(0), capacity(initialCapacity) {
        data = new int[capacity];
    }

    void push_back(int element) {
        if (size == capacity) {
            capacity *= 2;
            int* newData = new int[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = element;
    }

    void insert_at(int index, int element) {
        if (index < 0 || index > size) {
            throw out_of_range("Index out of range");
        }
        if (size == capacity) {
            capacity *= 2;
            int* newData = new int[capacity];
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

    int get_at(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    void remove_at(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        --size;
    }

    void set_at(int index, int element) {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            return;
        }
        data[index] = element;
    }

    int length() {
        return size;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    OList test;
    test.delete_back();
    test.push_back("aboba");
    test.push_front("chipi");
    test.push_back("chapa");
    test.print(" ");
    test.delete_value("aboba");
    test.delete_value("appa");
    test.print(" ");
    cout << "----------------" << endl;

    Queue test1;
    test1.push("a");
    test1.push("b");
    test1.push("c");
    test1.push("d");
    test1.print();
    test1.pop();
    test1.print();
    cout << "----------------" << endl;


    try{
        Array test2;
        test2.push_back(1);
        test2.push_back(6);
        test2.push_back(13);
        test2.push_back(4);
        test2.remove_at(2);
        test2.print();
    }catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
