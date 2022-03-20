#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>
#define EPSILON 1e-9

using namespace std;

bool isEqual(float a, float b);

struct Point
{
    float x;
    float y;

    inline void operator=(const Point p)
    {
        this->x = p.x;
        this->y = p.y;
    }
};

bool isEqual(float a, float b)
{
    return fabs(a - b) < EPSILON;
}

inline bool operator==(const Point a, const Point b)
{
    return (isEqual(a.x, b.x) && isEqual(a.y, b.y));
}

inline bool operator!=(const Point a, const Point b)
{
    return !(a == b);
}

inline bool operator>(const Point a, const Point b)
{
    if (isEqual(a.y, b.y))
    {
        if (isEqual(a.x, b.x))
            return false;
        return a.x > b.x;
    }
    return a.y < b.y;
}

inline bool operator>=(const Point a, const Point b)
{
    if (isEqual(a.y, b.y))
        return (isEqual(a.x, b.x) || a.x > b.x);
    return a.y < b.y;
}

inline bool operator<(const Point a, const Point b)
{
    return !(a >= b);
}

inline bool operator<=(const Point a, const Point b)
{
    return !(a > b);
}

ostream &operator<<(ostream &output, const Point p)
{
    output << "( " << p.x << ", " << p.y << " )";
    return output;
}

#endif