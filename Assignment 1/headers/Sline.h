#ifndef LINE_H
#define LINE_H

#include <iostream>
#include "Point.h"

using namespace std;

int y_sweepLine; // y coordinate of sweep line

/**
 * @brief Line is a structure that contains the two endpoints
 *
 */
struct Line
{
    Point p1;
    Point p2;
    int lineNo;

    /**
     * @brief Assigns endpoints of a point to another line.
     *
     * @param l Line whose points are to be copied.
     */
    inline void operator=(const Line l)
    {
        this->p1 = l.p1;
        this->p2 = l.p2;
    }
};

/**
 * @brief Gets the x-coordinate of the intersection point of the sweep line and another line.
 *
 * @param a The x-coordinate of the intersection point is calculated for the sweep line and and this line.
 * @return double The x-coordinate of the intersection point.
 */
double getX(Line a);

/**
 * @brief Compares two line segements and checks if they are the same.
 *
 * @param a first Line
 * @param b second Line
 * @return true if a and b have the same endpoints
 * @return false if a and b do not have the same endpoints
 */
inline bool operator==(const Line a, const Line b)
{
    return (a.p1 == b.p1 && a.p2 == b.p2);
}

/**
 * @brief Compares two line segements and checks if they are not the same.
 *
 * @param a first Line
 * @param b second Line
 * @return true if a and b do not have the same endpoints
 * @return false if a and b have the same endpoints
 */
inline bool operator!=(const Line a, const Line b)
{
    return !(a == b);
}

/**
 * @brief Compares two line segements and checks if one line is greater than the other.
 *
 * @param a first Line
 * @param b second Line
 * @return true if a is greater than b
 * @return false if a is not greater than b
 */
inline bool operator>(const Line a, const Line b)
{
    double x1 = getX(a), x2 = getX(b);
    return (x1 > x2);
}

/**
 * @brief Compares two line segements and checks if one line is greater than or equal to the other.
 *
 * @param a first Line
 * @param b second Line
 * @return true if a is greater than or equal to b
 * @return false if a is not greater than or equal to b
 */
inline bool operator>=(const Line a, const Line b)
{
    double x1 = getX(a), x2 = getX(b);
    return (isEqual(x1, x2) || x1 > x2);
}

/**
 * @brief Compares two line segements and checks if one line is lesser than the other.
 *
 * @param a first Line
 * @param b second Line
 * @return true if a is lesser than b
 * @return false if a is not lesser than b
 */
inline bool operator<(const Line a, const Line b)
{
    return !(a >= b);
}

/**
 * @brief Compares two line segements and checks if one line is lesser than or equal to the other.
 *
 * @param a first Line
 * @param b second Line
 * @return true if a is lesser than or equal to b
 * @return false if a is not lesser than or equal to b
 */
inline bool operator<=(const Line a, const Line b)
{
    return !(a > b);
}

double getX(Line a)
{
    double m_inv = (a.p2.x - a.p1.x) / (a.p2.y - a.p1.y);
    double x = a.p1.x + (y_sweepLine - a.p1.y) * m_inv;
    return x;
}

#endif