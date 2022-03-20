#ifndef BALANCED_BST_H
#define BALANCED_BST_H

#include <iostream>
#include "EQPoint.h"
#include "EQNode.h"

using namespace std;

class EQBalancedBST
{
public:
    int getBalanceFactor(Node *curNode);
    int getHeight(Node *curNode);
    Point createPoint(int x, int y);
    Node *createNode(Point p);
    Node *leftRotate(Node *curNode);
    Node *rightRotate(Node *curNode);
    Node *getMin(Node *curNode);
    void printInorderTraversal(Node *curNode);
    void printPreorderTraversal(Node *curNode);
    void printPostorderTraversal(Node *curNode);
    Node *root;
    Node *insertNode(Node *curNode, Point p);
    Node *findNode(Node *curNode, Point p);
    Node *deleteNode(Node *curNode, Point p);
    void printTraversals(Node *curNode);
};

#endif