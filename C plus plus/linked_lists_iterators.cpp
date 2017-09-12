#include <iostream> 
#include <map> 

//To prevent those using g++ from trying to use a library 
//they don't have 
#ifndef __GNUC__ 
#include <conio.h> 
#else 
#include <stdio.h> 
#endif 

#include <sstream> 

template <typename T> class doublyLinkedList;

using namespace std;

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
class nodeType : public manageMemory {
public:
	T info;
	nodeType *forward;
	nodeType *backward;
};


//****************** 
//The ListIterator class 
//******************     
template <typename T>
class ListIterator : public manageMemory {
	friend class doublyLinkedList<T>;
public:
	ListIterator();
	T& operator*() const;
	ListIterator operator++();
	ListIterator operator--();
	ListIterator operator+(const int amount) const;
	ListIterator operator-(const int amount) const;
	T& operator[](const int);


	bool operator!=(const ListIterator& right) const;
private:

	nodeType<T> *current;   //Where the ListIterator is pointing to 
	bool offTheEdge;
};

//****************** 
//The linked list class 
//****************** 
template <typename T>
class doublyLinkedList : public manageMemory {

public:

	//public members of the doublyLinkedList class 
	doublyLinkedList();
	~doublyLinkedList();
	string getStringFromList();

	void insertFirst(const T&);
	void insertLast(const T&);

	ListIterator<T> begin() const;
	ListIterator<T> end() const;


protected:
	nodeType<T> *first;
	nodeType<T> *last;
	int count;
};

template <typename T>
doublyLinkedList<T>::doublyLinkedList() {
	count = 0;
	first = NULL;
	last = NULL;
}

template <typename T>
doublyLinkedList<T>::~doublyLinkedList() {

	nodeType<T> *temp = NULL;

	while (first != NULL) {
		temp = first;
		first = first->forward;
		delete temp;
	}
}

template <typename T>
void doublyLinkedList<T>::insertFirst(const T& info) {
	nodeType<T> *temp = new nodeType<T>();
	temp->info = info;
	temp->forward = NULL;
	temp->backward = NULL;

	if (first == NULL) {
		//this list empty! 
		last = temp;
	}
	else {
		//put temp before first 
		temp->forward = first;
		first->backward = temp;

	}
	first = temp;
	count++;
}

template <typename T>
void doublyLinkedList<T>::insertLast(const T& info) {
	nodeType<T> *temp = new nodeType<T>();
	temp->info = info;
	temp->forward = NULL;

	if (first == NULL) {
		//this list empty! 
		first = temp;
	}
	else {
		//put temp after last 
		last->forward = temp;
		temp->backward = last;
	}
	last = temp;
	count++;
}


//This method helps return a string representation of all nodes in the linked list 
template <typename T>
string doublyLinkedList<T>::getStringFromList() {
	stringstream ss;
	if (first == NULL) {
		ss << "The list is empty.";
	}
	else {

		nodeType<T> *currentNode = first;
		ss << currentNode->info;
		currentNode = currentNode->forward;

		while (currentNode != NULL) {
			ss << " " << currentNode->info;
			currentNode = currentNode->forward;
		}
	}
	return ss.str();
}

//TODO 
//The linked list's begin() method, which returns an ListIterator object pointing to the first of the list 
template <typename T>
ListIterator<T> doublyLinkedList<T>::begin() const {
	ListIterator<T> temp;  // create temp iterator object 

	//temp.first = first;     
	temp.current = first;  // temp's current assigned to list's first 
	//pastBoundary = true; 
	if (this->count == 1) {
		temp.offTheEdge = false; //we are on the list and otherwise we wouldn't have a chance to run through our code below. 
	}
	else {
		temp.offTheEdge = true; // set offTheEdge to true 
	}
	return temp;
}

