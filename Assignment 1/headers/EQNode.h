#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "EQPoint.h"

using namespace std;

struct Node
{
    Point point;
    Node *left;
    Node *right;
    int height;
};

#endif