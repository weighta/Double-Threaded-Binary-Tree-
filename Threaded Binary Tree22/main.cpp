#include <iostream>
#include "BST.h"


class Test {
private:
	int h = 0;
public:
	Test(int poop, int foo =NULL) {
		h = foo;
		int fart = 0;
	}
};

int main() {
	BST<int, string> myBST(77, "seventy-seven");
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
	myBST.preds();
	myBST.print();


	//for (int i = 0; i < myBST.size(); i++) {
	//	sayl(myBST.root[i].element());
	//}
	

	
	return 0;
}