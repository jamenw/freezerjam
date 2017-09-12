#include <iostream> 
//To prevent those using g++ from trying to use a library 
//they don't have 
#ifndef __GNUC__ 
#include <conio.h> 
#else 
#include <cstdio> 
#endif 

#include <sstream> 

using namespace std;


#include <map> 

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
	nodeType *link;
};


//****************** 
//The linked list base class 
//This contains within it a class declaration for an iterator 
//****************** 
template <typename T>
class singlyLinkedList : public manageMemory  {
public:

	//public members of the singlyLinkedList class 
	singlyLinkedList();
	~singlyLinkedList();
	string getStringFromList();

	void insertFirst(const T&);
	void insertLast(const T&);
	T& getKthElement(const int);               //For your assignment 
	void deleteKthElement(const int);          //For your assignment 
	void deleteFirstInstanceOfLargest();       //For your assignment 


protected:
	nodeType<T> *first;
	nodeType<T> *last;
	int count;
};


template <typename T>
singlyLinkedList<T>::singlyLinkedList() {
	first = NULL;
	last = NULL;
	count = 0;
}

template <typename T>
singlyLinkedList<T>::~singlyLinkedList() {
	nodeType<T> *temp;
	while (first != NULL) {
		temp = first;
		first = first->link;
		delete temp;
	}
	last = NULL;
	count = 0;
}

template <typename T>
void singlyLinkedList<T>::insertFirst(const T& value) {
	nodeType<T> *temp = new nodeType<T>();
	temp->info = value;
	temp->link = NULL;

	//empty list scenario 
	if (first == NULL) {
		last = temp;
	}
	else {
		temp->link = first;
	}

	first = temp;
	count++;
}

template <typename T>
void singlyLinkedList<T>::insertLast(const T& value) {
	nodeType<T> *temp = new nodeType<T>;
	temp->info = value;
	temp->link = NULL;

	if (first == NULL) {
		first = temp;
	}
	else {
		//put it on 
		last->link = temp;
	}
	last = temp;
	count++;
}


//TODO: Complete this method 
template <typename T>
T& singlyLinkedList<T>::getKthElement(const int item) // good job on this function!!!! 
{
	int countit = 1;

	nodeType<T> *temp = first;

	while (countit < item) {

		temp = temp->link;
		countit++;

	}

	return temp->info;

}

//TODO: Complete this method 
template <typename T>
void singlyLinkedList<T>::deleteKthElement(const int item)
{
	int countit = 1;
	//cout << "item: " << item << endl; just did this for viewing purposes 

	nodeType<T> *previous = first;
	nodeType<T> *current = first;

	/*while (countit < item) {  //I'm going to leave your code here and do the modified code below so that you can compare

	previous = current;
	current = current->link;
	countit++;
	}

	delete previous;
	previous = NULL;
	count--;
	*********************************************************************************************************/
	//we need to first include our scenarios, this is what you were missing 
	if (first == NULL) { //no nodes in list 
		return;
	}
	if (first == last) { //one node in the list 
		delete current;
		first = NULL;
		last = NULL;
		count--;
		return;
	}
	if (item > count) { //if item passed in is our of scope, just leave the function 
		return;
	}

	while (countit <= item) { //okay, now we'll have to loop through so that we  
		if (countit == item) { //if our position equals the position we are at, leave the loop because our current already holds this position 
			break;
		}
		else if (current->link != NULL) { //if it isnt' equal, let's move on to the next node 
			previous = current;
			current = current->link;
			countit++;
		}
	} //now that we found our node, we can go and delete it depending on where it is 
	if (current == first) { //if our node is at the front 
		first = current->link;
		delete current;
		count--;
		return;
	}
	else if (current == last) { //if our node is at the end of the list 
		previous->link = NULL;
		last = previous;
		delete current;
		count--;
		return;
	}
	else { //if it isn't first or last, it must be in between 
		previous->link = current->link;
		delete current;
		count--;
	}
}

