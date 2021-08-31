/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

/**
 * Private helper function for the public mirror function.
 * @param subRoot
 */
 template <typename T>
void BinaryTree<T>::mirror(Node*& subRoot)
{
  if (subRoot == NULL)
    return;

  // Flip left & right subtree
  mirror(subRoot->left);
  mirror(subRoot->right);

  // swap left & right subtree
  Node* nodeTemp = subRoot->left;
  subRoot->left = subRoot->right;
  subRoot->right = nodeTemp;
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    std::vector<Node *> v;
    Node* currentNode = root;
    Node* nextNode;
    Node* maxNode = NULL;

    while (!v.empty() || currentNode != NULL)
    {
      while (currentNode != NULL) {
        v.push_back(currentNode);
        currentNode = currentNode->left;
      }
      nextNode = v.back();
      if (maxNode != NULL && nextNode->elem < maxNode->elem)
        return false;
      maxNode = nextNode;
      v.pop_back();
      currentNode = nextNode->right;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursive(root);
}

/**
 * Private helper function for the public isOrderedRecursive function.
 * @param subRoot
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(const Node* subRoot) const
{
    if (subRoot == NULL)
        return true;

    // check if left chiled is ordered
    if (!isOrderedRecursive(subRoot->left))
        return false;
    // check if right chiled is ordered
    if (!isOrderedRecursive(subRoot->right))
        return false;

    // check if root value is greater than the largest in left child
    if (subRoot->left != NULL && subRoot->elem < findMax(subRoot->left))
        return false;
    // check if root value is smaller than the smallest in right child
    if (subRoot->right != NULL && subRoot->elem > findMin(subRoot->right))
        return false;

    return true;
}

template <typename T>
T BinaryTree<T>::findMax(const Node* subRoot) const
{
    T currentMax = subRoot->elem;
    if (subRoot->left!=NULL) {
        currentMax = std::max(currentMax, findMax(subRoot->left));
    }
    if (subRoot->right!=NULL) {
        currentMax = std::max(currentMax, findMax(subRoot->right));
    }
    return currentMax;
}

template <typename T>
T BinaryTree<T>::findMin(const Node* subRoot) const
{
    T currentMin = subRoot->elem;
    if (subRoot->left!=NULL) {
        currentMin = std::min(currentMin, findMin(subRoot->left));
    }
    if (subRoot->right!=NULL) {
        currentMin = std::min(currentMin, findMin(subRoot->right));
    }
    return currentMin;
}

// template <typename T>
// T BinaryTree<T>::getLargest(const Node* subRoot) const
// {
//
// }
