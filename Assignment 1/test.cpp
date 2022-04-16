#include <bits/stdc++.h>

using namespace std;

#define EPSILON 1e-9

struct Point
{
    double x;
    double y;
};

struct Line
{
    Point p1;
    Point p2;
    int lineNo;
};

bool detectedIntersection(Line l1, Line l2);
Point calculateIntersection(Line l1, Line l2);
int orientation(Point p, Point q, Point r);
bool onSegment(Point p, Point q, Point r);
bool isEqual(double a, double b);

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("points.txt", "w", stdout);

    int n;
    cin >> n;
    cout << n << '\n';
    Line l[n];
    for (int i = 0; i < n; i++)
    {
        cin >> l[i].p1.x >> l[i].p1.y >> l[i].p2.x >> l[i].p2.y;
        l[i].lineNo = i;
        cout << fixed << setprecision(12) << l[i].p1.x << " " << l[i].p1.y << " " << l[i].p2.x << " " << l[i].p2.y << '\n';
    }

    int intersections = 0;
    vector<Point> ints;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (detectedIntersection(l[i], l[j]))
            {
                Point p = calculateIntersection(l[i], l[j]);
                bool insert = true;
                for (auto x : ints)
                {
                    if (isEqual(p.x, x.x) && isEqual(p.y, x.y))
                        insert = false;
                }
                if (insert)
                {
                    // cout << "Lines " << i << " and " << j << "\n";
                    // cout << fixed << setprecision(12) << "Intersection Point: (" << p.x << ", " << p.y << ")\n";
                    intersections++;
                    ints.push_back(p);
                }
                // cout << '\n';
            }
        }
    }

    cout << intersections << '\n';
    for (auto p : ints)
    {
        cout << fixed << setprecision(12) << p.x << " " << p.y << '\n';
    }

    return 0;
}

bool detectedIntersection(Line l1, Line l2)
{
    Point p1 = l1.p1, q1 = l1.p2;
    Point p2 = l2.p1, q2 = l2.p2;

    int o1 = orientation(p1, p2, q1);
    int o2 = orientation(p1, q2, q1);
    int o3 = orientation(p2, p1, q2);
    int o4 = orientation(p2, q1, q2);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1))
    {
        return true;
    }

    if (o2 == 0 && onSegment(p1, q2, q1))
    {
        return true;
    }

    if (o3 == 0 && onSegment(p2, p1, q2))
    {
        return true;
    }

    if (o4 == 0 && onSegment(p2, q1, q2))
    {
        return true;
    }

    return false;
}

Point calculateIntersection(Line l1, Line l2)
{
    Point p;
    double m1 = (l1.p2.y - l1.p1.y) / (l1.p2.x - l1.p1.x);
    double m2 = (l2.p2.y - l2.p1.y) / (l2.p2.x - l2.p1.x);
    double c1 = l1.p1.y - m1 * l1.p1.x;
    double c2 = l2.p1.y - m2 * l2.p1.x;

    if (!isEqual(l1.p1.x, l1.p2.x) && !isEqual(l2.p1.x, l2.p2.x))
    {
        if (isEqual(m1, m2))
        {
            if (isEqual(l1.p2.x, l2.p1.x) && isEqual(l1.p2.y, l2.p1.y))
                p.x = l1.p2.x, p.y = l1.p2.y;
            else if (isEqual(l1.p1.x, l2.p2.x) && isEqual(l1.p1.y, l2.p2.y))
                p.x = l1.p1.x, p.y = l2.p2.y;
        }
        else
        {
            p.x = (c2 - c1) / (m1 - m2);
            p.y = p.x * m1 + c1;
        }
    }
    else if (isEqual(l1.p1.x, l1.p2.x) && !isEqual(l2.p1.x, l2.p2.x))
    {
        p.x = l1.p1.x;
        p.y = p.x * m2 + c2;
    }
    else if (!isEqual(l1.p1.x, l1.p2.x) && isEqual(l2.p1.x, l2.p2.x))
    {
        p.x = l2.p1.x;
        p.y = p.x * m1 + c1;
    }
    else
    {
        // p.x = p.y = std::numeric_limits<double>::infinity();
        p.x = l1.p1.x;
        if (l2.p1.y >= l1.p2.y && l1.p2.y >= l2.p2.y)
            p.y = l1.p2.y;
        else if (l2.p1.y >= l1.p1.y && l1.p1.y >= l2.p2.y)
            p.y = l1.p1.y;
    }

    return p;
}

int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (isEqual(val, 0))
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

    bool res = (c2 || c1) && (c4 || c3) && (c6 || c5) && (c8 || c7);

    return res;

    // if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    // return true;
}

bool isEqual(double a, double b)
{
    return fabs(a - b) < EPSILON;
}