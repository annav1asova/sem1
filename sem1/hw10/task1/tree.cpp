#include "tree.h"
#include <iostream>
#include <string.h>

using namespace std;

struct TreeNode
{
   int value;
   TreeNode *leftChild;
   TreeNode *rightChild;
   char *code;
};

struct Tree
{
    TreeNode *root;
    int key;
};

Tree *createTree()
{
    Tree *tree = new Tree;
    tree->root = nullptr;
    tree->key = 0;
    return tree;
}

TreeNode *createNewNode(int value, TreeNode *left, TreeNode *right)
{
    TreeNode *node = new TreeNode;
    node->value = value;
    node->leftChild = left;
    node->rightChild = right;
    return node;
}

Tree *createTreeWithKidsTrees(Tree *first, Tree *second)
{
    Tree *newTree = createTree();
    add(newTree, '\0', 0);
    newTree->root->leftChild = first->root;
    newTree->root->rightChild = second->root;
    newTree->key = first->key + second->key;
    return newTree;
}

void deleteTree(TreeNode *node)
{
    if (node == nullptr)
        return;

     deleteTree(node->leftChild);
     deleteTree(node->rightChild);
     delete node;
}

void deleteTree(Tree *tree)
{
    deleteTree(tree->root);
    delete tree;
}

void printTree(TreeNode *node, ofstream &fout)
{
    if (node == nullptr)
    {
        fout << " null";
        return;
    }

    fout << " (";
    fout << node->value;

    printTree(node->leftChild, fout);
    printTree(node->rightChild, fout);
    fout << ")";
}

void printTree(Tree *tree, ofstream &f)
{
    printTree(tree->root, f);
}

void add(TreeNode *&node, int value)
{
    if (node == nullptr)
    {
        node = createNewNode(value, nullptr, nullptr);
        return;
    }
    if (node->value == value)
        return;
    if (node->value > value)
        add(node->leftChild, value);
    if (node->value < value)
        add(node->rightChild, value);
}

void add(Tree *tree, int value, int key)
{
    add(tree->root, value);
    tree->key = key;
}

bool exists(TreeNode *node, int value)
{
    if (node == nullptr)
        return false;
    if (value == node->value)
        return true;
    if (value > node->value)
        return exists(node->rightChild, value);
    if (value < node->value)
        return exists(node->leftChild, value);
}

bool exists(Tree *tree, int value)
{
    return exists(tree->root, value);
}

char *stringAdd(char *str, char ch)
{
    if (str == nullptr)
    {
        char *newString = new char[1];
        newString[0] = ch;
        newString[1] = '\0';
        return newString;
    }
    int length = strlen(str);
    char *newString = new char[length + 1];
    for (int i = 0; i < length; i++)
    {
        newString[i] = str[i];
    }
    newString[length] = ch;
    newString[length + 1] = '\0';
    return newString;
}

int key(Tree *tree)
{
    return tree->key;
}

void getCodes(TreeNode *node, int length, char **codes)
{
    if (node->leftChild == nullptr)
    {
        codes[node->value] = new char[length + 1];
        strcpy(codes[node->value], node->code);
        return;
    }

    node->leftChild->code = stringAdd(node->code, '0');
    node->rightChild->code = stringAdd(node->code, '1');

    length++;

    getCodes(node->leftChild, length, codes);
    getCodes(node->rightChild, length, codes);
}

char **getCodes(Tree *tree)
{
    char **codes = new char*[256];
    for (int i = 0; i < 256; i++)
        codes[i] = nullptr;

    tree->root->code = "";
    getCodes(tree->root, 0, codes);
    return codes;
}

