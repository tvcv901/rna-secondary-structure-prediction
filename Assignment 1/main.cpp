#include <iostream>
#include ".\headers\EQNode.h"
#include ".\headers\EventQueue.h"
#include ".\headers\Point.h"
#include ".\headers\SLine.h"
#include ".\headers\SNode.h"
#include ".\headers\status.h"
#include "EQBalancedBST.cpp"
#include "SBalancedBST.cpp"

using namespace std;

int main()
{
    Point p1, p2, p3;
    p1.x = p2.x = 5.1234, p1.y = p2.y = 0.6789;
    cout << (p1 == p2) << '\n';
    cout << (p1 < p2) << '\n';
    cout << (p1 > p2) << '\n';

    p3 = p1;
    cout << (p1 == p3) << '\n';
    cout << (p1 < p3) << '\n';
    cout << (p1 > p3) << '\n';

    return 0;
}