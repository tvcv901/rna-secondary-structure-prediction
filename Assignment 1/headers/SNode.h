#ifndef SNODE_H
#define SNODE_H

#include <iostream>
#include "Point.h"
#include "SLine.h"

using namespace std;

/**
 * @brief LineNode structure is a node in the balanced binary search tree of Status.
 *
 */
struct LineNode
{
    Line line;
    LineNode *left;
    LineNode *right;
    int height;
};

/**
 * @brief Operator overloading to output the line and its height from leaf node in the balanced binary search tree.
 *
 * @param out Output stream to which coordinates of endpoints and height will be written.
 * @param curNode Node for which point coordinates and endpoints and height is required.
 * @return ostream& The output stream out.
 */
ostream &operator<<(ostream &out, const LineNode *curNode)
{
    out << "Line: ( (" << curNode->line.p1.x << ", " << curNode->line.p1.y << "), (" << curNode->line.p2.x << ", " << curNode->line.p2.y << ") ), Height: " << curNode->height << "\n";
    return out;
}

#endif