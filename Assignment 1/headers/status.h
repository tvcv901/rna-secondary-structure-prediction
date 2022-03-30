#ifndef SBALANCED_BST_H
#define SBALANCED_BST_H

#include <iostream>
#include "Point.h"
#include "SLine.h"
#include "SNode.h"

using namespace std;

/**
 * @brief SBalancedBST is the implementation of the Status data structure using AVL Tree.
 *
 */
class SBalancedBST
{
public:
    /**
     * @brief Get the Balance Factor of a node.
     *
     * @param curNode Node for which balance factor is to be calculated.
     * @return int The balance factor of curNode.
     */
    int getBalanceFactor(LineNode *curNode);

    /**
     * @brief Get the Height of a node.
     *
     * @param curNode Node for which height is to be calculated.
     * @return int The height of curNode.
     */
    int getHeight(LineNode *curNode);

    /**
     * @brief Create a Point object
     *
     * @param x The x-coordinate of the point to be created.
     * @param y The y-coordinate of the point to be created.
     * @return Point The point with coordinates (x, y).
     */
    Point createPoint(float x, float y);

    /**
     * @brief Create a Line object.
     *
     * @param x1 x-coordinate of one endpoint of the line.
     * @param y1 y-coordinate of one endpoint of the line.
     * @param x2 x-coordinate of second endpoint of the line.
     * @param y2 y-coordinate of second endpoint of the line.
     * @param lineNo index of the line.
     * @return Line The Line with endpoints (x1, y1) and (x2, y2).
     */
    Line createLine(float x1, float y1, float x2, float y2, int lineNo);

    /**
     * @brief Create a Node object.
     *
     * @param l The Line object for which a LineNode is to be created.
     * @return LineNode* The pointer to the LineNode object created.
     */
    LineNode *createNode(Line l);

    /**
     * @brief Left rotate operation can be used for balancing the BST.
     *
     * @param curNode The LineNode on which the left rotate operation is to be performed.
     * @return LineNode* The root of the subtree after performing the left rotate operation.
     */
    LineNode *leftRotate(LineNode *curNode);

    /**
     * @brief Right rotate operation can be used for balancing the BST.
     *
     * @param curNode The LineNode on which the right rotate operation is to be performed.
     * @return LineNode* The root of the subtree after performing the right rotate operation.
     */
    LineNode *rightRotate(LineNode *curNode);

    /**
     * @brief Get the Lowest LineNode in a subtree rooted at a particular node.
     *
     * @param curNode The root of the subtree for which the lowest node is to be found.
     * @return LineNode* The lowest node of the subtree rooted at curNode.
     */
    LineNode *getLowestNode(LineNode *curNode);

    /**
     * @brief Get the Highest LineNode in a subtree rooted at a particular node.
     *
     * @param curNode The root of the subtree for which the highest node is to be found.
     * @return LineNode* The highest node of the subtree rooted at curNode.
     */
    LineNode *getHighestNode(LineNode *curNode);

    /**
     * @brief Get the LineNode which is the predecessor of a node.
     *
     * @param curNode Node for which predecessor is required.
     * @param l The line segment of the node.
     * @return LineNode* The predecessor of curNode.
     */
    LineNode *getLeftNode(LineNode *curNode, Line l);

    /**
     * @brief Get the LineNode which is the successor of a node.
     *
     * @param curNode Node for which successor is required.
     * @param l The line segment of the node.
     * @return LineNode* The successor of curNode.
     */
    LineNode *getRightNode(LineNode *curNode, Line l);

    /**
     * @brief Pointer to the root of the balanced BST.
     *
     */
    LineNode *root;

    /**
     * @brief Inserts a new node into the balanced BST rooted at a node with the given line.
     *
     * @param curNode The line is inserted into the subtree rooted at this node.
     * @param l The line to the inserted.
     * @return LineNode* The new root after inserting l into the subtree rooted at curNode.
     */
    LineNode *insertNode(LineNode *curNode, Line l);

    /**
     * @brief Deletes a line from the balanced BST rooted at a node.
     *
     * @param curNode The line is deleted in the subtree rooted at this node, if it exists.
     * @param l The line to be deleted.
     * @return LineNode* The new root after deleting l from the subtree rooted at curNode, if it exists.
     */
    LineNode *deleteNode(LineNode *curNode, Line l);

    /**
     * @brief Prints the preorder traversal of the points in the subtree rooted at a node.
     *
     * @param curNode Preorder traversal is performed at this node.
     */
    void preorder(LineNode *curNode);

    /**
     * @brief Prints the inorder traversal of the points in the subtree rooted at a node.
     *
     * @param curNode Inorder traversal is performed at this node.
     */
    void inorder(LineNode *curNode);

    /**
     * @brief Prints the postorder traversal of the points in the subtree rooted at a node.
     *
     * @param curNode Postorder traversal is performed at this node.
     */
    void postorder(LineNode *curNode);

    /**
     * @brief Prints all the traversals - inorder, preorder and postorder of the tree rooted at a node.
     *
     * @param curNode Print the traversals rooted at this node.
     */
    void printTraversals(LineNode *curNode);
};

#endif