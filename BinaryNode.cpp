/**
 * @file BinaryNode.cpp
 * @brief Implements the BinaryNode class to be used in creating a Binary Tree
 * @author Elijah Shaw/Jonathan Chu
 */

#include "BinaryNode.h"

/*
 * @pre no pre-condition
 * @post new BinaryNode<ItemType> exists
 * @param NULL
 */
template <class ItemType> BinaryNode<ItemType>::BinaryNode() {
  leftPtr = nullptr;
  rightPtr = nullptr;
  leftThread = 1;
  rightThread = 1;
}

/*
 * @pre ItemType object exists
 * @post new BinaryNode<ItemType> exists with that ItemType object stored in it
 * @param ItemType const reference
 */
template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem) {
  item = anItem;
  leftPtr = this;
  rightPtr = this;
  leftThread = 1;
  rightThread = 1;
}

/*
 * @pre ItemType object and 2 BinaryNode<ItemType> pointers exist
 * @post new BinaryNode<ItemType> exists with the ItemType object and pointers
 * stored in it
 * @param ItemType const reference
 * @param BinaryNode<ItemType> pointer
 * @param BinaryNode<ItemType> pointer
 */
template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem,
                                 BinaryNode<ItemType> *left,
                                 BinaryNode<ItemType> *right) {
  item = anItem;
  leftPtr = left;
  rightPtr = right;
}

template <class ItemType> BinaryNode<ItemType>::~BinaryNode() {}

/*
 * @pre BinaryNode<ItemType> and ItemType objects exist
 * @post BinaryNode<ItemType>'s item variable is changed
 * @param ItemType const reference
 */
template <class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType &anItem) {
  item = anItem;
}

/*
 * @pre BinaryNode<ItemType> object exists
 * @post nothing is changed
 * @param NULL
 * @return ItemType object (possibly NULL)
 */
template <class ItemType> ItemType BinaryNode<ItemType>::getItem() const {
  return item;
}

/*
 * @pre BinaryNode<ItemType> object exists
 * @post nothing is changed
 * @param NULL
 * @return BinaryNode<ItemType>* (possibly nullptr)
 */
template <class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getLeftPtr() const {
  return leftPtr;
}

/*
 * @pre BinaryNode<ItemType> object exists
 * @post nothing is changed
 * @param NULL
 * @return BinaryNode<ItemType>* (possibly nullptr)
 */
template <class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getRightPtr() const {
  return rightPtr;
}

/*
 * @pre BinaryNode<ItemType> object exists
 * @post BinaryNode<ItemType>'s left pointer variable is changed
 * @param BinaryNode<ItemType> pointer
 */
template <class ItemType>
void BinaryNode<ItemType>::setLeftPtr(BinaryNode<ItemType> *newLeftPtr) {
  leftPtr = newLeftPtr;
}

/*
 * @pre BinaryNode<ItemType> object exists
 * @post BinaryNode<ItemType>'s right pointer variable is changed
 * @param BinaryNode<ItemType> pointer
 */
template <class ItemType>
void BinaryNode<ItemType>::setRightPtr(BinaryNode<ItemType> *newRightPtr) {
  rightPtr = newRightPtr;
}

/*
 * @pre Left thread exists
 * @post Left thread variable is retrieved
 * @param NULL
 * @return boolean value of left thread
 */
template <class ItemType> bool BinaryNode<ItemType>::getLeftThread() const {
  return leftThread;
}

/*
 * @pre Right thread exists
 * @post Right thread variable is retrieved
 * @param NULL
 * @return boolean value of right thread
 */
template <class ItemType> bool BinaryNode<ItemType>::getRightThread() const {
  return rightThread;
}

/*
 * @pre Left thread exists
 * @post Left thread variable is changed
 * @param bool new value for left thread
 */
template <class ItemType>
void BinaryNode<ItemType>::setLeftThread(bool thread) {
  leftThread = thread;
}

/*
 * @pre Right thread exists
 * @post Right thread variable is changed
 * @param bool new value for right thread
 */
template <class ItemType>
void BinaryNode<ItemType>::setRightThread(bool thread) {
  rightThread = thread;
}