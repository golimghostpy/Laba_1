#include "Stack.h"

bool Stack::is_empty(){
    return head == nullptr;
}

void Stack::push(string value){
    ONode* new_elem = new ONode(value);

    if(is_empty()){
        head = new_elem;
        tail = new_elem;
    }

    new_elem->next = head;
    head = new_elem;
}

void Stack::pop(){
    if (is_empty()){
        cout << "Stack is empty" << endl;
        return;
    }

    ONode* new_head = head->next;
    cout << "Popped value: " << head->data << endl;
    delete head;
    head = new_head;
}

void Stack::print(){
    if (head == nullptr) return;

    ONode* curr = head;

    while(curr != tail){
        cout << curr->data << "->";
        curr = curr->next;
    }

    cout << curr->data << endl;
}

void stack_do(const string& path, OList& query){
    ifstream readFile(path);
    Stack toWork;
    string line;
    while (readFile >> line){
        toWork.push(line);
    }
    readFile.close();

    toWork.print();

    string token = query.find_at(0)->data;
    string item = "";
    if (query.size == 2){
        item = query.find_at(1)->data;
    }

    if (token == "SPUSH"){
        if (item == ""){
            cerr << "Can't push empty string" << endl;
            return;
        }
        toWork.push(item);
    } else if (token == "SPOP"){
        toWork.pop();
    } else if (token == "SPRINT"){
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
