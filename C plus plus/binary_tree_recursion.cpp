#include <iostream>
#include <string>
//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using namespace std;


void pressAnyKeyToContinue() {
	printf("Press any key to continue\n");

	//Linux and Mac users with g++ don't need this
	//But everyone else will see this message.
#ifndef __GNUC__
	_getch();
#else
	int c;
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));
#endif

}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
		return false;
	}
}

template <typename T>
class binaryTreeNode {
public:
	T info;
	binaryTreeNode<T>* llink;
	binaryTreeNode<T>* rlink;

};

template <typename T>
class binaryTreeType {
public:
	binaryTreeType();
	void insert(const T& insertItem);
	void postOrder() const;
	int nodeCount();
	int leavesCount();
	int singleChildCount();
	int levelCount(const int& num);

private:
	void postOrder(binaryTreeNode<T> *p) const;
	int nodeCount(binaryTreeNode<T> *p);
	int leavesCount(binaryTreeNode<T> *p);
	int singleChildCount(binaryTreeNode<T> *p);
	int levelCount(const int& num, int currentlevel, binaryTreeNode<T> *p);

	binaryTreeNode<T> *root;
};

template <typename T>
binaryTreeType<T>::binaryTreeType() {
	root = NULL;
}

template <typename T>
void binaryTreeType<T>::insert(const T& insertItem) {
	binaryTreeNode<T> *newNode = new binaryTreeNode<T>();
	newNode->info = insertItem;
	newNode->llink = NULL;
	newNode->rlink = NULL;

	if (root == NULL) {
		root = newNode;
		return;
	}

	binaryTreeNode<T> *current = root;
	binaryTreeNode<T> *trailCurrent = NULL;


	while (current != NULL) {
		trailCurrent = current;
		if (current->info > insertItem) {
			current = current->llink;
		}
		else {
			current = current->rlink;
		}
	}

	//trailCurrent points to the last node in the branch where we can 
	//stick a new node onto
	if (trailCurrent->info > insertItem) {
		//stick it on the left
		trailCurrent->llink = newNode;
	}
	else {
		trailCurrent->rlink = newNode;
	}


}

template <typename T>
void binaryTreeType<T>::postOrder() const {
	//This just gets it started
	postOrder(root);
}

template <typename T>
void binaryTreeType<T>::postOrder(binaryTreeNode<T> *p) const {
	if (p != NULL) {
		postOrder(p->llink);
		postOrder(p->rlink);
		cout << p->info << " ";
	}
}

//nodeCount() returns the total count of items in the tree.
template <typename T>
int binaryTreeType<T>::nodeCount() {
	return nodeCount(root);
}

template <typename T>
int binaryTreeType<T>::nodeCount(binaryTreeNode<T> *p) {
	int count = 0;
	if (p == NULL) {
		return 0;
	}
	else {
		count++;
		count += nodeCount(p->llink);
		count += nodeCount(p->rlink);
	}
	return count;
}

//leavesCount() counts the total amount of nodes in the three that don't have children.
template <typename T>
int binaryTreeType<T>::leavesCount() {
	return leavesCount(root);
}

template <typename T>
int binaryTreeType<T>::leavesCount(binaryTreeNode<T> *p) {
	int count = 0;
	if (p == NULL) {
		return 0;
	}
	else {
		if (p->llink == NULL && p->rlink == NULL) {
			count++;
		}
		count += leavesCount(p->llink);
		count += leavesCount(p->rlink);
	}
	return count;
}

//singleChildCount() counts the total amount of nodes in the tree that have only one child.
template <typename T>
int binaryTreeType<T>::singleChildCount() {
	return singleChildCount(root);
}

template <typename T>
int binaryTreeType<T>::singleChildCount(binaryTreeNode<T> *p) {
	int count = 0;
	if (p == NULL) {
		return 0;
	}
	else {
		if ((p->llink != NULL && p->rlink == NULL) || (p->llink == NULL && p->rlink != NULL)) {
			count++;
		}
		count += singleChildCount(p->llink);
		count += singleChildCount(p->rlink);
	}
	return count;
}

//levelCount() counts the amount of nodes on that particular level on that tree(root level is level 1).
template <typename T>
int binaryTreeType<T>::levelCount(const int& num) {
	return levelCount(num, 1, root);
}

template <typename T>
int binaryTreeType<T>::levelCount(const int& num, int currentlevel, binaryTreeNode<T> *p) {

	int count = 0;
	if (p == NULL) {
		return 0;
	}
	else {
		if (num == currentlevel) {
			return 1;
		}
		currentlevel++;
		count += levelCount(num, currentlevel, p->llink);
		count += levelCount(num, currentlevel, p->rlink);
	}
	return count;
}


int main() {

	binaryTreeType<int> myTree;

	myTree.insert(37);
	myTree.insert(32);
	myTree.insert(73);
	myTree.insert(95);
	myTree.insert(42);
	myTree.insert(12);
	myTree.insert(00);
	myTree.insert(49);
	myTree.insert(98);
	myTree.insert(7);
	myTree.insert(27);
	myTree.insert(17);
	myTree.insert(47);
	myTree.insert(87);
	myTree.insert(77);
	myTree.insert(97);
	myTree.insert(67);
	myTree.insert(85);
	myTree.insert(15);
	myTree.insert(5);
	myTree.insert(35);
	myTree.insert(55);
	myTree.insert(65);
	myTree.insert(75);
	myTree.insert(25);
	myTree.insert(45);
	myTree.insert(3);
	myTree.insert(93);
	myTree.insert(83);
	myTree.insert(53);
	myTree.insert(63);
	myTree.insert(23);
	myTree.insert(13);
	myTree.insert(43);
	myTree.insert(33);

	myTree.postOrder();

	//***************************************************************
	//NOTE: Global variables are banned to solve these problems!
	//Data members which store accumulated counts are also not allowed.  
	// Your counting needs to be done within the methods.  
	//***************************************************************
	checkTest("Test #1, number of nodes", 35, myTree.nodeCount());
	checkTest("Test #2, number of leaves, (i.e. nodes with no children)", 11, myTree.leavesCount());
	checkTest("Test #3, number of nodes with one child", 14, myTree.singleChildCount());
	checkTest("Test #4, number of nodes on level 1 (the root level)", 1, myTree.levelCount(1));
	checkTest("Test #5, number of nodes on level 2", 2, myTree.levelCount(2));
	checkTest("Test #6, number of nodes on level 3", 4, myTree.levelCount(3));
	checkTest("Test #7, number of nodes on level 4", 6, myTree.levelCount(4));
	checkTest("Test #8, number of nodes on level 5", 7, myTree.levelCount(5));
	checkTest("Test #9, number of nodes on level 6", 7, myTree.levelCount(6));
	checkTest("Test #10, number of nodes on level 7", 7, myTree.levelCount(7));
	checkTest("Test #11, number of nodes on level 8", 1, myTree.levelCount(8));
	checkTest("Test #12, number of nodes on level 9", 0, myTree.levelCount(9));
	

	pressAnyKeyToContinue();
	return 0;
}