//TODO: Complete this method 
template <typename T>
void singlyLinkedList<T>::deleteFirstInstanceOfLargest()
{
	/*int countit = 1;

	nodeType<T> *previous = NULL;
	nodeType<T> *current = first;
	nodeType<T> *temp = first;

	int biggest = 0;
	int bigcount = 1;

	while (temp->link != last)  {
	if (temp->info > biggest) {
	biggest = temp->info;

	}
	bigcount++;
	}

	while (countit < bigcount) {

	previous = current;
	current = current->link;
	countit++;
	}

	delete previous;
	previous = NULL;
	count--;
	******************************************************************************************************************************/
	nodeType<T> *prev = first;        //need to initialize these; 
	nodeType<T> *prevLarge = first;
	nodeType<T> *largest = first;
	nodeType<T> *current = first;
	int large = 0; //int to track our large value; 

	if (first == NULL) { //no nodes, don't do anything 
		return;
	}
	else if (first == last) { //only one node that you are deleting, get rid of it 
		delete current;
		first = NULL;
		last = NULL;
		count = 0;
		return;
	}
	//okay, those scenarios are taken care of, now let's take care of finding the node we need. 
	for (int i = 1; i <= count; i++) {
		if (current->info > large) { //if the node is larger than what we have, set that node to largest and then modify the others 
			largest = current;
			prevLarge = prev;
			large = current->info;
			prev = current;
			current = current->link;
		}
		else {
			if (current->link != NULL) { //else, continue on the list until we get to the end 
				prev = current;
				current = current->link;
			}
		}
	}
	//now that we have the node with the first largest value, let's code on how to delete it 
	if (largest == first) { //if the largest node is at the front 
		first = largest->link;
		delete largest;
		count--;
		return;
	}
	else if (largest == last) { //if the largest node is at the back 
		prevLarge->link = NULL;
		last = prevLarge;
		delete largest;
		count--;
		return;
	}
	else {  //means that the node is somewhere in between so run this code 
		prevLarge->link = largest->link;
		delete largest;
		count--;
	}

}


