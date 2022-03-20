#ifndef EQNODE_H
#define EQNODE_H

#include <iostream>
#include "Point.h"

using namespace std;

struct PointNode
{
    Point point;
    PointNode *left;
    PointNode *right;
    int height;
};

ostream &operator<<(ostream &out, const PointNode *curNode)
{
    out << "Point: " << curNode->point << ", Height: " << curNode->height << "\n";
    return out;
}

#endif