/**
 * @file BinaryTreeDriver.cpp
 * @brief tests the implementation of the threaded Binary Tree class
 * @author Jonathan Chu/Elijah Shaw
 */

#include "BinaryNodeTree.h"
#include <iostream>

using namespace std;

/**
 * @pre a Threaded BST of int exists
 * @post Threaded BST is populated with all entries from first to last int
 * params
 * @param int
 * @param int
 * @param BinaryNodeTree<int> reference
 */
void buildIntTree(int first, int last, BinaryNodeTree<int> &treeToBuild) {
  // if we're at bottom in certain cases
  if (first == last) {
    treeToBuild.add(first);
    return;
  }
  int midpoint;
  midpoint = (last + first) / 2;
  // if there's still new midpoints to find
  if (midpoint != first && midpoint != last) {
    treeToBuild.add(midpoint);
    if (midpoint - 1 == first && midpoint + 1 == last) {
      if (first == 1) {
        buildIntTree(first, midpoint - 1, treeToBuild);
        buildIntTree(midpoint + 1, last, treeToBuild);
      } else {
        buildIntTree(midpoint + 1, last, treeToBuild);
        buildIntTree(first, midpoint - 1, treeToBuild);
      }
    } else {
      buildIntTree(first, midpoint - 1, treeToBuild);
      buildIntTree(midpoint + 1, last, treeToBuild);
    }
  } else if (midpoint == first && midpoint != last) {
    // if we're on the left side, add in descending order
    if (first == 1) {
      treeToBuild.add(last);

      treeToBuild.add(first);

      // if we're on the right side, add in ascending order
    } else {
      treeToBuild.add(first);

      treeToBuild.add(last);
    }
  }
}

// runs the testing program
int main() {
  int n;
  cout << "Enter an integer n to create TBST of n nodes:" << endl;
  cin >> n;
  // stops user from entering something that breaks client
  if (n <= 0) {
    cout << "No negatives or 0." << endl;
    return 0;
  }
  BinaryNodeTree<int> *testTree2 = new BinaryNodeTree<int>();
  buildIntTree(1, n, *testTree2);
  BinaryNodeTree<int> *testTree = new BinaryNodeTree<int>(*testTree2);
  cout << "Printing Inorder Traversal of User-Generated TBST:" << endl;
  // loop to delete even numbers
  if (n >= 2) {
    for (int i = 2; i <= n; i = i + 2) {
      testTree->remove(i);
    }
    cout << "Removed all even numbers from copy tree" << endl;
  } else {
    cout << "No even numbers in copy tree to begin with" << endl;
  }
  // prints out both trees after removing even numbers from the copy tree
  cout << "[Original Tree]" << endl;
  testTree2->inorder();
  cout << endl;
  cout << "[Copy Tree]" << endl;
  testTree->inorder();
  cout << endl;
  // frees all memory
  delete testTree;
  delete testTree2;
  return 0;
}