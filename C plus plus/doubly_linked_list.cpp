#include <iostream> 
#include <string> 
#include <map> 
//To prevent those using g++ from trying to use a library 
//they don't have 
#ifndef __GNUC__ 
#include <conio.h> 
#else 
#include <cstdio> 
#endif 

#include <sstream> 

using namespace std;


bool checkTest(string testName, string whatItShouldBe, string whatItIs);
bool checkTest(string testName, int whatItShouldBe, int whatItIs);


//************************************************************************ 
//A class I designed to help keep track of how much memory you allocate 
//Do not modify, this is not part of your assignment, it just helps test it. 
//For this to work, a class needs to inherit off of this one.  
//Then this does the rest of the work, since it  
//overloads new, new[], delete, and delete[]. 
//************************************************************************ 
class manageMemory {
public:

	static std::size_t getTotalSize() {
		std::size_t total = 0;
		std::map<void *, std::size_t>::iterator iter;
		for (iter = mapOfAllocations.begin(); iter != mapOfAllocations.end(); ++iter) {
			total += iter->second;
		}
		return total;
	}

	//I overloaded the new and delete keywords so I could manually track allocated memory. 
	void* operator new(std::size_t x){
		void *ptr = ::operator new(x);
		mapOfAllocations[ptr] = x;
		return ptr;
	}
	void* operator new[](std::size_t x) {
		void *ptr = ::operator new[](x);
		mapOfAllocations[ptr] = x;
		return ptr;
	}
	void operator delete(void* x) {
		mapOfAllocations.erase(x);
		::operator delete(x);
	}
	void operator delete[](void* x) {
		mapOfAllocations.erase(x);
		::operator delete[](x);
	}
private:
	static std::map<void *, std::size_t> mapOfAllocations;
};
std::map<void *, std::size_t> manageMemory::mapOfAllocations;

//****************** 
//The node class 
//****************** 

template <typename T>
class Node {
public:
	T info;
	Node *forward;
	Node *backward;
};

//****************** 
//The linked list base class 
//This contains within it a class declaration for an iterator 
//****************** 
template <typename T>
class doublyLinkedList {
public:

	//public members of the doublyLinkedList class 
	doublyLinkedList();
	~doublyLinkedList();
	string getStringFromList();

	void insertFirst(const T&);
	void insertLast(const T&);

	void deleteAllOfOccurrence(const T& value); //For your assignment 
	void reverseList();  //For your assignment 
	T getAndDeleteLastSmallestValue();  //For your assignment, needs to handle try/catch 
	T& operator[](const int index);   //For your assignment 


protected:
	Node<T> *first;
	Node<T> *last;
	int count;
};


template <typename T>
doublyLinkedList<T>::doublyLinkedList() {
	first = NULL;
	last = NULL;
	count = 0;
}

template <typename T>
doublyLinkedList<T>::~doublyLinkedList() {
	Node<T> *temp;
	while (first != NULL) {
		temp = first;
		first = first->forward;
		delete temp;
	}
	last = NULL;
	count = 0;
}

template <typename T>
void doublyLinkedList<T>::insertFirst(const T& newItem)
{
	Node<T> *newNode;
	newNode = new Node<T>;
	newNode->backward = NULL;
	newNode->info = newItem;
	newNode->forward = first;

	if (first == NULL)
	{
		first = newNode;
		last = first;
	}
	else
	{
		first->backward = newNode;
		first = newNode;
	}
	count++;
}

template <typename T>
void doublyLinkedList<T>::insertLast(const T& newItem) {
	Node<T> *newNode;
	newNode = new Node<T>;
	newNode->forward = NULL;
	newNode->backward = last;
	newNode->info = newItem;

	if (first == NULL) {
		//Empty list 
		first = newNode;
		last = first;
	}
	else {
		last->forward = newNode;
		last = newNode;
	}
	count++;
}

template<typename T>
T& doublyLinkedList<T>::operator[](const int index){
	Node<T> *temp = first;
	int position = 0;

	while (position <= index) {
		if (position == index) {
			return temp->info;
		}
		else if (temp->forward != NULL) {
			temp = temp->forward;
			position++;
		}
	}
	return temp->info;
}