//TODO 
//The linked list's end() method, which returns an iterator object pointing to the first of the list 
template <typename T>
ListIterator<T> doublyLinkedList<T>::end() const {
	ListIterator<T> temp; // create temp iterator object 

	//temp.last = last; 
	temp.current = last;    // temp's current assigned to list's last 
	//pastBoundary = true; 
	temp.offTheEdge = true;     // set offTheEdge to true 

	return temp;
}

//*********************************** 
//The ListIterator class methods 
//*********************************** 

//The ListIterator's constructor 
template <typename T>
ListIterator<T>::ListIterator() {
	current = NULL;
	offTheEdge = false;
}

//TODO 
template <typename T>
T& ListIterator<T>::operator*() const{
	// get info that its pointing to 
	//ListIterator<T> temp; 
	//To make it compile 
	//T temp = NULL;*************************** you were creating that variable and returning it which was contributing to error 
	//return *temp; // temp.current; 
	return current->info; //we want to return the current->info 
}

//TODO 
template <typename T>
ListIterator<T> ListIterator<T>::operator++() { //-0.5 points for looping and half a point was the minimum I could take off 
	/***********************************************************************************************************************
	Your function here wasn't working quite right either, this was contributing to your line 261 error. Working code below.
	***************************************************************************************************************
	ListIterator<T> temp;
	temp.offTheEdge = false;

	while (temp.offTheEdge == false || current != NULL) {       // you can't loop here, you're just moving by one.
	current = current->forward;

	if (current == NULL)  {
	temp.offTheEdge = true;
	}

	}
	return *this;
	**********************************************************************************************************/
	if (this->current->forward == NULL) { //if we are at the edge of the list, tell the iteration that we are at the end and return the node 
		this->offTheEdge = true; //we will be off the edge so set it to true 
		return *this; //return the node at the end 
	}
	else {
		this->current = this->current->forward; //if not at the end, we keep moving forward 
		this->offTheEdge = false; //we aren't at the end so we aren't off the edge 
		return *this; //return the node we are at now 
	}
}

//TODO 
template <typename T>
ListIterator<T> ListIterator<T>::operator--() { //-0.5 points for looping and half a point was the minimum I could take off 
	/******************************************************************************************************************************
	You had some right thinking with this function but it wasn't working, working code belox.
	***************************************************************************************************************
	ListIterator<T> temp;
	temp.offTheEdge = false;

	while (temp.offTheEdge == false || current != NULL) {   // move forward only if won't begin NULL
	current = current->backward;                 // move foward one node

	if (current == NULL) {          // if the next node is NULL
	temp.offTheEdge = true;         // set offTheEdge to true
	}

	}

	return *this;
	****************************************************************************************************************************/
	if (this->current->backward == NULL) { //if we are at the beginning of the list, tell the iteration we reached the edge and return the node 
		this->offTheEdge = true; //we will be off the edge, set it to true 
		return *this; //return the first node 
	}
	else {
		this->current = this->current->backward; //we aren't at the beginning of the list, let's just go back one. 
		this->offTheEdge = false; //we aren't off the list so our offTheEdge would be false 
		return *this; //return the node we are at. 
	}
}

//TODO 
template <typename T>
ListIterator<T> ListIterator<T>::operator+(const int amount) const { //-1 point for not taking negative values into account and missing the other logic you see in the working code 
	/***************************************************************************************************************
	You were working in the right direction, but you didn't take into account all the things you needed to.
	***************************************************************************************************************
	// copy of the current "this" object, and move that new object forward.
	ListIterator<T>temp(*this);
	// temp becomes the copy of the object
	// move forward the copy 'amount' number of times
	for (int x = 0; x < amount; x++) {
	temp.current = temp.current->forward;
	}

	return *this;
	**************************************************************************************************************/
	ListIterator<T> temp(*this);
	if (amount <= 0) { //for negative numbers 
		for (int i = 0; i > amount; i--) { //if adding negative numbers, you're basically subtracting 
			--temp; //that's why I decrement 
		}
		if (temp.offTheEdge == true) { //after looping, if the iterator is off edge we just keep iterator at what it was 
			return *this;
		}
		else {
			return temp; //else return the correct node 
		}
	}
	else {
		for (int i = 0; i < amount; i++) { //adding positive numbers 
			++temp; //incrememnt the list 
		}
		if (temp.offTheEdge == true) { //if it's too far, just keep what it was before 
			return *this;
		}
		else {
			return temp; //else show the correct node 
		}
	}
}

