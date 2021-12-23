Compiling Instructions:

To compile the project, simply compile only BinaryTreeDriver.cpp using "g++ BinaryTreeDriver.cpp".

Running the program:

When the program runs, the user will be asked for numerical input (n) in the console. From there, the program will generate a Threaded BST from 1 to n.
The program will then remove all nodes containing odd values in the Threaded BST. Upon completion, the program will traverse (inorder) the Threaded BST and print values.
Once the output is printed, the memory of the tree is deleted and associated destructors are called.

Testing:

We tested our program by running valgrind to check for memory leaks, especially in regards to additional or missing nodes.
We checked the output by traversing through the BST and checking if there were any even values that still remained post removal.
We used different sizes of input to verify that the program works for various scales of input.