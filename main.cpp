#include "libs.h"
#include "OList.h"
#include "DList.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "Array.h"
#include "AVLTree.h"
#include <getopt.h>



int main(int argc, char* argv[])
{
    int c;
    string file;
    string query;

    static struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"query", required_argument, 0, 'q'},
        {0, 0, 0, 0}
    };

    while((c = getopt_long(argc, argv, "f:q:", long_options, NULL)) != -1){
        switch(c){
            case 'f': file = optarg; break;
            case 'q': query = optarg; break;
            default: cerr << "Unknown option: " << c << endl; return 1;
        }
    }

    if (file.empty()){
        cerr << "You must write filename" << endl;
        return 1;
    }
    if (query.empty()){
        cerr << "You can't write empty command" << endl;
        return 1;
    }

    string path = "files/" + file;
    ifstream readFile(path);
    if (!readFile.is_open()){
        cerr << "No such a file" << endl;
        return 1;
    }
    readFile.close();

    OList splited = split(query, " ");
    char structToken = (splited.find_at(0)->data)[0];
    if(structToken == 'O'){
        olist_do(path, splited);
    }
    else if (structToken == 'D'){
        tlist_do(path, splited);
    }
    else if (structToken == 'S'){
        stack_do(path, splited);
    }
    else if (structToken == 'Q'){
        queue_do(path, splited);
    }
    else if (structToken == 'M'){
        array_do(path, splited);
    }
    else if (structToken == 'H'){
        hash_do(path, splited);
    }
    else if (structToken == 'T'){
        tree_do(path, splited);
    }
    else {
        cerr << "Wrong token" << endl;
    }

    return 0;
}
