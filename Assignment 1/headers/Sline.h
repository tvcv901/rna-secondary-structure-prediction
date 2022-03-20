#ifndef LINE_H
#define LINE_H

#include <iostream>
#include "Point.h"

using namespace std;

struct Line
{
    Point p1;
    Point p2;

    inline void operator=(const Line l)
    {
        this->p1 = l.p1;
        this->p2 = l.p2;
    }
};

inline bool operator==(const Line l1, const Line l2)
{
    return ((l1.p1.x == l2.p1.x) && (l1.p1.y == l2.p1.y) && (l1.p2.x == l2.p2.x) && (l1.p2.y == l2.p2.y));
}

inline bool operator!=(const Line l1, const Line l2)
{
    return !(l1 == l2);
}

inline bool operator<(const Line l1, const Line l2)
{
    return ((l1.p1.y > l2.p1.y) || ((l1.p1.y == l2.p1.y) && (l1.p1.x < l2.p1.x)));
}

inline bool operator>(const Line l1, const Line l2)
{
    return ((l1.p1.y < l2.p1.y) || ((l1.p1.y == l2.p1.y) && (l1.p1.x > l2.p1.x)));
}

#endif