#include "Array.h"

void Array::push_back(string element) {
    if (size == capacity) {
        capacity *= 2;
        string* newData = new string[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[size++] = element;
}

void Array::insert_at(int index, string element) {
    if (index < 0 || index > size) {
        throw out_of_range("Index out of range");
    }
    if (size == capacity) {
        capacity *= 2;
        string* newData = new string[capacity];
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

string Array::get_at(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    return data[index];
}

void Array::remove_at(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    --size;
}

void Array::set_at(int index, string element) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    data[index] = element;
}

void Array::print() {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

void array_do(const string& path, OList& query){
    ifstream readFile(path);
    Array toWork;
    string line;
    while (readFile >> line){
        toWork.push_back(line);
    }
    readFile.close();

    string token = query.find_at(0)->data;
    string item = "";
    int index = -1;
    if (query.size == 2){
        item = query.find_at(1)->data;
    }
    else if (query.size == 3){
        index = stoi(query.find_at(1)->data);
        item = query.find_at(2)->data;
    }
    try{
        if (token == "MPUSHB"){
            if (item == ""){
                cerr << "Can't push empty string" << endl;
                return;
            }
            toWork.push_back(item);
        } else if(token == "MREPLACE"){
            if (item == ""){
                cerr << "Can't set empty string" << endl;
                return;
            }
            toWork.set_at(index, item);
        }else if (token == "MGET"){
            if (item == ""){
                cerr << "Can't find element without index" << endl;
                return;
            }
            cout << "Got item: " << toWork.get_at(stoi(item)) << endl;;
        } else if (token == "MDEL"){
            if (item == ""){
                cerr << "Can't find element without index" << endl;
                return;
            }
            toWork.remove_at(stoi(item));
        } else if (token == "MLENGTH"){
            cout << toWork.size << endl;
        } else if (token == "MPRINT"){
            toWork.print();
        } else{
            cerr << "No such a command" << endl;
        }
    } catch (const char* err){
        cerr << err << endl;
    }

    ofstream writeFile(path);
    for (auto i = 0; i < toWork.size; ++i){
        writeFile << (toWork.data)[i] << endl;
    }
    writeFile.close();
}
