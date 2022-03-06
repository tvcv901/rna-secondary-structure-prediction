#include <iostream>

using namespace std;

struct Point {
    int x;
    int y;

    inline void operator = (const Point a) {
        this -> x = a.x;
        this -> y = a.y;
    }
};

inline bool operator == (const Point a, const Point b) {
    return (a.x == b.x && a.y == b.y);
}

inline bool operator != (const Point a, const Point b) {
    return (a.x != b.x || a.y != b.y);
}

inline bool operator > (const Point a, const Point b) {
    if (a.y == b.y) return a.x > b.x;
    return a.y < b.y;
}

inline bool operator >= (const Point a, const Point b) {
    if (a.y == b.y) return a.x >= b.x;
    return a.y < b.y;
}

inline bool operator < (const Point a, const Point b) {
    if (a.y == b.y) return a.x < b.x;
    return a.y > b.y;
}

inline bool operator <= (const Point a, const Point b) {
    if (a.y == b.y) return a.x <= b.x;
    return a.y > b.y;
}

ostream &operator << (ostream &output, const Point p) {
    output << "( " << p.x << ", " << p.y << " )\n";
    return output;
}

struct Node {
    Point point;
    Node* left;
    Node* right;
    int height;
};

class BalancedBST {
private:
    int getBalanceFactor(Node* curNode);
    int getHeight(Node* curNode);
    Node* createNode(Point p);
    Node* leftRotate(Node* curNode);
    Node* rightRotate(Node* curNode);
    Node* getMin(Node* curNode);
    void printInorderTraversal(Node* curNode);
    void printPreorderTraversal(Node* curNode);
    void printPostorderTraversal(Node* curNode);
public:
    Node* root;
    Node* insertNode(Node* curNode, Point p);
    Node* findNode(Node* curNode, Point p);
    Node* deleteNode(Node* curNode, Point p);
    void printTraversals(Node* curNode);
};

int main()
{

    return 0;
}

int BalancedBST::getBalanceFactor(Node* curNode) {
    if (curNode == NULL)
        return 0;

    Node* leftNode = curNode -> left;
    Node* rightNode = curNode -> right;
    return (getHeight(leftNode) - getHeight(rightNode));
}

int BalancedBST::getHeight(Node* curNode) {
    if (curNode == NULL)
        return 0;

    return curNode -> height;
}

Node* BalancedBST::createNode(Point p) {
    Node* node = new Node;
    node -> point = p;
    node -> height = 1;
    return node;
}

Node* BalancedBST::leftRotate(Node* curNode) {
    Node* x = curNode;
    Node* y = x -> right;
    Node* b = y -> left;

    y -> left = x;
    x -> right = b;

    x -> height = max(getHeight(x -> left), getHeight(x -> right)) + 1;
    y -> height = max(getHeight(y -> left), getHeight(y -> right)) + 1;

    return y;
}

Node* BalancedBST::rightRotate(Node* curNode) {
    Node* y = curNode;
    Node* x = y -> left;
    Node* b = x -> right;

    x -> right = y;
    y -> left = b;

    y -> height = max(getHeight(y -> left), getHeight(y -> right)) + 1;
    x -> height = max(getHeight(x -> left), getHeight(x -> right)) + 1;

    return x;
}

Node* BalancedBST::getMin(Node* curNode) {
    Node* minNode = curNode;
    while (minNode -> left != NULL)
        minNode = minNode -> left;

    return minNode;
}

void BalancedBST::printInorderTraversal(Node* curNode) {
    if (curNode == NULL)
        return;

    printInorderTraversal(curNode -> left);
    cout << (curNode -> point).x << " " << (curNode -> point).y << '\n';
    printInorderTraversal(curNode -> right);
}

void BalancedBST::printPreorderTraversal(Node* curNode) {
    if (curNode == NULL)
        return;

    cout << (curNode -> point).x << " " << (curNode -> point).y << '\n';
    printPreorderTraversal(curNode -> left);
    printPreorderTraversal(curNode -> right);
}

