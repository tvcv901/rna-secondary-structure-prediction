#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>
#define EPSILON 1e-9

using namespace std;

bool isEqual(double a, double b);

class SBalancedBST;

/**
 * @brief Point is a structure that contains the x and y coordinates.
 *
 */
struct Point
{
    double x;
    double y;

    /**
     * @brief l is the set of line segments whose lower endpoint is at this point.
     * u is the set of line segements whose upper endpoint is at this point.
     * c is the set of line segments that have this point as an interior point.
     */
    SBalancedBST *l, *u, *c;

    /**
     * @brief Assigns x and y coordinates of a point to another point.
     *
     * @param p Point whose coordinates are to be copied.
     */
    inline void operator=(const Point p)
    {
        this->x = p.x;
        this->y = p.y;
    }
};

/**
 * @brief Checks whether two double values differ within a small value EPSILON.
 *
 * @param a first double.
 * @param b second double.
 * @return true if a and b differ by less than EPSILON.
 * @return false if a and b differ by more than or equal to EPSILON.
 */
bool isEqual(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

/**
 * @brief Compares two points and checks if they are equal.
 *
 * @param a first Point.
 * @param b second Point.
 * @return true if a and b are the same point.
 * @return false if a and b are not the same point.
 */
inline bool operator==(const Point a, const Point b)
{
    return (isEqual(a.x, b.x) && isEqual(a.y, b.y));
}

/**
 * @brief Compares two points and checks if they are not equal.
 *
 * @param a first Point.
 * @param b second Point.
 * @return true if they are not equal.
 * @return false if they are equal.
 */
inline bool operator!=(const Point a, const Point b)
{
    return !(a == b);
}

/**
 * @brief Compares two points and checks if one point is greater than the other.
 *
 * @param a first Point.
 * @param b second Point.
 * @return true if a is greater than b.
 * @return false if a is not greater than b.
 */
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

/**
 * @brief Compares two points and checks if one point is greater than or equal to the other.
 *
 * @param a first Point.
 * @param b second Point.
 * @return true if a is greater than or equal to b.
 * @return false if a is not greater than or equal to b.
 */
inline bool operator>=(const Point a, const Point b)
{
    if (isEqual(a.y, b.y))
        return (isEqual(a.x, b.x) || a.x > b.x);
    return a.y < b.y;
}

/**
 * @brief Compares two points and checks if one point is less than the other.
 *
 * @param a first Point.
 * @param b second Point.
 * @return true if a is less than b.
 * @return false if a is not less than b.
 */
inline bool operator<(const Point a, const Point b)
{
    return !(a >= b);
}

/**
 * @brief Compares two points and checks if one point is less than or equal to the other.
 *
 * @param a first Point.
 * @param b second Point.
 * @return true if a is less than or equal to b.
 * @return false if a is not less than or equal to b.
 */
inline bool operator<=(const Point a, const Point b)
{
    return !(a > b);
}

/**
 * @brief Operator overloading to output the x and y coordinates of the point.
 *
 * @param output Output stream to which x and y coordinates will be written.
 * @param p Point for which coordinates are required.
 * @return ostream& The output stream out.
 */
ostream &operator<<(ostream &output, const Point p)
{
    output << "( " << p.x << ", " << p.y << " )";
    return output;
}

#endif