#ifndef SBALANCED_BST_H
#define SBALANCED_BST_H

#include <iostream>
#include "Point.h"
#include "SLine.h"
#include "SNode.h"

using namespace std;

class SBalancedBST
{
public:
    int getBalanceFactor(LineNode *curNode);
    int getHeight(LineNode *curNode);
    Point createPoint(int x, int y);
    Line createLine(int x1, int y1, int x2, int y2);
    LineNode *createNode(Line l);
    LineNode *leftRotate(LineNode *curNode);
    LineNode *rightRotate(LineNode *curNode);
    LineNode *getLowestNode(LineNode *curNode);
    LineNode *getHighestNode(LineNode *curNode);
    LineNode *above(LineNode *curNode, Line l);
    LineNode *below(LineNode *curNode, Line l);
    LineNode *root;
    LineNode *insertNode(LineNode *curNode, Line l);
    LineNode *deleteNode(LineNode *curNode, Line l);
    void preorder(LineNode *curNode);
    void inorder(LineNode *curNode);
    void postorder(LineNode *curNode);
    void printTraversals(LineNode *curNode);
};

#endif