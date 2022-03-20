#include <iostream>
#include ".\headers\Point.h"
#include ".\headers\SLine.h"
#include ".\headers\SNode.h"
#include ".\headers\status.h"

using namespace std;

int SBalancedBST::getBalanceFactor(LineNode *curNode)
{
    if (curNode == NULL)
        return 0;
    return (getHeight(curNode->left) - getHeight(curNode->right));
}

int SBalancedBST::getHeight(LineNode *curNode)
{
    if (curNode == NULL)
        return 0;
    return curNode->height;
}

Point SBalancedBST::createPoint(float x, float y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Line SBalancedBST::createLine(float x1, float y1, float x2, float y2)
{
    Line l;
    l.p1 = createPoint(x1, y1);
    l.p2 = createPoint(x2, y2);
    return l;
}

LineNode *SBalancedBST::createNode(Line l)
{
    LineNode *node = new LineNode;
    node->line = l;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

LineNode *SBalancedBST::leftRotate(LineNode *x)
{
    LineNode *y = x->right;
    LineNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

LineNode *SBalancedBST::rightRotate(LineNode *x)
{
    LineNode *y = x->left;
    LineNode *z = y->right;
    y->right = x;
    x->left = z;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

LineNode *SBalancedBST::insertNode(LineNode *curNode, Line l)
{
    if (curNode == NULL)
    {
        struct LineNode *temp = createNode(l);
        return temp;
    }
    if (l < curNode->line)
        curNode->left = insertNode(curNode->left, l);
    else if (l > curNode->line)
        curNode->right = insertNode(curNode->right, l);
    else
        return curNode;
    curNode->height = 1 + max(getHeight(curNode->left), getHeight(curNode->right));
    int balance = getBalanceFactor(curNode);
    if (balance > 1)
    {
        if (l < (curNode->left)->line)
            return rightRotate(curNode);
        if (l > (curNode->left)->line)
        {
            curNode->left = leftRotate(curNode->left);
            return rightRotate(curNode);
        }
    }
    if (balance < -1)
    {
        if (l > (curNode->right)->line)
            return leftRotate(curNode);
        if (l < (curNode->right)->line)
        {
            curNode->right = rightRotate(curNode->right);
            return leftRotate(curNode);
        }
    }
    return curNode;
}

LineNode *SBalancedBST::getLowestNode(LineNode *curNode)
{
    LineNode *lowestNode = curNode;
    while (lowestNode->left != NULL)
        lowestNode = lowestNode->left;
    return lowestNode;
}

LineNode *SBalancedBST::getHighestNode(LineNode *curNode)
{
    LineNode *highestNode = curNode;
    while (highestNode->right != NULL)
        highestNode = highestNode->right;
    return highestNode;
}

LineNode *SBalancedBST::above(LineNode *curNode, Line l)
{
    LineNode *pre = NULL;
    LineNode *cur = curNode;
    while (cur->line != l)
    {
        if (l > cur->line)
        {
            if (pre == NULL)
                pre = cur;
            else
            {
                if (pre->line < cur->line)
                    pre = cur;
            }
        }
        if (l < cur->line)
            cur = cur->left;
        else
            cur = cur->right;
    }
    if (cur->left != NULL)
        return getHighestNode(cur->left);
    return pre;
}

LineNode *SBalancedBST::below(LineNode *curNode, Line l)
{
    LineNode *suc = NULL;
    LineNode *cur = curNode;
    while (cur->line != l)
    {
        if (l < cur->line)
        {
            if (suc == NULL)
                suc = cur;
            else
            {
                if (suc->line > cur->line)
                    suc = cur;
            }
        }
        if (l < cur->line)
            cur = cur->left;
        else
            cur = cur->right;
    }
    if (cur->right != NULL)
        return getLowestNode(cur->right);
    return suc;
}

LineNode *SBalancedBST::deleteNode(LineNode *curNode, Line l)
{
    if (curNode == NULL)
        return curNode;
    if (l < curNode->line)
        curNode->left = deleteNode(curNode->left, l);
    else if (l > curNode->line)
        curNode->right = deleteNode(curNode->right, l);
    else
    {
        if ((curNode->left == NULL) || (curNode->right == NULL))
        {
            LineNode *temp;
            if (curNode->left != NULL)
                temp = curNode->left;
            else
                temp = curNode->right;
            if (temp == NULL)
            {
                temp = curNode;
                curNode = NULL;
            }
            else
                *curNode = *temp;
            free(temp);
        }
        else
        {
            LineNode *temp = getLowestNode(curNode->right);
            curNode->line = temp->line;
            curNode->right = deleteNode(curNode->right, temp->line);
        }
    }
    if (curNode == NULL)
        return curNode;
    curNode->height = 1 + max(getHeight(curNode->left), getHeight(curNode->right));
    int balance = getBalanceFactor(curNode);
    if (balance > 1)
    {
        if (getBalanceFactor(curNode->left) >= 0)
            return rightRotate(curNode);
        else
        {
            curNode->left = leftRotate(curNode->left);
            return rightRotate(curNode);
        }
    }
    if (balance < -1)
    {
        if (getBalanceFactor(curNode->left) >= 0)
            return leftRotate(curNode);
        else
        {
            curNode->right = rightRotate(curNode->right);
            return leftRotate(curNode);
        }
    }
    return curNode;
}

void SBalancedBST::preorder(LineNode *curNode)
{
    if (curNode != NULL)
    {
        cout << curNode;
        preorder(curNode->left);
        preorder(curNode->right);
    }
}

void SBalancedBST::inorder(LineNode *curNode)
{
    if (curNode != NULL)
    {
        inorder(curNode->left);
        cout << curNode;
        inorder(curNode->right);
    }
}

void SBalancedBST::postorder(LineNode *curNode)
{
    if (curNode == NULL)
        return;
    postorder(curNode->left);
    postorder(curNode->right);
    cout << curNode;
}

void SBalancedBST::printTraversals(LineNode *curNode)
{
    cout << "Inorder Traversal:\n";
    inorder(curNode);
    cout << '\n';

    cout << "Preorder Traversal:\n";
    preorder(curNode);
    cout << '\n';

    cout << "Postorder Traversal:\n";
    postorder(curNode);
    cout << '\n';
}