template<typename T>
void doublyLinkedList<T>::reverseList(){  //For your assignment 
	Node<T> *sweep = first; //node to traverse the list 
	Node<T> *temp = NULL; //node that will be used to swap pointers 
	int size = 1; //position in our list 

	while (size <= count) { //to loop through the list 
		temp = sweep; //make temp our node so that we can swap pointers 
		if (sweep->forward != NULL) { //if node isn't at end of list, move forward 
			sweep = sweep->forward; //move sweeping node forward so not to mess with the pointers 
		}
		temp->forward = temp->backward; //now we will swap the backwards and forwards pointers 
		temp->backward = sweep;
		size++;
	}
	last = first; //set the end of the list to what was first 
	first = sweep; //set the front of the list to where our sweep ended (the end of the first list) 
	return; //since return type was void, just return. 
}

/*I wrote the two following functions again so that I could understand how the assignment worked, my comments are included below*/
template<typename T>
T doublyLinkedList<T>::getAndDeleteLastSmallestValue(){  //For your assignment 
	Node<T> *temp = first; //node used to traverse 
	Node<T> *smallest = first; //node to hold smallest node 
	T returned; //our info will be stored in this variable 

	if (first == NULL) { //no nodes 
		throw 21;
	}
	if (first == last) { //one node 
		returned = temp->info; //save info so when we delete node, we'll still have the info 
		delete temp;
		first = NULL;
		last = NULL;
		count--;
		return returned;
	}
	while (temp != NULL) { //now loop through entire list finding the last smallest node 
		if (temp->info <= smallest->info) {
			smallest = temp;
			returned = smallest->info;
		}
		temp = temp->forward;
	}
	if (smallest == first) { //if found node is at the front, delete it 
		smallest->forward->backward = NULL;
		first = smallest->forward;
		delete smallest;
		count--;
		return returned;
	}
	else if (smallest == last) { //if found node is at the back, delete it 
		smallest->backward->forward = NULL;
		last = smallest->backward;
		delete smallest;
		count--;
		return returned;
	}
	else {
		smallest->backward->forward = smallest->forward; //elsewhere in the list, and delete it 
		smallest->forward->backward = smallest->backward;
		delete smallest;
		count--;
		return returned;
	}

}

template<typename T>
void doublyLinkedList<T>::deleteAllOfOccurrence(const T& value){  //For your assignment 
	//Remember, you are only allowed to loop once over the list.   
	Node<T> *temp = NULL; //node that will delete the nodes 
	Node<T> *check = first; //node that will go through the list and find all nodes with the matching value 

	if (first == NULL) { //no nodes 
		return;
	}
	if (first == last && first->info == value) { //one node and it matches. Else do nothing 
		delete check;
		first = NULL;
		last = NULL;
		count--;
		return;
	}
	while (check != NULL) { //loop through list to find the nodes to delete 
		temp = check;
		check = check->forward;
		if (temp->info == value) { //if found node, do one of the following scenarios 
			if (temp == first) { //while still keeping the looping, delete the node if it's at the front 
				temp->forward->backward = NULL;
				first = temp->forward;
				delete temp;
				count--;
			}
			else if (temp == last) { //while still keeping the looping, delete the node if it's at the end 
				temp->backward->forward = NULL;
				last = temp->backward;
				delete temp;
				count--;
				return;
			}
			else { //while still keeping the looping, delete the node wherever on the list 
				temp->backward->forward = temp->forward;
				temp->forward->backward = temp->backward;
				delete temp;
				count--;
			}
		}
	}
}

