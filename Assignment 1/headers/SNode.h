#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "SPoint.h"
#include "SLine.h"

using namespace std;

struct Node
{
    Line line;
    Node *left;
    Node *right;
    int height;
};

ostream &operator<<(ostream &out, const Node *n)
{
    out << "Line: ( (" << n->line.p1.x << ", " << n->line.p1.y << "), (" << n->line.p2.x << ", " << n->line.p2.y << ") ), Height: " << n->height << "\n";
    return out;
}

#endif