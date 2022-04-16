#include <iostream>
#include ".\headers\Point.h"
#include ".\headers\SLine.h"
#include ".\headers\SNode.h"
#include ".\headers\status.h"
#include ".\SBalancedBST.cpp"

using namespace std;

int main()
{
    SBalancedBST bst;
    bst.root = NULL;
    y_sweepLine = 9;

    while (true)
    {
        int operation;
        cout << "Select operation:\n";
        cout << "1. Insert Line\n";
        cout << "2. Delete Line\n";
        cout << "3. Print Traversals of Current Tree\n";
        cin >> operation;
        cout << '\n';

        switch (operation)
        {
        case 1:
        {
            cout << "Enter endpoints of line to be inserted in the format: x1 y1 x2 y2\n";
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Line l = bst.createLine(x1, y1, x2, y2, 0);

            bst.root = bst.insertNode(bst.root, l);
            cout << '\n';
            break;
        }

        case 2:
        {
            cout << "Enter endpoints of line to be deleted in the format: x1 y1 x2 y2\n";
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Line l = bst.createLine(x1, y1, x2, y2, 0);

            bst.root = bst.deleteNode(bst.root, l);
            cout << '\n';
            break;
        }

        case 3:
        {
            bst.printTraversals(bst.root);
            cout << '\n';
            break;
        }

        default:
        {
            cout << "Enter a number between 1 and 4\n\n";
        }
        }
    }

    return 0;
}