//This method helps return a string representation of all nodes in the linked list, do not modify. 
template <typename T>
string singlyLinkedList<T>::getStringFromList() {
	stringstream ss;
	if (first == NULL) {
		ss << "The list is empty.";
	}
	else {

		nodeType<T> *currentNode = first;
		ss << currentNode->info;
		currentNode = currentNode->link;

		while (currentNode != NULL) {
			ss << " " << currentNode->info;
			currentNode = currentNode->link;
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
		cout << "***Failed test " << testName << " *** " << endl << "  You lost track of " << whatItIs << " bytes in memory!" << endl;
		return false;
	}
}

//This helps with testing, do not modify. 
void testGetKthElement() {
	singlyLinkedList<int> *d = new singlyLinkedList<int>;
	for (int i = 10; i < 20; i++)  {
		d->insertLast(i);
	}

	//Test just to make sure the data went in the list.  
	checkTest("testGetKthElement #1", "10 11 12 13 14 15 16 17 18 19", d->getStringFromList());

	//Test retrieving items.  
	int item = d->getKthElement(1);
	checkTest("testGetKthElement #2", 10, item);

	item = d->getKthElement(5);
	checkTest("testGetKthElement #3", 14, item);

	item = d->getKthElement(10);
	checkTest("testGetKthElement #4", 19, item);

	//Make sure the list was undisturbed during this time 
	checkTest("testGetKthElement #5", "10 11 12 13 14 15 16 17 18 19", d->getStringFromList());

	//now test the return by reference 
	d->getKthElement(1) = 1000;
	checkTest("testGetKthElement #6", "1000 11 12 13 14 15 16 17 18 19", d->getStringFromList());

	delete d;
}

//This helps with testing, do not modify. 
void testDeleteKthElement() {
	singlyLinkedList<int> *d = new singlyLinkedList<int>;
	for (int i = 10; i < 17; i++)  {
		d->insertLast(i);
	}

	//Test just to make sure the data went in the list.  
	checkTest("testDeleteKthElement #1", "10 11 12 13 14 15 16", d->getStringFromList());

	//Test deleting front items.  
	d->deleteKthElement(1);
	checkTest("testDeleteKthElement #2", "11 12 13 14 15 16", d->getStringFromList());

	d->deleteKthElement(1);
	checkTest("testDeleteKthElement #3", "12 13 14 15 16", d->getStringFromList());

	//Test deleting back itmes 
	d->deleteKthElement(5);
	checkTest("testDeleteKthElement #4", "12 13 14 15", d->getStringFromList());

	d->deleteKthElement(4);
	checkTest("testDeleteKthElement #5", "12 13 14", d->getStringFromList());

	//Test deleting a Kth element that doesn't exist. 
	d->deleteKthElement(500);
	checkTest("testDeleteKthElement #6", "12 13 14", d->getStringFromList());

	//Test deleting middle item 
	d->deleteKthElement(2);
	checkTest("testDeleteKthElement #7", "12 14", d->getStringFromList());

	//Test deleting item on the back 
	d->deleteKthElement(2);
	checkTest("testDeleteKthElement #8", "12", d->getStringFromList());

	//Test deleting item on the front 
	d->deleteKthElement(1);
	checkTest("testDeleteKthElement #9", "The list is empty.", d->getStringFromList());

	//Test attempting to delete from an empty list 
	d->deleteKthElement(1);
	checkTest("testDeleteKthElement #10", "The list is empty.", d->getStringFromList());

	delete d;
}

//This helps with testing, do not modify. 
void testDeleteFirstInstanceOfLargest() {
	singlyLinkedList<int> *d = new singlyLinkedList<int>;

	d->insertLast(4);
	d->insertLast(3);
	d->insertLast(5);
	d->insertLast(1);
	d->insertFirst(2);
	d->insertFirst(5);
	d->insertLast(5);


	//Test just to make sure the data went in the list. This tests insertFirst and insertLast 
	checkTest("testDeleteFirstInstanceOfLargest #1", "5 2 4 3 5 1 5", d->getStringFromList());

	//Do a delete, test it. 
	d->deleteFirstInstanceOfLargest();
	checkTest("testDeleteFirstInstanceOfLargest #2", "2 4 3 5 1 5", d->getStringFromList());

	d->deleteFirstInstanceOfLargest();
	checkTest("testDeleteFirstInstanceOfLargest #3", "2 4 3 1 5", d->getStringFromList());

	d->deleteFirstInstanceOfLargest();
	checkTest("testDeleteFirstInstanceOfLargest #4", "2 4 3 1", d->getStringFromList());

	d->deleteFirstInstanceOfLargest();
	checkTest("testDeleteFirstInstanceOfLargest #5", "2 3 1", d->getStringFromList());

	d->deleteFirstInstanceOfLargest();
	checkTest("testDeleteFirstInstanceOfLargest #6", "2 1", d->getStringFromList());

	d->deleteFirstInstanceOfLargest();
	checkTest("testDeleteFirstInstanceOfLargest #7", "1", d->getStringFromList());

	//testing deleting the only item on the list 
	d->deleteFirstInstanceOfLargest();
	checkTest("testDeleteFirstInstanceOfLargest #8", "The list is empty.", d->getStringFromList());

	//testing attempting to delete from an empty list 
	d->deleteFirstInstanceOfLargest();
	checkTest("testDeleteFirstInstanceOfLargest #9", "The list is empty.", d->getStringFromList());

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

}


int main() {


	//Each of these checks how many bytes you have used. 
	checkTestMemory("Memory Leak/Allocation Test #1", 0, manageMemory::getTotalSize());

	//For your assignment, write the code to make these three methods work 
	//You should not modify the code here in main. 

	testGetKthElement();

	checkTestMemory("Memory Leak/Allocation Test #2", 0, manageMemory::getTotalSize());

	testDeleteKthElement();

	checkTestMemory("Memory Leak/Allocation Test #3", 0, manageMemory::getTotalSize());

	testDeleteFirstInstanceOfLargest();

	checkTestMemory("Memory Leak/Allocation Test #4", 0, manageMemory::getTotalSize());

	pressAnyKeyToContinue();


	return 0;
}