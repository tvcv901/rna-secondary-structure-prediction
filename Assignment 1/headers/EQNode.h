#ifndef EQNODE_H
#define EQNODE_H

#include <iostream>
#include "Point.h"

using namespace std;

/**
 * @brief PointNode structure is a node in a balanced binary search tree of Event Queue.
 *
 */
struct PointNode
{
    Point point;
    PointNode *left;
    PointNode *right;
    int height;
};

/**
 * @brief Operator overloading to output the point and its height from leaf node in the balanced binary search tree.
 *
 * @param out Output stream to which coordinates and height will be written.
 * @param curNode Node for which point coordinates and height is required.
 * @return ostream& The output stream out.
 */
ostream &operator<<(ostream &out, const PointNode *curNode)
{
    out << "Point: " << curNode->point << ", Height: " << curNode->height << "\n";
    return out;
}

#endif