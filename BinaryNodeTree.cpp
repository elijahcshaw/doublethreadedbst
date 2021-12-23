/**
 * @file BinaryNodeTree.cpp
 * @brief implemementation of all functions of the Threaded BST
 * @author Jonathan Chu/Elijah Shaw
 */

#include "BinaryNodeTree.h"
#include <iostream>
using namespace std;

/**
 * @pre no pre-condition
 * @post new Threaded BST has been created (no actual entries yet)
 * @param NULL
 */
template <class ItemType> BinaryNodeTree<ItemType>::BinaryNodeTree() {
  rootPtr = new BinaryNode<ItemType>();
}

/**
 * @pre an ItemType object exists
 * @post new Threaded BST has been created (root object of ItemType)
 * @param ItemType const reference
 */
template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType &rootItem) {
  rootPtr = new BinaryNode<ItemType>(rootItem);
}

/**
 * @pre BinaryNode and two Threaded BSTs exist
 * @post one BinaryNode from a tree is deep-copied into a second tree
 * @param BinaryNode<ItemType> pointer
 */
template <class ItemType>
void BinaryNodeTree<ItemType>::copyBranch(BinaryNode<ItemType> *startNode) {
  add(startNode->getItem());
  if (startNode->getLeftThread() && startNode->getRightThread()) {
    return;
  } else if (startNode->getLeftThread()) {
    copyBranch(startNode->getRightPtr());
  } else if (startNode->getRightThread()) {
    copyBranch(startNode->getLeftPtr());
  } else {
    copyBranch(startNode->getLeftPtr());
    copyBranch(startNode->getRightPtr());
  }
}

/**
 * @pre a Threaded BST exists
 * @post a second Threaded BST exists that's a deep copy of the original
 * @param BinaryNodeTree<ItemType> const
 */
template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType> &tree) {
  // insert the root
  rootPtr = new BinaryNode<ItemType>();
  BinaryNode<ItemType> *root = tree.rootPtr;
  add(root->getItem());
  // if there's only one node in the other tree
  if (root->getLeftThread() && root->getRightThread()) {
    return;
    // if there's only something on right side
  } else if (root->getLeftThread()) {
    copyBranch(root->getRightPtr());
    // if there's only something on left side
  } else if (root->getRightThread()) {
    copyBranch(root->getLeftPtr());
    // if there's stuff on both
  } else {
    copyBranch(root->getLeftPtr());
    copyBranch(root->getRightPtr());
  }
}

/** destructor
 * @pre a Threaded BST exists
 * @post that Threaded BST no longer exists (memory is freed)
 * @param NULL
 */
template <class ItemType> BinaryNodeTree<ItemType>::~BinaryNodeTree() {
  if (rootPtr == nullptr) {
    return;
  }
  BinaryNode<ItemType> *n = rootPtr;
  BinaryNode<ItemType> *temp;
  // moves all the way to the left
  while (n->getLeftThread() == 0) {
    n = n->getLeftPtr();
  }
  // while we're not at the farthest right
  while (n->getRightPtr() != n) {
    if (n->getRightThread() == 0) {
      temp = n->getRightPtr();
      delete n;
      n = temp;
      // while there is no left thread
      while (n->getLeftThread() != 1) {
        n = n->getLeftPtr();
      }
    } else {
      temp = n->getRightPtr();
      delete n;
      n = temp;
    }
  }
  delete n;
}

/**
 * @pre a Threaded BST exists
 * @brief adds a new node into the Threaded BST
 * @post a new BinaryNode of ItemType is in the Threaded BST
 * @param ItemType const reference
 */