//This helps with testing, do not modify. 
void testDeleteAllOfOccurrence() {
	doublyLinkedList<int> *d = new doublyLinkedList<int>;

	d->insertLast(9);
	d->insertLast(9);
	d->insertLast(4);
	d->insertLast(2);
	d->insertLast(9);
	d->insertLast(9);
	d->insertLast(5);
	d->insertLast(1);
	d->insertLast(9);
	d->insertLast(2);
	d->insertLast(9);
	d->insertLast(9);

	//Test just to make sure the data went in the list.  
	checkTest("testDeleteAllOfOccurrence #1", "9 9 4 2 9 9 5 1 9 2 9 9", d->getStringFromList());

	//Do a delete, test it. 
	d->deleteAllOfOccurrence(9);
	checkTest("testDeleteAllOfOccurrence #2", "4 2 5 1 2", d->getStringFromList());

	//Test deleting something that doesn't exist 
	d->deleteAllOfOccurrence(7);
	checkTest("testDeleteAllOfOccurrence #3", "4 2 5 1 2", d->getStringFromList());

	//A few more tests 
	d->deleteAllOfOccurrence(2);
	checkTest("testDeleteAllOfOccurrence #4", "4 5 1", d->getStringFromList());

	d->deleteAllOfOccurrence(4);
	checkTest("testDeleteAllOfOccurrence #5", "5 1", d->getStringFromList());

	d->deleteAllOfOccurrence(5);
	checkTest("testDeleteAllOfOccurrence #6", "1", d->getStringFromList());

	d->deleteAllOfOccurrence(1);
	checkTest("testDeleteAllOfOccurrence #7", "The list is empty.", d->getStringFromList());

	//retest deleting something that doesn't exist. 
	d->deleteAllOfOccurrence(7);
	checkTest("testDeleteAllOfOccurrence #8", "The list is empty.", d->getStringFromList());

	delete d;

}
void testReverseList(){

	//Test reversing an even amount of numbers 
	doublyLinkedList<int> *d = new doublyLinkedList<int>;
	for (int i = 0; i < 10; i++) {
		d->insertLast(i);
	}
	d->reverseList();
	checkTest("testReverseList #1", "9 8 7 6 5 4 3 2 1 0", d->getStringFromList());
	delete d;

	//Test reversing an odd amount of numbers 
	d = new doublyLinkedList<int>;
	for (int i = 0; i < 9; i++) {
		d->insertLast(i);
	}
	d->reverseList();
	checkTest("testReverseList #2", "8 7 6 5 4 3 2 1 0", d->getStringFromList());
	delete d;

	//Test reversing a list of only one number 
	d = new doublyLinkedList<int>;
	d->insertLast(1);
	d->reverseList();
	checkTest("testReverseList #3", "1", d->getStringFromList());
	delete d;

	//Make sure the method can handle no numbers 
	d = new doublyLinkedList<int>;
	d->reverseList();
	checkTest("testReverseList #4", "The list is empty.", d->getStringFromList());
	delete d;

}
void testGetAndDeleteLastSmallestValue(){

	//The smallest is in the middle 
	doublyLinkedList<int> *d = new doublyLinkedList<int>;
	d->insertLast(9);
	d->insertLast(4);
	d->insertLast(2);
	d->insertLast(1);
	d->insertLast(3);
	d->insertLast(2);
	d->insertLast(9);
	int temp = d->getAndDeleteLastSmallestValue();
	checkTest("testGetAndDeleteLastSmallestValue #1", 1, temp);

	checkTest("testGetAndDeleteLastSmallestValue #2", "9 4 2 3 2 9", d->getStringFromList());

	temp = d->getAndDeleteLastSmallestValue();
	checkTest("testGetAndDeleteLastSmallestValue #3", 2, temp);

	checkTest("testGetAndDeleteLastSmallestValue #4", "9 4 2 3 9", d->getStringFromList());


	delete d;

	//The smallest is at the beginning 
	d = new doublyLinkedList<int>;
	d->insertLast(2);
	d->insertLast(3);
	d->insertLast(4);
	d->insertLast(5);
	d->insertLast(6);
	d->insertLast(3);
	temp = d->getAndDeleteLastSmallestValue();
	checkTest("testGetAndDeleteLastSmallestValue #5", 2, temp);

	checkTest("testGetAndDeleteLastSmallestValue #6", "3 4 5 6 3", d->getStringFromList());

	//and then the end 
	temp = d->getAndDeleteLastSmallestValue();
	checkTest("testGetAndDeleteLastSmallestValue #7", 3, temp);

	checkTest("testGetAndDeleteLastSmallestValue #8", "3 4 5 6", d->getStringFromList());

	delete d;

	//Testing using a different template type 
	//Also testing finding the item at the end 
	doublyLinkedList<string>* ds = new doublyLinkedList<string>;
	ds->insertLast("grapes");
	ds->insertLast("bananas");
	ds->insertLast("oranges");
	ds->insertLast("lemons");
	ds->insertLast("apples");
	string stemp = ds->getAndDeleteLastSmallestValue();
	checkTest("testGetAndDeleteLastSmallestValue #9", "apples", stemp);
	delete ds;

	//Only one item in the list 
	d = new doublyLinkedList<int>;
	d->insertLast(3);
	temp = d->getAndDeleteLastSmallestValue();
	checkTest("testGetAndDeleteLastSmallestValue #10", 3, temp);

	checkTest("testGetAndDeleteLastSmallestValue #11", "The list is empty.", d->getStringFromList());
	delete d;

	//No items, testing try/catch 
	ds = new doublyLinkedList<string>;
	try{
		stemp = ds->getAndDeleteLastSmallestValue();
		checkTest("testGetAndDeleteLastSmallestValue #12", "Failure, this shouldn't display!", "");
	}
	catch (int error){
		checkTest("testGetAndDeleteLastSmallestValue #12", "Caught error", "Caught error");
	}
	delete ds;



}

