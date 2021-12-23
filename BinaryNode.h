/**
 * @file BinaryNode.h
 * @brief header file for the BinaryNode class
 * @author Elijah Shaw/Jonathan Chu
 */

#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode {
  private:
    ItemType item;
    BinaryNode<ItemType>* leftPtr;
    BinaryNode<ItemType>* rightPtr;
    bool leftThread;
    bool rightThread; 
  public:
    BinaryNode();                                         // default constructor
    BinaryNode(const ItemType& anItem);                   // constructors
    BinaryNode(const ItemType& anItem,
              BinaryNode<ItemType>* left, 
              BinaryNode<ItemType>* right);
    ~BinaryNode();                                        // destructor
    void setItem(const ItemType& anItem);
    ItemType getItem() const;
    BinaryNode<ItemType>* getLeftPtr() const;
    BinaryNode<ItemType>* getRightPtr() const;
    void setLeftPtr(BinaryNode<ItemType>* newLeftPtr);
    void setRightPtr(BinaryNode<ItemType>* newRightPtr);
    bool getLeftThread() const;
    bool getRightThread() const;
    void setLeftThread(bool thread);
    void setRightThread(bool thread);
};

#include "BinaryNode.cpp"
#endif