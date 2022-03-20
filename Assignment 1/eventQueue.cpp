#include <iostream>
#include ".\headers\Point.h"
#include ".\headers\EQNode.h"
#include ".\headers\EventQueue.h"
#include "EQBalancedBST.cpp"

using namespace std;

int main()
{
    EQBalancedBST bst;
    bst.root = NULL;

    while (true)
    {
        int operation;
        cout << "Select operation:\n";
        cout << "1. Insert Point\n";
        cout << "2. Find Point\n";
        cout << "3. Delete Point\n";
        cout << "4. Print Traversals of Current Tree\n";
        cin >> operation;
        cout << '\n';

        switch (operation)
        {
        case 1:
        {
            cout << "Enter coordinates of point to be inserted in the format: x y\n";
            float x, y;
            cin >> x >> y;
            Point p = bst.createPoint(x, y);

            bst.root = bst.insertNode(bst.root, p);
            cout << '\n';
            break;
        }

        case 2:
        {
            cout << "Enter coordinates of point to be searched in the format: x y\n";
            float x, y;
            cin >> x >> y;
            Point p = bst.createPoint(x, y);

            PointNode *node = bst.findNode(bst.root, p);
            if (node != NULL)
            {
                cout << node->point << "\n\n";
            }
            else
            {
                cout << "Point does not exist\n\n";
            }
            break;
        }

        case 3:
        {
            cout << "Enter coordinates of point to be deleted in the format: x y\n";
            float x, y;
            cin >> x >> y;
            Point p = bst.createPoint(x, y);

            bst.root = bst.deleteNode(bst.root, p);
            cout << '\n';
            break;
        }

        case 4:
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