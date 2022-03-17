#include <iostream>

using namespace std;

struct Point
{
    int x;
    int y;
};

struct Line
{
    Point p1;
    Point p2;
};

struct Node
{
    Line l;
    struct Node *left;
    struct Node *right;
    int height;
};

inline bool operator==(const Line l1, const Line l2)
{
    return ((l1.p1.x == l2.p1.x) && (l1.p1.y == l2.p1.y) && (l1.p2.x == l2.p2.x) && (l1.p2.y == l2.p2.y));
}

inline bool operator!=(const Line l1, const Line l2)
{
    return !(l1 == l2);
}

inline bool operator<(const Line l1, const Line l2)
{
    return ((l1.p1.y > l2.p1.y) || ((l1.p1.y == l2.p1.y) && (l1.p1.x < l2.p1.x)));
}

inline bool operator>(const Line l1, const Line l2)
{
    return ((l1.p1.y < l2.p1.y) || ((l1.p1.y == l2.p1.y) && (l1.p1.x > l2.p1.x)));
}

ostream &operator<<(ostream &out, const Node *n)
{
    out << "((" << n->l.p1.x << "," << n->l.p1.y << "),(" << n->l.p2.x << "," << n->l.p2.y << ")," << n->height << ")) ";
    return out;
}

int getHeight(struct Node *r);
int getBalanceFactor(struct Node *r);
struct Node *rightRotate(struct Node *x);
struct Node *leftRotate(struct Node *x);

struct Node *insertNode(struct Node *r, Line x);
struct Node *lowestNode(struct Node *r);
struct Node *highestNode(struct Node *r);
struct Node *deleteNode(struct Node *r, Line x);
struct Node *above(struct Node *r, Line x);
struct Node *below(struct Node *r, Line x);

struct Point createPoint(int a, int b);
struct Line createLine(int a, int b, int c, int d);

void preorder(struct Node *r);
void inorder(struct Node *r);
void postorder(struct Node *r);

int main()
{
    struct Node *avl = NULL;
    struct Line l;
    struct Point p;
    int n;
    cout << "Enter the number of points: ";
    cin >> n;
    cout << "Enter each point in the format x1 y1 x2 y2\n";
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (y1 > y2)
            l = createLine(x1, y1, x2, y2);
        else
            l = createLine(x2, y2, x1, y1);
        avl = insertNode(avl, l);
    }
    cout << "\nInorder Traversal: ";
    inorder(avl);
    cout << "\nPreorder Traversal: ";
    preorder(avl);
    cout << "\nPostorder Traversal: ";
    postorder(avl);
}

int getHeight(struct Node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

struct Node *rightRotate(struct Node *x)
{
    struct Node *y = x->left;
    struct Node *z = y->right;
    y->right = x;
    x->left = z;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

int getBalanceFactor(struct Node *n)
{
    if (n == NULL)
        return 0;
    return (getHeight(n->left) - getHeight(n->right));
}

struct Node *insertNode(struct Node *n, Line x)
{
    if (n == NULL)
    {
        struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
        temp->l = x;
        temp->left = NULL;
        temp->right = NULL;
        temp->height = 1;
        return temp;
    }
    if (x < n->l)
        n->left = insertNode(n->left, x);
    else if (x > n->l)
        n->right = insertNode(n->right, x);
    else
        return n;
    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    int balance = getBalanceFactor(n);
    if (balance > 1)
    {
        if (x < (n->left)->l)
            return rightRotate(n);
        if (x > (n->left)->l)
        {
            n->left = leftRotate(n->left);
            return rightRotate(n);
        }
    }
    if (balance < -1)
    {
        if (x > (n->right)->l)
            return leftRotate(n);
        if (x < (n->right)->l)
        {
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }
    }
    return n;
}

struct Node *lowestNode(struct Node *n)
{
    struct Node *cur = n;
    while (cur->left != NULL)
        cur = cur->left;
    return cur;
}

struct Node *highestNode(struct Node *n)
{
    struct Node *cur = n;
    while (cur->right != NULL)
        cur = cur->right;
    return cur;
}

struct Node *above(struct Node *n, Line x)
{
    struct Node *pre = NULL;
    struct Node *cur = n;
    while (cur->l != x)
    {
        if (x > cur->l)
        {
            if (pre == NULL)
                pre = cur;
            else
            {
                if (pre->l < cur->l)
                    pre = cur;
            }
        }
        if (x < cur->l)
            cur = cur->left;
        else
            cur = cur->right;
    }
    if (cur->left != NULL)
        return highestNode(cur->left);
    return pre;
}

struct Node *below(struct Node *n, Line x)
{
    struct Node *suc = NULL;
    struct Node *cur = n;
    while (cur->l != x)
    {
        if (x < cur->l)
        {
            if (suc == NULL)
                suc = cur;
            else
            {
                if (suc->l > cur->l)
                    suc = cur;
            }
        }
        if (x < cur->l)
            cur = cur->left;
        else
            cur = cur->right;
    }
    if (cur->right != NULL)
        return lowestNode(cur->right);
    return suc;
}

struct Node *deleteNode(struct Node *r, Line x)
{
    if (r == NULL)
        return r;
    if (x < r->l)
        r->left = deleteNode(r->left, x);
    else if (x > r->l)
        r->right = deleteNode(r->right, x);
    else
    {
        if ((r->left == NULL) || (r->right == NULL))
        {
            struct Node *temp;
            if (r->left != NULL)
                temp = r->left;
            else
                temp = r->right;
            if (temp == NULL)
            {
                temp = r;
                r = NULL;
            }
            else
                *r = *temp;
            free(temp);
        }
        else
        {
            struct Node *temp = lowestNode(r->right);
            r->l = temp->l;
            r->right = deleteNode(r->right, temp->l);
        }
    }
    if (r == NULL)
        return r;
    r->height = 1 + max(getHeight(r->left), getHeight(r->right));
    int balance = getBalanceFactor(r);
    if (balance > 1)
    {
        if (getBalanceFactor(r->left) >= 0)
            return rightRotate(r);
        else
        {
            r->left = leftRotate(r->left);
            return rightRotate(r);
        }
    }
    if (balance < -1)
    {
        if (getBalanceFactor(r->left) >= 0)
            return leftRotate(r);
        else
        {
            r->right = rightRotate(r->right);
            return leftRotate(r);
        }
    }
    return r;
}

struct Point createPoint(int a, int b)
{
    struct Point p;
    p.x = a;
    p.y = b;
    return p;
}

struct Line createLine(int a, int b, int c, int d)
{
    struct Line l;
    l.p1 = createPoint(a, b);
    l.p2 = createPoint(c, d);
    return l;
}

void preorder(struct Node *n)
{
    if (n != NULL)
    {
        cout << n;
        preorder(n->left);
        preorder(n->right);
    }
}

void inorder(struct Node *n)
{
    if (n != NULL)
    {
        inorder(n->left);
        cout << n;
        inorder(n->right);
    }
}

void postorder(struct Node *n)
{
    if (n == NULL)
        return;
    postorder(n->left);
    postorder(n->right);
    cout << n;
}
