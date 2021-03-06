#include "tree.h"
#include <iostream>
#include <string.h>

using namespace std;

struct TreeNode
{
   int value;
   TreeNode *leftChild;
   TreeNode *rightChild;
   char code[codeSize];
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
    for (int i = 0; i < codeSize; i++)
        node->code[i] = '\0';
    return node;
}

Tree *createTreeWithKidsTrees(Tree *first, Tree *second)
{
    Tree *newTree = createTree();
    add(newTree, '\0', 0);
    newTree->root->leftChild = first->root;
    newTree->root->rightChild = second->root;
    newTree->key = first->key + second->key;
    delete first;
    delete second;
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

void stringAdd(char *str, char ch, char codes[codeSize])
{
    if (str[0] == '\0')
    {
        codes[0] = ch;
        return;
    }
    int length = strlen(str);
    for (int i = 0; i < length; i++)
    {
        codes[i] = str[i];
    }
    codes[length] = ch;
}

int key(Tree *tree)
{
    return tree->key;
}

void getCodes(TreeNode *node, char codes[256][codeSize])
{
    if (node->leftChild == nullptr)
    {
        for (int i = 0; i < codeSize; i++)
        {
            codes[node->value][i] = node->code[i];
        }
        return;
    }

    stringAdd(node->code, '0', node->leftChild->code);
    stringAdd(node->code, '1', node->rightChild->code);

    getCodes(node->leftChild, codes);
    getCodes(node->rightChild, codes);
}

void getCodes(Tree *tree, char codes[256][codeSize])
{
    strcpy(tree->root->code, "");
    getCodes(tree->root, codes);
}
