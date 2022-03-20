#ifndef BALANCED_BST_H
#define BALANCED_BST_H

#include <iostream>
#include "SPoint.h"
#include "SLine.h"
#include "SNode.h"

using namespace std;

class SBalancedBST
{
public:
    int getBalanceFactor(Node *curNode);
    int getHeight(Node *curNode);
    Point createPoint(int x, int y);
    Line createLine(int x1, int y1, int x2, int y2);
    Node *createNode(Line l);
    Node *leftRotate(Node *curNode);
    Node *rightRotate(Node *curNode);
    Node *getLowestNode(Node *curNode);
    Node *getHighestNode(Node *curNode);
    Node *above(Node *curNode, Line l);
    Node *below(Node *curNode, Line l);
    Node *root;
    Node *insertNode(Node *curNode, Line l);
    Node *deleteNode(Node *curNode, Line l);
    void preorder(Node *curNode);
    void inorder(Node *curNode);
    void postorder(Node *curNode);
    void printTraversals(Node *curNode);
};

#endif