#include "Queue.h"

bool Queue::is_empty(){
    return head == nullptr;
}

void Queue::push(string value){
    ONode* new_elem = new ONode(value);

    if (is_empty()){
        head = new_elem;
        tail = new_elem;
        return;
    }

    tail->next = new_elem;
    tail = new_elem;
}

void Queue::pop(){
    if (is_empty()){
        cout << "Queue is empty" << endl;
        return;
    }

    ONode* new_head = head->next;
    cout << "Popped value: " << head->data << endl;
    delete head;
    head = new_head;
}

void Queue::print(){
    ONode* curr = head;

    while (curr->next != nullptr){
        cout << curr->data << "<-";
        curr = curr->next;
    }
    cout << curr->data << endl;
}

void queue_do(const string& path, OList& query){
    ifstream readFile(path);
    Queue toWork;
    string line;
    while (readFile >> line){
        toWork.push(line);
    }
    readFile.close();

    string token = query.find_at(0)->data;
    string item = "";
    if (query.size == 2){
        item = query.find_at(1)->data;
    }

    if (token == "QPUSH"){
        if (item == ""){
            cerr << "Can't push empty string" << endl;
            return;
        }
        toWork.push(item);
    } else if (token == "QPOP"){
        toWork.pop();
    } else if (token == "QPRINT"){
        toWork.print();
    } else{
        cerr << "No such a command" << endl;
    }

    ofstream writeFile(path);
    for (auto i = toWork.head; i != toWork.tail; i = i->next){
        writeFile << i->data << endl;
    }
    writeFile << toWork.tail->data << endl;
    writeFile.close();
}
