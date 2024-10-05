#include "DList.h"

bool TList::is_empty(){
    return first == nullptr;
}

void TList::push_front(string value){
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

void TList::push_back(string value){
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

void TList::delete_front(){
    if(is_empty()){
        cout << "List is empty" << endl;
        return;
    }

    TNode* toDel = first;
    first = first->next;
    delete toDel;
}

void TList::delete_back(){
    if(is_empty()){
        cout << "List is empty" << endl;
        return;
    }

    TNode* toDel = last;
    last = last->prev;
    delete toDel;
}

void TList::delete_value(string value){
    if (is_empty()){
        cout << "No such a value" << endl;
        return;
    }

    if (first->data == value) {
        delete_front();
        return;
    }

    TNode* curr = first;

    while (curr != nullptr && curr->data != value) {
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

    curr->prev->next = curr->next;
    delete curr;
    --size;
}

int TList::find_value(string value){
    TNode* curr = first;
    int index = 0;

    while (curr->data != value && curr != nullptr){
        curr = curr->next;
        ++index;
    }

    if (curr == nullptr) {
        return -1;
    }
    return index;
}

void TList::print(string delimiter){
    TNode* curr = first;
    while(curr->next != nullptr){
        cout << curr->data << delimiter;
        curr = curr->next;
    }
    cout << curr->data << endl;
}

void tlist_do(const string& path, OList& query){
    ifstream readFile(path);
    TList toWork;
    string line;
    while (readFile >> line){
        toWork.push_back(line);
    }
    readFile.close();

    string token = query.find_at(0)->data;
    string item;
    if (query.size == 2){
        item = query.find_at(1)->data;
    }

    if (token == "DLPUSHF"){
        toWork.push_front(item);
    } else if (token == "DLPUSHB"){
        toWork.push_back(item);
    } else if (token == "DLDELF"){
        toWork.delete_front();
    } else if (token == "DLDELB"){
        toWork.delete_back();
    } else if (token == "DLDELVAL"){
        toWork.delete_value(item);
    } else if (token == "DLFIND"){
        int index = toWork.find_value(item);
        if (index == -1){
            cout << "This element isn't in list" << endl;
        }
        else{
            cout << "Index of element = " << index << endl;
        }
    } else if (token == "DLPRINT"){
        toWork.print(" ");
    } else{
        cerr << "No such a command" << endl;
    }

    ofstream writeFile(path);
    for (auto i = toWork.first; i != toWork.last; i = i->next){
        writeFile << i->data << endl;
    }
    writeFile << toWork.last->data << endl;
    writeFile.close();
}
