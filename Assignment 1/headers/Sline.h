#ifndef LINE_H
#define LINE_H

#include <iostream>
#include "Point.h"

using namespace std;

int y_sweepLine; // y coordinate of sweep line

struct Line
{
    Point p1;
    Point p2;
    int lineNo;

    inline void operator=(const Line l)
    {
        this->p1 = l.p1;
        this->p2 = l.p2;
    }
};

float getX(Line a);

inline bool operator==(const Line a, const Line b)
{
    return (a.p1 == b.p1 && a.p2 == b.p2);
}

inline bool operator!=(const Line a, const Line b)
{
    return !(a == b);
}

inline bool operator>(const Line a, const Line b)
{
    float x1 = getX(a), x2 = getX(b);
    return (x1 > x2);
}

inline bool operator>=(const Line a, const Line b)
{
    float x1 = getX(a), x2 = getX(b);
    return (isEqual(x1, x2) || x1 > x2);
}

inline bool operator<(const Line a, const Line b)
{
    return !(a >= b);
}

inline bool operator<=(const Line a, const Line b)
{
    return !(a > b);
}

float getX(Line a)
{
    float m_inv = (a.p2.x - a.p1.x) / (a.p2.y - a.p1.y);
    float x = a.p1.x + (y_sweepLine - a.p1.y) * m_inv;
    return x;
}

#endif