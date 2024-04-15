/// Alexander P. Weight
/// Professor Jason Christian
/// CSIS215: Algorithms and Data Structures
/// April 15, 2024

#include <iostream>
#include "BST.h"

int main() {

	//Here where all the tests begin: I think they're pretty self-explanatory
	//P.S the macros.h file contains sayl definition

	sayl("Alexander Weight -- CSIS 215 Programming Assignment 2 -- Double Threaded Binary Tree\n");
	sayl("Initializing BST constructor");
	BST<int, string> myBST(77, "seventy-seven"); //The constructor was optional, I just did it for fun
	sayl("Inserting nodes to BST");
	myBST.insert(70, "seventy");
	myBST.insert(75, "seventy-five");
	myBST.insert(66, "sixty-six");
	myBST.insert(79, "seventy-nine");
	myBST.insert(68, "sixty-eight");
	myBST.insert(67, "sixty-seven");
	myBST.insert(69, "sixty-nine");
	myBST.insert(90, "ninety");
	myBST.insert(85, "eighty-five");
	myBST.insert(83, "eighty-three");
	myBST.insert(87, "eighty-seven");
	myBST.insert(65, "sixty-five");
	sayl("Printing tree...\n");
	myBST.print();
	sayl("\nTree finished");
	sayl("Testing printing in order without recurssion...\n")
	myBST.printInOrder();
	sayl("\nPrint in order finished, now printing reversed...\n");
	myBST.printReverse();

	return 0;
}