//TODO 
template <typename T>
ListIterator<T> ListIterator<T>::operator-(const int amount) const { //-1 point for not taking negative values into account and missing the other logic you see in the working code 
	/***************************************************************************************************************
	You were working in the right direction, but you didn't take into account all the things you needed to.
	***************************************************************************************************************
	// copy of the current "this" object, and move that new object backward.
	ListIterator<T>temp(*this);
	// temp becomes the copy of the object
	// move backward the copy 'amount' number of times
	for (int x = 0; x < amount; x++) {
	temp.current = temp.current->backward;
	}

	return *this;
	**************************************************************************************************************/
	ListIterator<T> temp(*this);
	if (amount <= 0) { //for negative numbers 
		for (int i = 0; i > amount; i--) { //if subtracting negative numbers, it's the same as adding in our list 
			++temp; //that's why I incrememnt 
		}
		if (temp.offTheEdge == true) { //if iterator is off the edge, return what we first had 
			return *this;
		}
		else {
			return temp; //return where our iterator is at 
		}
	}
	else {
		for (int i = 0; i < amount; i++) { //just subtracting positive numbers 
			--temp; //that's why I decrement 
		}
		if (temp.offTheEdge == true) { //if iterator is off the edge, just return what we started at 
			return *this;
		}
		else {
			return temp; //else return where we are now. 
		}
	}
}

//TODO 
template <typename T>
T& ListIterator<T>::operator[](const int index) { //-1 point for not having anything here 
	/****************************************************************************************************************
	This function is actually really easy if you have your plus function completed.
	****************************************************************************************************************/
	ListIterator<T> temp(*this);
	temp = temp + index;
	return temp.current->info;
}

