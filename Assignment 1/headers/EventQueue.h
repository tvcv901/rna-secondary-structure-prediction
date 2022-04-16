#ifndef EQBALANCED_BST_H
#define EQBALANCED_BST_H

#include <iostream>
#include "Point.h"
#include "EQNode.h"

using namespace std;

/**
 * @brief EQBalancedBST is the implementation of the Event Queue data structure using AVL Tree.
 *
 */
class EQBalancedBST
{
public:
    /**
     * @brief Get the Balance Factor of a node.
     *
     * @param curNode Node for which balance factor is to be calculated.
     * @return int The balance factor of curNode.
     */
    int getBalanceFactor(PointNode *curNode);

    /**
     * @brief Get the Height of a node.
     *
     * @param curNode Node for which height is to be calculated.
     * @return int The height of curNode.
     */
    int getHeight(PointNode *curNode);

    /**
     * @brief Create a Point object
     *
     * @param x The x-coordinate of the point to be created.
     * @param y The y-coordinate of the point to be created.
     * @return Point The point with coordinates (x, y).
     */
    Point createPoint(double x, double y);

    /**
     * @brief Create a PointNode object.
     *
     * @param p The Point object for which a PointNode is to be created.
     * @return PointNode* The pointer to the PointNode object created.
     */
    PointNode *createNode(Point p);

    /**
     * @brief Left rotate operation can be used for balancing the BST.
     *
     * @param curNode The PointNode on which the left rotate operation is to be performed.
     * @return PointNode* The root of the subtree after performing the left rotate operation.
     */
    PointNode *leftRotate(PointNode *curNode);

    /**
     * @brief Right rotate operation can be used for balancing the BST.
     *
     * @param curNode The PointNode on which the right rotate operation is to be performed.
     * @return PointNode* The root of the subtree after performing the right rotate operation on curNode.
     */
    PointNode *rightRotate(PointNode *curNode);

    /**
     * @brief Get the lowest PointNode in a subtree rooted at a particular node.
     *
     * @param curNode The root of the subtree for which the lowest node is to be found.
     * @return PointNode* The lowest node of the subtree rooted at curNode.
     */
    PointNode *getMin(PointNode *curNode);

    /**
     * @brief Prints the inorder traversal of the points in the subtree rooted at a node.
     *
     * @param curNode Inorder traversal is performed at this node.
     */
    void printInorderTraversal(PointNode *curNode);

    /**
     * @brief Prints the preorder traversal of the points in the subtree rooted at a node.
     *
     * @param curNode Preorder traversal is performed at this node.
     */
    void printPreorderTraversal(PointNode *curNode);

    /**
     * @brief Prints the postorder traversal of the points in the subtree rooted at a node.
     *
     * @param curNode Postorder traversal is performed at this node.
     */
    void printPostorderTraversal(PointNode *curNode);

    /**
     * @brief Pointer to the root of the balanced BST.
     *
     */
    PointNode *root;

    /**
     * @brief Inserts a new node into the balanced BST rooted at a node with the given point.
     *
     * @param curNode The point is inserted into the subtree rooted at this node.
     * @param p The point to the inserted.
     * @return PointNode* The new root after inserting p into the subtree rooted at curNode.
     */
    PointNode *insertNode(PointNode *curNode, Point p);

    /**
     * @brief Searches for a point in the balanced BST rooted at a given node.
     *
     * @param curNode The point is searched in the subtree rooted at this node.
     * @param p The point to be searched.
     * @return PointNode* The node which contains the point p in the subtree rooted at curNode or a null pointer if p is not found.
     */
    PointNode *findNode(PointNode *curNode, Point p);

    /**
     * @brief Deletes a point from the balanced BST rooted at a node.
     *
     * @param curNode The point is deleted in the subtree rooted at this node, if it exists.
     * @param p The point to be deleted.
     * @return PointNode* The new root after deleting p from the subtree rooted at curNode, if it exists.
     */
    PointNode *deleteNode(PointNode *curNode, Point p);

    /**
     * @brief Prints all the traversals - inorder, preorder and postorder of the tree rooted at a node.
     *
     * @param curNode Print the traversals rooted at this node.
     */
    void printTraversals(PointNode *curNode);
};

#endif