template <class ItemType>
void BinaryNodeTree<ItemType>::add(const ItemType &newData) {
  // if the root pointer does not contain any information
  if (rootPtr->getLeftPtr() == nullptr && rootPtr->getRightPtr() == nullptr) {
    rootPtr->setItem(newData);
    rootPtr->setLeftPtr(rootPtr);
    rootPtr->setRightPtr(rootPtr);
  } else {
    BinaryNode<ItemType> *current = rootPtr;
    BinaryNode<ItemType> *n = new BinaryNode<ItemType>(newData);
    bool foundPosition = false;
    // run until the right position in the BST is found
    while (!foundPosition) {
      // if the new item should go on the left
      if (newData < current->getItem()) {
        // if threaded somewhere (including itself)
        if (current->getLeftThread() == 1) {
          // if leftmost node
          if (current == current->getLeftPtr()) {
            current->setLeftPtr(n);
            current->setLeftThread(0);
            foundPosition = true;
          } else { // not the leftmost node, but on the left
            n->setLeftPtr(current->getLeftPtr());
            n->setLeftThread(1);
            current->setLeftPtr(n);
            current->setLeftThread(0);
            foundPosition = true;
          }
          n->setRightThread(1);
          n->setRightPtr(current);
        } else {
          // update current
          current = current->getLeftPtr();
        }
        // if the new item should go on the right
      } else {
        if (current->getRightThread() == 1) {
          // if rightmost node
          if (current == current->getRightPtr()) {
            current->setRightPtr(n);
            current->setRightThread(0);
            foundPosition = true;
          } else { // not the rightmost node, but on the right
            n->setRightPtr(current->getRightPtr());
            n->setRightThread(1);
            current->setRightPtr(n);
            current->setRightThread(0);
            foundPosition = true;
          }
          n->setLeftThread(1);
          n->setLeftPtr(current);
        } else {
          // update current
          current = current->getRightPtr();
        }
      }
    }
    // clean up memory used to add
    n = nullptr;
    delete n;
  }
}

/**
 * @pre a Threaded BST and an ItemType object exist
 * @post if Threaded BST contained that ItemType, that entry is no longer there
 * @param ItemType const reference
 * @return bool determines whether operation was successful
 */
template <class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType &data) {
  bool success;
  removeValue(data, success);
  return success;
}

/**
 * @pre a Threaded BST exists with entries
 * @brief removes a node containing specified value from Threaded BST
 * @post an entry is removed from that Threaded BST
 * @param BinaryNode<ItemType> pointer
 * @param ItemType const
 * @param bool reference whether operation was successful
 */
template <class ItemType>
void BinaryNodeTree<ItemType>::removeValue(const ItemType target,
                                           bool &success) {
  BinaryNode<ItemType> *node = findNode(target);
  if (node != nullptr) {
    success = true;
    moveValuesUpTree(node);
  } else {
    success = false;
  }
}

/**
 * @pre a Threaded BST exists with entries
 * @brief moves values up to replace specified node (prefers left first)
 * @post entries are adjusted after one is removed
 * @param BinaryNode<ItemType> pointer
 */
template <class ItemType>
void BinaryNodeTree<ItemType>::moveValuesUpTree(
    BinaryNode<ItemType> *subTreePtr) {
  // if the node is a leaf
  if (subTreePtr->getLeftThread() && subTreePtr->getRightThread()) {
    if (subTreePtr != rootPtr) {
      // look for parent node and replace associated pointers with threads
      BinaryNode<ItemType> *parentNode = subTreePtr->getLeftPtr();
      if (parentNode->getRightPtr() == subTreePtr) {
        // if the rightmost node, thread parent to itself
        if (subTreePtr->getRightPtr() != subTreePtr) {
          parentNode->setRightPtr(subTreePtr->getRightPtr());
        } else {
          parentNode->setRightPtr(parentNode);
        }
        parentNode->setRightThread(1);
        // clean up memory
        delete subTreePtr;
        subTreePtr = nullptr;
        return;
      }
      parentNode = subTreePtr->getRightPtr();
      // look for parent node (right side) and replace associated pointers with
      // threads
      if (parentNode->getLeftPtr() == subTreePtr) {
        // if the leftmost node, thread parent to itself
        if (subTreePtr->getLeftPtr() != subTreePtr) {
          parentNode->setLeftPtr(subTreePtr->getLeftPtr());
        } else {
          parentNode->setLeftPtr(parentNode);
        }
        parentNode->setLeftThread(1);
        // clean up memory
        delete subTreePtr;
        subTreePtr = nullptr;
        return;
      }
    } else { // single entry case (edge case, root pointer only)
      delete rootPtr;
      rootPtr = nullptr;
      return;
    }
    // if the node has two children, find the predecessor and replace the node
    // with the predecessor
  } else if (!subTreePtr->getLeftThread() && !subTreePtr->getRightThread()) {
    BinaryNode<ItemType> *replacementNode = findInOrderPredecessor(subTreePtr);
    subTreePtr->setItem(replacementNode->getItem());
    moveValuesUpTree(replacementNode);
    return;
  }
  // move values up the tree if it isn't a leaf
  // prefers left over right first
  if (subTreePtr->getLeftThread() == 0) {
    subTreePtr->setItem(subTreePtr->getLeftPtr()->getItem());
    moveValuesUpTree(subTreePtr->getLeftPtr());
  } else if (subTreePtr->getRightThread() == 0) {
    subTreePtr->setItem(subTreePtr->getRightPtr()->getItem());
    moveValuesUpTree(subTreePtr->getRightPtr());
  }
}