//TODO 
template <typename T>
bool ListIterator<T>::operator!=(const ListIterator<T>& right) const { //-2 points (!= operator and tricky iterator) 
	/****************************************************************************************************************
	You didn't have any code here, this was contributing to your line 261 error. Make sure to check out lines 213-218
	for a solution to the tricky iteration that I thought of. Most people used logic to include two edges rather than
	just one, I feel like I thought of an easier solution.
	*****************************************************************************************************************/
	if (this->offTheEdge == right.offTheEdge && this->current == right.current) {
		return false;
	}
	return true;
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


//This helps with testing, do not modify. 
void testIteration(){

	doublyLinkedList<int> myList;

	//Our test data should have all even numbers from 2 to 20 
	for (int i = 2; i <= 20; i += 2)  {
		myList.insertLast(i);
	}
	cout << "TestIteration test #1, this should display 2 4 6 8 10 12 14 16 18 20." << endl;

	for (auto i : myList) {
		cout << i << " ";
	}

	cout << endl;
}

//This helps with testing, do not modify. 
void testIterationTricky(){

	doublyLinkedList<int> myListOneNode;

	myListOneNode.insertLast(42);
	cout << "TestIterationTricky test #1, the next line should display 42" << endl;
	//see if we can just iterator through one item.   
	for (auto i : myListOneNode) {
		cout << i << " ";
	}
	cout << endl;

	doublyLinkedList<int> myListEmpty;
	cout << "TestIterationTricky test #2, the next line shouldn't display anything" << endl;
	//see if we can just iterator through one item.   
	for (auto i : myListEmpty) {
		cout << i << " ";
	}
	cout << endl;

}





//This helps with testing, do not modify. 
void testListIteratorIncrement(){

	doublyLinkedList<int> *d = new doublyLinkedList<int>;

	//Our test data should have all even numbers from 2 to 20 
	for (int i = 2; i <= 20; i += 2)  {
		d->insertLast(i);
	}

	//Get an iterator which points at the beginning of the list 
	ListIterator<int> iter = d->begin();

	//Test that it does point to the first 
	checkTest("testListIteratorsIncrement #1", 2, *iter);

	//Test that our ListIterator can move forward; 
	++iter;

	checkTest("testListIteratorsIncrement #2", 4, *iter);

	//move it some more 
	for (int i = 0; i < 7; i++)  {
		++iter;
	}
	checkTest("testListIteratorsIncrement #3", 18, *iter);

	//Hit the end 
	++iter;
	checkTest("testListIteratorsIncrement #4", 20, *iter);

	//Attempt to go past the end 
	++iter;
	checkTest("testListIteratorsIncrement #5", 20, *iter);

	delete d;
}

//This helps with testing, do not modify. 
void testListIteratorDecrement(){

	doublyLinkedList<int> *d = new doublyLinkedList<int>;

	//Our test data should have all even numbers from 2 to 20 
	for (int i = 2; i <= 20; i += 2)  {
		d->insertLast(i);
	}

	//Get an ListIterator which points at the beginning of the list 
	ListIterator<int> iter = d->end();

	//Test that it does point to the first 
	checkTest("testListIteratorsDecrement #1", 20, *iter);

	//Test that our ListIterator can move forward; 
	--iter;
	checkTest("testListIteratorsDecrement #2", 18, *iter);

	//move it some more 
	for (int i = 0; i < 7; i++)  {
		--iter;
	}
	checkTest("testListIteratorsDecrement #3", 4, *iter);

	//Hit the end 
	--iter;
	checkTest("testListIteratorsDecrement #4", 2, *iter);

	//Attempt to go past the end 
	--iter;
	checkTest("testListIteratorsDecrement #5", 2, *iter);

	//Now go back forward 
	++iter;
	checkTest("testListIteratorsDecrement #6", 4, *iter);

	delete d;
}

//This helps with testing, do not modify. 
void testListIteratorPlus(){

	doublyLinkedList<int> *d = new doublyLinkedList<int>;

	//Our test data should have all even numbers from 2 to 20 
	for (int i = 2; i <= 20; i += 2)  {
		d->insertLast(i);
	}

	//Get an ListIterator which points at the beginning of the list 
	ListIterator<int> iter = d->begin();

	ListIterator<int> iterResult;
	//Test that it does point to the first 
	checkTest("testListIteratorsPlus #1", 2, *iter);

	//Test moving 1 forward 
	iter = iter + 1;
	checkTest("testListIteratorsPlus #2", 4, *iter);

	//Test moving 5 forward 
	iter = iter + 5;
	checkTest("testListIteratorsPlus #3", 14, *iter);

	//Test moving 3 forward 
	iter = iter + 3;
	checkTest("testListIteratorsPlus #4", 20, *iter);

	//Test attempting to move 
	iter = iter + 1;
	checkTest("testListIteratorsPlus #5", 20, *iter);

	//Start back at the beginning, attempt to go too far. 
	iter = d->begin();
	iter = iter + 100;
	checkTest("testListIteratorsPlus #6", 2, *iter);

	//Start back at the beginning, verify left operand stays constant. 
	iter = d->begin();
	iterResult = iter + 4;
	checkTest("testListIteratorsPlus #7", 2, *iter);
	checkTest("testListIteratorsPlus #8", 10, *iterResult);


	delete d;
}

//This helps with testing, do not modify. 
void testListIteratorMinus(){

	doublyLinkedList<int> *d = new doublyLinkedList<int>;

	//Our test data should have all even numbers from 2 to 20 
	for (int i = 2; i <= 20; i += 2)  {
		d->insertLast(i);
	}

	//Get an ListIterator which points at the beginning of the list 
	ListIterator<int> iter = d->end();
	ListIterator<int> iterResult;
	//Test that it does point to the first 
	checkTest("testListIteratorMinus #1", 20, *iter);

	//Test moving 1 backward 
	iter = iter - 1;
	checkTest("testListIteratorMinus #2", 18, *iter);

	//Test moving 5 backward 
	iter = iter - 5;
	checkTest("testListIteratorMinus #3", 8, *iter);

	//Test moving 3 backward 
	iter = iter - 3;
	checkTest("testListIteratorMinus #4", 2, *iter);

	//Test attempting to move backward 
	iter = iter - 1;
	checkTest("testListIteratorMinus #5", 2, *iter);

	//Start back at the end, attempt to go too far. 
	iter = d->end();
	iter = iter - 100;
	checkTest("testListIteratorMinus #6", 20, *iter);

	//Start back at the end, verify left operand stays constant. 
	iter = d->end();
	iterResult = iter - 4;
	checkTest("testListIteratorMinus #7", 20, *iter);
	checkTest("testListIteratorMinus #8", 12, *iterResult);

	//Test trying to move with negative numbers 
	iter = d->begin();
	iter = iter + 4;
	iter = iter + (-2);
	checkTest("testListIteratorMinus #9", 6, *iter);

	iter = d->begin();
	iter = iter + 4;
	iter = iter - (-2);
	checkTest("testListIteratorMinus #10", 14, *iter);

	delete d;
}

//This helps with testing, do not modify. 
void testListIteratorSquareBrackets(){

	doublyLinkedList<int> *d = new doublyLinkedList<int>;

	//Our test data should have all even numbers from 2 to 20 
	for (int i = 2; i <= 20; i += 2)  {
		d->insertLast(i);
	}

	ListIterator<int> iter = d->begin();

	checkTest("testListIteratorSquareBrackets #1", 2, iter[0]);

	checkTest("testListIteratorSquareBrackets #2", 12, iter[5]);

	checkTest("testListIteratorSquareBrackets #3", 2, iter[0]);

	++iter;
	++iter;

	checkTest("testListIteratorSquareBrackets #4", 6, iter[0]);

	checkTest("testListIteratorSquareBrackets #5", 10, iter[2]);

	checkTest("testListIteratorSquareBrackets #6", 6, iter[0]);

	checkTest("testListIteratorSquareBrackets #7", 2, iter[-2]);

	checkTest("testListIteratorSquareBrackets #8", 6, iter[0]);

	iter[0] = 100;

	checkTest("testListIteratorSquareBrackets #9", 100, iter[0]);

	iter[1] = 200;

	checkTest("testListIteratorSquareBrackets #10", 200, iter[1]);
	checkTest("testListIteratorSquareBrackets #11", 100, iter[0]);

	delete d;
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
	cout << endl;
}

int main() {

	cout << "This first test can run forever until you get operators *, != and ++ implemented." << endl;
	pressAnyKeyToContinue();
	testIteration();
	checkTestMemory("Memory Leak/Allocation Test #1", 0, manageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testListIteratorIncrement();
	checkTestMemory("Memory Leak/Allocation Test #2", 0, manageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testListIteratorDecrement();
	checkTestMemory("Memory Leak/Allocation Test #3", 0, manageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testListIteratorPlus();
	checkTestMemory("Memory Leak/Allocation Test #4", 0, manageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testListIteratorMinus();
	checkTestMemory("Memory Leak/Allocation Test #5", 0, manageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testListIteratorSquareBrackets();
	checkTestMemory("Memory Leak/Allocation Test #6", 0, manageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testIterationTricky();
	checkTestMemory("Memory Leak/Allocation Test #7", 0, manageMemory::getTotalSize());
	pressAnyKeyToContinue();

	return 0;
}