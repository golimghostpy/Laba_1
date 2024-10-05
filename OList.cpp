#include "OList.h"


bool OList::is_empty(){
    return first == nullptr;
}

void OList::push_front(string value){
    ONode* new_elem = new ONode(value);

    if(is_empty()){
        first = new_elem;
        last = new_elem;
        ++size;
        return;
    }

    new_elem->next = first;
    first = new_elem;
    ++size;
}

void OList::push_back(string value){
    ONode* new_elem = new ONode(value);

    if(is_empty()){
        first = new_elem;
        last = new_elem;
        ++size;
        return;
    }

    last->next = new_elem;
    last = new_elem;
    ++size;
}

void OList::delete_front(){
    if(is_empty()){
        cout << "List is empty" << endl;
        return;
    }

    ONode* toDel = first;
    first = first->next;
    delete toDel;
    --size;
}

void OList::delete_back(){
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
    --size;
}

void OList::delete_value(string value) {
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
    --size;
}

int OList::find_value(string value){
    ONode* curr = first;
    int index = 0;

    while (curr->data != value && curr != nullptr){
        curr = curr->next;
        ++index;
    }

    if (curr == nullptr) return -1;

    return index;
}

void OList::print(string delimiter){
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

ONode* OList::find_at(int index){
    int counter = 0;
    ONode* current = first;
    while (counter < index){
        current = current->next;
        ++counter;
    }
    return current;
}

string OList::join(const char symbol){
    string joined;
    ONode* current = first;
    while (current){
        joined += current->data + symbol;
        current = current->next;
    }
    return joined;
}

void olist_do(const string& path, OList& query){
    ifstream readFile(path);
    OList toWork;
    string line;
    while (readFile >> line){
        toWork.push_back(line);
    }
    readFile.close();

    string token = query.find_at(0)->data;
    string item = "";
    if (query.size == 2){
        item = query.find_at(1)->data;
    }

    if (token == "OLPUSHF"){
        if (item == ""){
            cerr << "Can't push empty string" << endl;
            return;
        }
        toWork.push_front(item);
    } else if (token == "OLPUSHB"){
        if (item == ""){
            cerr << "Can't push empty string" << endl;
            return;
        }
        toWork.push_back(item);
    } else if (token == "OLDELF"){
        toWork.delete_front();
    } else if (token == "OLDELB"){
        toWork.delete_back();
    } else if (token == "OLDELVAL"){
        if (item == ""){
            cerr << "Can't delete empty string" << endl;
            return;
        }
        toWork.delete_value(item);
    } else if (token == "OLFIND"){
        if (item == ""){
            cerr << "Can't find empty string" << endl;
            return;
        }
        int index = toWork.find_value(item);
        if (index == -1){
            cout << "This element isn't in list" << endl;
        }
        else{
            cout << "Index of element = " << index << endl;
        }
    } else if (token == "OLPRINT"){
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

OList split(const string& str, const string& delimiter) {
    OList result;
    string currentPart;
    int delimiterLength = delimiter.size();

    for (auto i = 0; i < str.size(); ++i) {
        int j = 0;
        while (j < delimiterLength && i + j < str.size() && str[i + j] == delimiter[j]) {
            ++j;
        }

        if (j == delimiterLength) {
            if (currentPart != "") {
                result.push_back(currentPart);
                currentPart = "";
            }
            i += delimiterLength - 1;
        } else {
            currentPart += str[i];
        }
    }

    if (!currentPart.empty()) {
        result.push_back(currentPart);
    }

    return result;
}
