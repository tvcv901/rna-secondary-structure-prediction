#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Point.h"
#include "SLine.h"

using namespace std;

struct LineNode
{
    Line line;
    LineNode *left;
    LineNode *right;
    int height;
};

ostream &operator<<(ostream &out, const LineNode *curNode)
{
    out << "Line: ( (" << curNode->line.p1.x << ", " << curNode->line.p1.y << "), (" << curNode->line.p2.x << ", " << curNode->line.p2.y << ") ), Height: " << curNode->height << "\n";
    return out;
}

#endif