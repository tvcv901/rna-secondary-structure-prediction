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

void createSet(Point *p);
void handleEventPoint(Point p);
void dfs(LineNode *curNode, bool add); // for removing or adding lines to status
void findNewEvent(Line sl, Line sr, Point p);
bool detectedIntersection(Line l1, Line l2);
Point calculateIntersection(Line l1, Line l2);
int orientation(Point p, Point q, Point r);
bool onSegment(Point p, Point q, Point r);

FILE *inputFile = fopen("input.txt", "r");
FILE *outputFile = fopen("output.txt", "w");

EQBalancedBST Q;       // event queue
SBalancedBST T;        // status
int intersections = 0; // number of intersections

int main()
{
    int n; // number of lines
    fscanf(inputFile, "%d", &n);
    Line l[n];

    // insert all endpoints into the event queue
    for (int i = 0; i < n; i++)
    {
        float x1, y1, x2, y2;
        fscanf(inputFile, "%f%f%f%f", &x1, &y1, &x2, &y2);
        Point p1 = Q.createPoint(x1, y1);
        Point p2 = Q.createPoint(x2, y2);
        if (p1 > p2)
        {
            swap(p1, p2);
            swap(x1, x2);
            swap(y1, y2);
        }
        l[i] = T.createLine(x1, y1, x2, y2, i);

        createSet(&p1);
        createSet(&p2);

        (p1.u)->root = (p1.u)->insertNode((p1.u)->root, l[i]);
        (p2.l)->root = (p2.l)->insertNode((p2.l)->root, l[i]);
        Q.root = Q.insertNode(Q.root, p1);
        Q.root = Q.insertNode(Q.root, p2);
    }

    // keep processing event points until event queue is empty
    while (Q.root != NULL)
    {
        // delete topmost point
        PointNode *node = Q.getMin(Q.root);
        cout << "Handling Point " << node->point << '\n'; // this part does not print correctly
        Point p = node->point;
        Q.root = Q.deleteNode(Q.root, node->point);

        handleEventPoint(node->point);
    }

    return 0;
}

void createSet(Point *p)
{
    p->l = new SBalancedBST;
    p->u = new SBalancedBST;
    p->c = new SBalancedBST;
    (p->l)->root = NULL;
    (p->u)->root = NULL;
    (p->c)->root = NULL;
}

void handleEventPoint(Point p)
{
    cout << (p.u)->root;
    (p.u)->printTraversals((p.u)->root);
    int segments = ((p.l)->root != NULL) + ((p.u)->root != NULL) + ((p.c)->root != NULL);
    // cout << segments << '\n';
    if (segments > 1) // report intersection point
    {
        // print point and its intersecting lines (all the lines present in p.l, p.u and p.c)
        cout << "Point: " << p;
        intersections++;
    }
    dfs((p.l)->root, false); // remove all lines in T that have lower endpoint as p
    dfs((p.c)->root, false); // remove all lines in T that contain p (will be added to T again)

    dfs((p.u)->root, true); // add all lines to T that have upper endpoint as p
    y_sweepLine -= 2 * EPSILON;
    dfs((p.c)->root, true); // add all lines to T that contain p (order of these lines are reversed)

    if ((p.u)->root == NULL && (p.c)->root == NULL)
    {
        LineNode *ln = (p.l)->getLowestNode((p.l)->root);
        LineNode *rn = (p.l)->getHighestNode((p.l)->root);
        Line sl = ln->line, sr = rn->line;
        // get left and right neighbours of p in T
        findNewEvent(sl, sr, p); // check if they intersect
        // note: sl or/and sr can be null
    }
    else
    {
        Line s_, s__, sl, sr;
        LineNode *ls_;
        LineNode *lsu = (p.u)->getLowestNode((p.u)->root); // get leftmost segment of p.u
        LineNode *lsc = (p.c)->getLowestNode((p.c)->root); // get leftmost segment of p.c

        if (lsu == NULL)
            ls_ = lsc;
        else if (lsc == NULL)
            ls_ = lsu;
        else
            // s_ : leftmost segment of p.u and p.c
            ls_ = (lsu->line < lsc->line ? lsu : lsc);

        s_ = ls_->line;

        // sl : left neighbour of s_
        LineNode *ln;
        ln = (T.getLeftNode(T.root, s_));
        if (ln != NULL)
        {
            sl = ln->line;
            findNewEvent(sl, s_, p);
        }

        LineNode *ls__;
        LineNode *rsu = (p.u)->getHighestNode((p.u)->root); // get rightmost segment of p.u
        LineNode *rsc = (p.c)->getHighestNode((p.c)->root); // get rightmost segment of p.c

        if (rsu == NULL)
            ls__ = rsc;
        else if (rsc == NULL)
            ls__ = rsu;
        else
            // s__ : rightmost segment of p.u and p.c
            ls__ = (rsu->line > rsc->line ? rsu : rsc);

        s__ = ls__->line;

        // sr : right neighbour of s__
        LineNode *rn;
        rn = (T.getRightNode(T.root, s__));
        if (rn != NULL)
        {
            sr = rn->line;
            findNewEvent(sr, s__, p);
        }
    }
}