/**
 * @pre Threaded BST exists with entries
 * @brief helper method to find in order predecessor for removal process
 * @post nothing is changed
 * @param BinaryNode<ItemType> const pointer
 * @return BinaryNode<ItemType> pointer
 */
template <class ItemType>
BinaryNode<ItemType> *BinaryNodeTree<ItemType>::findInOrderPredecessor(
    const BinaryNode<ItemType> *targetPtr) {
  BinaryNode<ItemType> *searchNode;
  // since it is inorder, go left one node if possible
  if (targetPtr->getLeftThread() == 0) {
    searchNode = targetPtr->getLeftPtr();
    // start going as far right as possible to find predecessor
    while (searchNode->getRightPtr() != targetPtr) {
      searchNode = searchNode->getRightPtr();
    }
    return searchNode;
    // entry is leftmost node or doesn't have a predecessor
  } else {
    return targetPtr->getLeftPtr();
  }
}

/**
 * @pre a Threaded BST exists
 * @brief finds a specified node containing a target value and returns the
 * address
 * @post nothing is changed
 * @param BinaryNode<ItemType> pointer
 * @param ItemType const reference
 * @param bool
 * @return BinaryNode<ItemType> pointer
 */
template <class ItemType>
BinaryNode<ItemType> *
BinaryNodeTree<ItemType>::findNode(const ItemType &target) const {
  // if root doesn't exist
  if (rootPtr == nullptr) {
    return nullptr;
  }
  // if root contains the target
  if (rootPtr->getItem() == target) {
    return rootPtr;
  }
  BinaryNode<ItemType> *n = rootPtr;
  // moves all the way to the left
  while (n->getLeftThread() == 0) {
    n = n->getLeftPtr();
  }
  // while we're not at the farthest right, look through using inorder traversal
  while (n->getRightPtr() != n) {
    if (n->getItem() == target) {
      return n;
    }
    if (n->getRightThread() == 0) {
      n = n->getRightPtr();
      // while there is no left thread, go left (branch cases)
      while (n->getLeftThread() != 1) {
        n = n->getLeftPtr();
      }
    } else { // continue right
      n = n->getRightPtr();
    }
  } // if the rightmost node has the target value
  if (n->getItem() == target) {
    return n;
  }
  return nullptr;
}

/**
 * @pre a Threaded BST exists
 * @brief traverses the TBST using an inorder traversal method
 * @post nothing is changed
 * @param NULL
 */
template <class ItemType> void BinaryNodeTree<ItemType>::inorder() const {
  if (rootPtr == nullptr) {
    return;
  }
  BinaryNode<ItemType> *n = rootPtr;
  // moves all the way to the left
  while (n->getLeftThread() == 0) {
    n = n->getLeftPtr();
  }
  // while we're not at the farthest right
  while (n->getRightPtr() != n) {
    cout << " " << n->getItem();
    if (n->getRightThread() == 0) {
      n = n->getRightPtr();
      // while there is no left thread
      while (n->getLeftThread() != 1) {
        n = n->getLeftPtr();
      }
    } else {
      n = n->getRightPtr();
    }
  }
  cout << " " << n->getItem() << endl;
  return;
}
