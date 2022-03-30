#include <iostream>
#include ".\headers\Point.h"
#include ".\headers\EQNode.h"
#include ".\headers\EventQueue.h"

using namespace std;

int EQBalancedBST::getBalanceFactor(PointNode *curNode)
{
    if (curNode == NULL)
        return 0;

    PointNode *leftNode = curNode->left;
    PointNode *rightNode = curNode->right;
    return (getHeight(leftNode) - getHeight(rightNode));
}

int EQBalancedBST::getHeight(PointNode *curNode)
{
    if (curNode == NULL)
        return 0;

    return curNode->height;
}

Point EQBalancedBST::createPoint(float x, float y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

PointNode *EQBalancedBST::createNode(Point p)
{
    PointNode *node = new PointNode;
    node->point = p;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

PointNode *EQBalancedBST::leftRotate(PointNode *curNode)
{
    PointNode *x = curNode;
    PointNode *y = x->right;
    PointNode *b = y->left;

    y->left = x;
    x->right = b;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

PointNode *EQBalancedBST::rightRotate(PointNode *curNode)
{
    PointNode *y = curNode;
    PointNode *x = y->left;
    PointNode *b = x->right;

    x->right = y;
    y->left = b;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

PointNode *EQBalancedBST::getMin(PointNode *curNode)
{
    PointNode *minNode = curNode;
    while (minNode->left != NULL)
        minNode = minNode->left;

    return minNode;
}

void EQBalancedBST::printInorderTraversal(PointNode *curNode)
{
    if (curNode == NULL)
        return;

    printInorderTraversal(curNode->left);
    cout << curNode;
    printInorderTraversal(curNode->right);
}

void EQBalancedBST::printPreorderTraversal(PointNode *curNode)
{
    if (curNode == NULL)
        return;

    cout << curNode;
    printPreorderTraversal(curNode->left);
    printPreorderTraversal(curNode->right);
}

void EQBalancedBST::printPostorderTraversal(PointNode *curNode)
{
    if (curNode == NULL)
        return;

    printPostorderTraversal(curNode->left);
    printPostorderTraversal(curNode->right);
    cout << curNode;
}

PointNode *EQBalancedBST::insertNode(PointNode *curNode, Point p)
{
    if (curNode == NULL)
    {
        PointNode *newNode = createNode(p);
        return newNode;
    }

    PointNode *leftNode = curNode->left;
    PointNode *rightNode = curNode->right;

    if (p < curNode->point)
    {
        curNode->left = insertNode(leftNode, p);
    }
    else if (p > curNode->point)
    {
        curNode->right = insertNode(rightNode, p);
    }
    else
        return curNode;

    leftNode = curNode->left;
    rightNode = curNode->right;

    curNode->height = 1 + max(getHeight(leftNode), getHeight(rightNode));
    int balanceFactor = getBalanceFactor(curNode);

    // height of left subtree is greater than right subtree by more than 1
    if (balanceFactor > 1)
    {
        if (p < leftNode->point)
            return rightRotate(curNode);
        else if (p > leftNode->point)
        {
            curNode->left = leftRotate(leftNode);
            return rightRotate(curNode);
        }
    }

    // height of right subtree is greater than left subtree by more than 1
    if (balanceFactor < -1)
    {
        if (p > rightNode->point)
            return leftRotate(curNode);
        else if (p < rightNode->point)
        {
            curNode->right = rightRotate(rightNode);
            return leftRotate(curNode);
        }
    }

    return curNode;
}

PointNode *EQBalancedBST::findNode(PointNode *curNode, Point p)
{
    if (curNode == NULL || curNode->point == p)
        return curNode;

    if (p < curNode->point)
        return findNode(curNode->left, p);

    return findNode(curNode->right, p);
}

PointNode *EQBalancedBST::deleteNode(PointNode *curNode, Point p)
{
    if (curNode == NULL)
        return curNode;
    if (p < curNode->point)
        curNode->left = deleteNode(curNode->left, p);
    else if (p > curNode->point)
        curNode->right = deleteNode(curNode->right, p);
    else
    {
        PointNode *temp;
        if (curNode->left != NULL && curNode->right != NULL)
        {
            PointNode *nextLargest = getMin(curNode->right);
            curNode->point = nextLargest->point;
            curNode->right = deleteNode(curNode->right, curNode->point);
        }
        else if (curNode->left == NULL && curNode->right == NULL)
        {
            temp = curNode;
            curNode = NULL;
            free(temp);
        }
        else
        {
            // Note: you do not have to find next largest (or smallest) in this case
            // (since tree is balanced, the left or right node will replace the node to be deleted)
            if (curNode->left != NULL)
            {
                temp = curNode->left;
                *curNode = *temp;
            }
            else
            {
                temp = curNode->right;
                *curNode = *temp;
            }
            free(temp);
        }
    }

    if (curNode == NULL)
        return curNode;

    curNode->height = 1 + max(getHeight(curNode->left), getHeight(curNode->right));
    int balanceFactor = getBalanceFactor(curNode);

    if (balanceFactor > 1)
    {
        if (getBalanceFactor(curNode->left) >= 0)
            return rightRotate(curNode);
        else
        {
            curNode->left = leftRotate(curNode->left);
            return rightRotate(curNode);
        }
    }

    if (balanceFactor < -1)
    {
        if (getBalanceFactor(curNode->right) <= 0)
            return leftRotate(curNode);
        else
        {
            curNode->right = rightRotate(curNode->right);
            return leftRotate(curNode);
        }
    }

    return curNode;
}

void EQBalancedBST::printTraversals(PointNode *curNode)
{
    cout << "Inorder Traversal:\n";
    printInorderTraversal(curNode);

    cout << "\nPreorder Traversal:\n";
    printPreorderTraversal(curNode);

    cout << "\nPostorder Traversal:\n";
    printPostorderTraversal(curNode);
}