void dfs(LineNode *curNode, bool add)
{
    if (curNode == NULL)
        return;

    dfs(curNode->left, add);
    dfs(curNode->right, add);
    if (!add)
        T.root = T.deleteNode(T.root, curNode->line);
    else
        T.root = T.insertNode(T.root, curNode->line);
}

void findNewEvent(Line l1, Line l2, Point p)
{
    // do not include event points that are above the sweep line or to the left of p
    // they have already been handled
    if (detectedIntersection(l1, l2))
    {
        Point ip = calculateIntersection(l1, l2);
        // check if ip is to the left of p or above p
        // if not, add this point to the event queue
        Q.insertNode(Q.root, ip);

        // add all lines to C(p) if p is in the interior of the line
        if (l1.p1 != ip && l1.p2 != ip)
            ip.c->insertNode(ip.c->root, l1);

        if (l2.p1 != ip && l2.p2 != ip)
            ip.c->insertNode(ip.c->root, l2);
    }
}

bool detectedIntersection(Line l1, Line l2)
{
    Point p1 = l1.p1, q1 = l1.p2;
    Point p2 = l2.p1, q2 = l2.p2;

    int o1 = orientation(p1, q1, q2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1))
        return true;
    if (o2 == 0 && onSegment(p1, q2, q1))
        return true;
    if (o3 == 0 && onSegment(p2, p1, q2))
        return true;
    if (o4 == 0 && onSegment(p2, q1, q2))
        return true;

    return false;
}

Point calculateIntersection(Line l1, Line l2)
{
    Point p;
    float m1 = (l1.p2.y - l1.p1.y) / (l1.p2.x - l1.p1.x);
    float m2 = (l2.p2.y - l2.p1.y) / (l2.p2.x - l2.p1.x);

    float c1 = l1.p1.y - m1 * l1.p1.x;
    float c2 = l2.p1.y - m2 * l2.p1.x;

    p.x = (c2 - c1) / (m1 - m2);
    p.y = p.x * m1 + c1;

    return p;
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val < EPSILON)
        return 0; // colinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool onSegment(Point p, Point q, Point r)
{
    bool c1 = q.x < max(p.x, r.x);
    bool c2 = isEqual(q.x, max(p.x, r.x));
    bool c3 = q.x > min(p.x, r.x);
    bool c4 = isEqual(q.x, min(p.x, r.x));
    bool c5 = q.y < max(p.y, r.y);
    bool c6 = isEqual(q.y, max(p.y, r.y));
    bool c7 = q.y > min(p.y, r.y);
    bool c8 = isEqual(q.y, min(p.y, r.y));

    if ((c2 || c1) && (c4 || c3) && (c6 || c5) && (c8 || c7))
        return true;

    // if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    // return true;

    return false;
}