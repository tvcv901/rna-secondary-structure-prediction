#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

struct Point
{
    int x;
    int y;

    inline void operator=(const Point p)
    {
        this->x = p.x;
        this->y = p.y;
    }
};

#endif