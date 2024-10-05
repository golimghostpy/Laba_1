#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include "libs.h"
#include "OList.h"

struct TreeNode {
    string key;
    TreeNode* left;
    TreeNode* right;
    int height;
};

struct AVLTree {
    TreeNode* root;

    AVLTree() : root(nullptr) {}

    void insert(string);
    bool search(string);
    void remove(string);
    void print();
    int getHeight(TreeNode*);
    TreeNode* minValueNode(TreeNode*);
    int getBalance(TreeNode*);
    TreeNode* insertNode(TreeNode*, string);
    bool searchNode(TreeNode*, string);
    TreeNode* removeNode(TreeNode*, string);
    void printNode(TreeNode*, int);
    TreeNode* rotateRight(TreeNode*);
    TreeNode* rotateLeft(TreeNode*);
};

string to_string_tree(AVLTree*);
string to_string_node(TreeNode*);
void tree_do(const string&, OList&);

#endif // AVLTREE_H_INCLUDED
