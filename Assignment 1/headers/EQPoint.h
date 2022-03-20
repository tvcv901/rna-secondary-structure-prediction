#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

struct Point
{
    int x;
    int y;

    inline void operator=(const Point a)
    {
        this->x = a.x;
        this->y = a.y;
    }
};

inline bool operator==(const Point a, const Point b)
{
    return (a.x == b.x && a.y == b.y);
}

inline bool operator!=(const Point a, const Point b)
{
    return (a.x != b.x || a.y != b.y);
}

inline bool operator>(const Point a, const Point b)
{
    if (a.y == b.y)
        return a.x > b.x;
    return a.y < b.y;
}

inline bool operator>=(const Point a, const Point b)
{
    if (a.y == b.y)
        return a.x >= b.x;
    return a.y < b.y;
}

inline bool operator<(const Point a, const Point b)
{
    if (a.y == b.y)
        return a.x < b.x;
    return a.y > b.y;
}

inline bool operator<=(const Point a, const Point b)
{
    if (a.y == b.y)
        return a.x <= b.x;
    return a.y > b.y;
}

ostream &operator<<(ostream &output, const Point p)
{
    output << "( " << p.x << ", " << p.y << " )\n";
    return output;
}

#endif