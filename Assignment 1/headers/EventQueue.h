#ifndef EQBALANCED_BST_H
#define EQBALANCED_BST_H

#include <iostream>
#include "Point.h"
#include "EQNode.h"

using namespace std;

class EQBalancedBST
{
public:
    int getBalanceFactor(PointNode *curNode);
    int getHeight(PointNode *curNode);
    Point createPoint(float x, float y);
    PointNode *createNode(Point p);
    PointNode *leftRotate(PointNode *curNode);
    PointNode *rightRotate(PointNode *curNode);
    PointNode *getMin(PointNode *curNode);
    void printInorderTraversal(PointNode *curNode);
    void printPreorderTraversal(PointNode *curNode);
    void printPostorderTraversal(PointNode *curNode);
    PointNode *root;
    PointNode *insertNode(PointNode *curNode, Point p);
    PointNode *findNode(PointNode *curNode, Point p);
    PointNode *deleteNode(PointNode *curNode, Point p);
    void printTraversals(PointNode *curNode);
};

#endif