void BalancedBST::printPostorderTraversal(Node* curNode) {
    if (curNode == NULL)
        return;

    printPostorderTraversal(curNode -> left);
    printPostorderTraversal(curNode -> right);
    cout << (curNode -> point).x << " " << (curNode -> point).y << '\n';
}

Node* BalancedBST::insertNode(Node* curNode, Point p) {
    if (curNode == NULL) { // works
        Node* newNode = createNode(p);
        return newNode;
    }

    Node* leftNode = curNode -> left;
    Node* rightNode = curNode -> right;

    if (p < curNode -> point) 
        curNode -> left = insertNode(leftNode, p);
    else if (p > curNode -> point) 
        curNode -> right = insertNode(rightNode, p);
    else return curNode;

    leftNode = curNode -> left;
    rightNode = curNode -> right;

    curNode -> height = 1 + max(getHeight(leftNode), getHeight(rightNode));
    int balanceFactor = getBalanceFactor(curNode);

    // height of left subtree is greater than right subtree by more than 1
    if (balanceFactor > 1) {
        if (p < leftNode -> point)
            return rightRotate(curNode);
        else if (p > leftNode -> point) {
            curNode -> left = leftRotate(leftNode);
            return rightRotate(curNode);
        }
    }

    // height of right subtree is greater than left subtree by more than 1
    if (balanceFactor < -1) {
        if (p > rightNode -> point)
            return leftRotate(curNode);
        else if (p < rightNode -> point) {
            curNode -> right = rightRotate(rightNode);
            return leftRotate(curNode);
        }
    }

    return curNode;
}

Node* BalancedBST::findNode(Node* curNode, Point p) {
    if (curNode == NULL || curNode -> point == p)
        return curNode;

    if (p < curNode -> point)
        return findNode(curNode -> left, p);

    return findNode(curNode -> right, p);
}

Node* BalancedBST::deleteNode(Node* curNode, Point p) {
    if (curNode == NULL)
        return curNode;

    if (p < curNode -> point)
        curNode -> left = deleteNode(curNode -> left, p);
    else if (p > curNode -> point)
        curNode -> right = deleteNode(curNode -> right, p);
    else
    {
        if (curNode -> left != NULL && curNode -> right != NULL)
        {
            Node* nextLargest = getMin(curNode -> right);
            curNode -> point = nextLargest -> point;
            curNode -> right = deleteNode(curNode -> right, curNode -> point);
        }
        else if (curNode -> left == NULL && curNode -> right == NULL)
        {
            curNode = NULL;
            free(curNode);
        }
        else
        {
            // Note: you do not have to find next largest (or smallest) in this case
            // (since tree is balanced, the left or right node will replace the node to be deleted)
            Node* temp = curNode;
            if (curNode -> left != NULL)
            {
                curNode = curNode -> left;
                curNode -> left = temp;
                free(curNode);
            }
            else
            {
                curNode = curNode -> right;
                curNode -> right = temp;
                free(curNode);
            }
        }
    }

    if (curNode == NULL)
        return curNode;

    curNode -> height = 1 + max(getHeight(curNode -> left), getHeight(curNode -> right));
    int balanceFactor = getBalanceFactor(curNode);

    if (balanceFactor > 1)
    {
        if (getBalanceFactor(curNode -> left) >= 0)
            return rightRotate(curNode);
        else
        {
            curNode -> left = leftRotate(curNode -> left);
            return rightRotate(curNode);
        }

    }

    if (balanceFactor < -1)
    {
        if (getBalanceFactor(curNode -> right) <= 0)
            return leftRotate(curNode);
        else
        {
            curNode -> right = rightRotate(curNode -> right);
            return leftRotate(curNode);
        }
    }

    return curNode;
}

void BalancedBST::printTraversals(Node* curNode) {
    cout << "Inorder Traversal:\n";
    printInorderTraversal(curNode);

    cout << "\nPreorder Traversal:\n";
    printPreorderTraversal(curNode);

    cout << "\nPostorder Traversal:\n";
    printPostorderTraversal(curNode);
}
