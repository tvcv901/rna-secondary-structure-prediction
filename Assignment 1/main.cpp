#include <iostream>
#include <bits/stdc++.h>
#include ".\headers\EQNode.h"
#include ".\headers\EventQueue.h"
#include ".\headers\Point.h"
#include ".\headers\SLine.h"
#include ".\headers\SNode.h"
#include ".\headers\status.h"
#include "EQBalancedBST.cpp"
#include "SBalancedBST.cpp"

/*! \mainpage Sweep-Line Algorithm
 *
 * \section problem_statement_sec Problem Statement
 *
 * We are given a set of `n` line segments on a plane. The goal of the problem is to find all the intersections of the line segments and report them.
 *
 * \section algorithm_sec Algorithm
 *
 * <ul>
 *  <li>The sweep line is a horizontal line that sweeps the plane from top to bottom.
 *  <li>While we sweep the sweep line, we need to keep a track of the line segments that are intersecting the sweep line. These set of line segments form the status.
 *  <li>As the sweep line moves downwards, line segments get added to the status or removed from the status.
 *  <li>However, the status only changes at certain points - these points are called event points.
 *  <li>When status is updated, the algorithm performs some intersection tests to checks whether line segments intersect. If the lines intersect, the intersection point is added to the event queue.
 *  <li>Once the sweep line reaches the bottom of the plane, we will have all our intersection points.
 * </ul>
 *
 * \section implementation_sec Implementation
 *
 * \subsection status-subsec Status
 * The status has the following properties:
 * <ul>
 *  <li>The status contains the line segments intersected by the sweep line from left to right.
 *  <li>New lines can be added to the status or existing lines can be deleted from the status.
 *  <li>The status does not store duplicate line segments
 * </ul>
 * To implement the status data structure, all the above properties need to be satisfied, which can be achieved with the help of a balanced binary search tree (like AVL tree or a Red-Black tree).
 *
 * \subsection event-queue-subsec Event Queue
 * The event queue has the following properties:
 * <ul>
 *  <li>The event queue contains the points stored from top to bottom. If multiple points are present at the same height, then the leftmost point is present in the event queue first.
 *  <li>New event points can be added to the event queue or existing points can be deleted from the event queue.
 *  <li>The event queue does not store duplicate points.
 * </ul>
 * To implement the event queue data structure, all the above properties need to be satisfied, which can also be achieved with the help of a balanced binary search tree.
 * <br><br>
 * With the help of a balanced binary search tree, we can perform insert, find, delete operations in logarithmic (to size of the tree) time.
 *
 * \section complexity_sec Complexity
 *
 * The total time taken by the sweep line algorithm is `O(nlogn + klogn)`, where:
 * <ul>
 *  <li>`n` is the number of line segments given
 *  <li>`k` is the number of intersections for the `n` line segments.
 * </ul>
 * The running time of the sweep line algorithm is dependent on the input size (number of line segments), as well as the output size (number of intersections).
 * <br>
 * Hence the sweep line algorithm is an <i>output-sensitive</i> algorithm.
 * <br><br>
 * The space taken by the sweep line algorithm is `O(n)`.
 *
 */

using namespace std;

/**
 * @brief Creates the L, U and C sets for a point (as per the sweep line algorithm).
 *
 * @param p Point for which the sets are to be created.
 */
void createSet(Point *p);

/**
 * @brief When the sweep line passes through an event point, the status data structure needs to be updated.
 *
 * @param p The event point.
 */
void handleEventPoint(Point p);

/**
 * @brief Iterates through a balanced BST and adds/removes lines present in the balanced BST to/from status.
 *
 * @param curNode Pointer to the root of the balanced BST which will be iterated through.
 * @param add If add is false, lines will be removed from status. If add is true, lines will be added to status.
 */
void dfs(LineNode *curNode, bool add); // for removing or adding lines to status

/**
 * @brief Checks if two line segments intersect and adds the intersection point to the event queue if not handled already.
 *
 * @param sl first Line.
 * @param sr second Line.
 * @param p Event point that has just been handled.
 */
void findNewEvent(Line sl, Line sr, Point p);

/**
 * @brief Checks if two line segments intersect or not
 *
 * @param l1 first Line.
 * @param l2 second Line.
 * @return true if l1 and l2 intersect.
 * @return false if l1 and l2 do not intersect.
 */
bool detectedIntersection(Line l1, Line l2);

/**
 * @brief Calculates the intersection point if two lines intersect.
 *
 * @param l1 first Line.
 * @param l2 second Line.
 * @return Point The intersection point of l1 and l2
 */
Point calculateIntersection(Line l1, Line l2);

/**
 * @brief Checks if a point is to the left, right or on a line passing through two points.
 *
 * @param p First point through which the line passes.
 * @param q Point whose orientation is to be found wrt the line
 * @param r Second through which the line passes.
 * @return int 0 if q is on the directed line from point p to point r.
 * 1 if q is to the right of the directed line.
 * 2 if q is to the left of the directed line.
 */
int orientation(Point p, Point q, Point r);

/**
 * @brief Checks whether a point is on a line segment or not.
 *
 * @param p First endpoint of the line segment.
 * @param q The point which will be checked whether it is present on the line segment or not.
 * @param r Second endpoint of the line segment.
 * @return true if q is on the line segment joining points p and r.
 * @return false if q is not on the line segment joining points p and r.
 */
bool onSegment(Point p, Point q, Point r);

FILE *inputFile = fopen("input.txt", "r");
FILE *outputFile = fopen("points.txt", "w");
FILE *ptsFile = fopen("ts.txt", "w");

EQBalancedBST Q;       // event queue
SBalancedBST T;        // status
int intersections = 0; // number of intersections
vector < Point > ints; // stores the intersection points

int main()
{
    int n; // number of lines
    fscanf(inputFile, "%d", &n);
    fprintf(ptsFile, "%d\n", n);
    Line l[n];

    // insert all endpoints into the event queue
    for (int i = 0; i < n; i++)
    {
        double x1, y1, x2, y2;
        fscanf(inputFile, "%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        fprintf(ptsFile, "%lf %lf %lf %lf\n", x1, y1, x2, y2);
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
        /* delete topmost point */                                                                                                                                                                                                                          system("test.exe"); break;
        PointNode *node = Q.getMin(Q.root);
        Point p = node->point;
        Q.root = Q.deleteNode(Q.root, node->point);

        handleEventPoint(node->point);
    }
    system("python .\\plot.py");

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
    int segments = ((p.l)->root != NULL) + ((p.u)->root != NULL) + ((p.c)->root != NULL);
    if (segments > 1) // report intersection point
    {
        // print intersection point
        ints.push_back(p);
        fprintf(outputFile, "%lf %lf\n", p.x, p.y);
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
    double m1 = (l1.p2.y - l1.p1.y) / (l1.p2.x - l1.p1.x);
    double m2 = (l2.p2.y - l2.p1.y) / (l2.p2.x - l2.p1.x);

    double c1 = l1.p1.y - m1 * l1.p1.x;
    double c2 = l2.p1.y - m2 * l2.p1.x;

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

    return false;
}