void testOperatorSquareBrackets(){

	doublyLinkedList<string> ds;
	ds.insertLast("grapes");
	ds.insertLast("bananas");
	ds.insertLast("oranges");
	ds.insertLast("lemons");
	ds.insertLast("cherries");
	ds.insertLast("strawberries");
	ds.insertLast("apples");

	//testing getting a value out for that index 
	string value = ds[0];
	checkTest("testOperatorSquareBrackets #1", "grapes", value);

	value = ds[1];
	checkTest("testOperatorSquareBrackets #2", "bananas", value);

	value = ds[3];
	checkTest("testOperatorSquareBrackets #3", "lemons", value);

	value = ds[6];
	checkTest("testOperatorSquareBrackets #4", "apples", value);

	//testing return by reference and changing a value 
	ds[6] = "peaches";
	value = ds[6];
	checkTest("testOperatorSquareBrackets #5", "peaches", value);


}

//This method helps return a string representation of all nodes in the linked list 
template <typename T>
string doublyLinkedList<T>::getStringFromList() {
	stringstream ss;
	if (first == NULL) {
		ss << "The list is empty.";
	}
	else {

		Node<T> *currentNode = first;
		ss << currentNode->info;
		currentNode = currentNode->forward;

		while (currentNode != NULL) {
			ss << " " << currentNode->info;
			currentNode = currentNode->forward;
		};
	}
	return ss.str();
}

//This helps with testing, do not modify. 
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
		return false;
	}
}

//This helps with testing, do not modify. 
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
		return false;
	}
}

//This helps with testing, do not modify. 
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "  There are " << whatItIs << " bytes of memory yet to be reclaimed!" << endl;
		return false;
	}
}


void pressAnyKeyToContinue() {
	cout << "Press any key to continue...";

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

int main() {

	testOperatorSquareBrackets();
	//Each of these checks how many bytes you have used. 
	checkTestMemory("Memory Leak/Allocation Test #1", 0, manageMemory::getTotalSize());
	testReverseList();
	checkTestMemory("Memory Leak/Allocation Test #2", 0, manageMemory::getTotalSize());
	testGetAndDeleteLastSmallestValue();
	checkTestMemory("Memory Leak/Allocation Test #3", 0, manageMemory::getTotalSize());
	testDeleteAllOfOccurrence();
	checkTestMemory("Memory Leak/Allocation Test #4", 0, manageMemory::getTotalSize());

	pressAnyKeyToContinue();

	return 0;
}