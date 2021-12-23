/**
 * @file BinaryNodeTree.h
 * @brief header file for the Threaded BST
 * @author Elijah Shaw/Jonathan Chu
 */
#ifndef _BINARY_NODE_TREE
#define _BINARY_NODE_TREE

#include "BinaryNode.h"


template<class ItemType>
class BinaryNodeTree {
  private:
    BinaryNode<ItemType>* rootPtr;
  protected:
    // remove value, replace with child
    void removeValue(const ItemType target, bool& success);

    // moves values up tree
    void moveValuesUpTree(BinaryNode<ItemType>* subTreePtr);

    BinaryNode<ItemType>* findInOrderPredecessor(const BinaryNode<ItemType>* targetPtr);

    // search for specific node (preorder traverse)
    BinaryNode<ItemType>* findNode(const ItemType& target) const;

    // copies tree root and points to copy
    BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* copyTreePtr);

  public:
    BinaryNodeTree();                                                   // default constructor
    BinaryNodeTree(const ItemType& rootItem);                           // constructors
    BinaryNodeTree(const ItemType& rootItem,
                   const BinaryNodeTree<ItemType>* leftTreePtr,
                   const BinaryNodeTree<ItemType>* rightTreePtr);
    BinaryNodeTree(const BinaryNodeTree<ItemType>& tree);               // copy constructor
    void copyBranch(BinaryNode<ItemType>* startNode);   
    ~BinaryNodeTree();                                                  // destructor
    void add(const ItemType& newData);
    bool remove(const ItemType& data);
    void inorder() const;
};

#include "BinaryNodeTree.cpp"
#endif