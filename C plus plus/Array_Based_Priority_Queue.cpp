#include <iostream>
#include <string>
#include <sstream>
#include <map>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <stdio.h>
#endif // _WIN32

using namespace std;

//--------------------------------------------------------------------------
//A class I designed to help keep track of how much memory you allocate
//Do not modify, this is not part of your assignment, it just helps test it.
//For this to work, a class needs to inherit off of this one.
//Then this does the rest of the work, since it
//overloaded new, new[], delete, and delete[].
//--------------------------------------------------------------------------
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


void pressAnyKeyToContinue();
std::map<void *, std::size_t> manageMemory::mapOfAllocations;


//**********************
//INSERT CODE BELOW HERE
//**********************

//class priorityQueue : public class manageMemory

template <typename T>
class priorityQueue {
public:
	priorityQueue(unsigned int); //constructor  
	~priorityQueue();			//destructor  
	void push_back(const T&);	//pushing a value and priority with default value  
	void push_back(const T&, int); //pushing a value and priority with priority value  
	T pop_front();				//remove off the front  
	T pop_highest_priority();	//go through list and remove highest priority value  

private:
	int front;		//front index  
	int back;		//back index  
	int capacity;	//size of the array  
	T *values;		//array for values  
	int *priorityValues; //array for priorities  
};

template <typename T>
priorityQueue<T>::priorityQueue(unsigned int capacity) {
	values = new T[capacity];		//make the dynamic values array  
	priorityValues = new int[capacity]; //make the dynamic priority array  
	for (unsigned int i = 0; i < capacity; i++) {
		priorityValues[i] = 0;		//initialize all items in priority array to zero  
	}
	this->capacity = capacity;		//make the capacity the size passed in  
	front = 0;
	back = 0;
}

template <typename T>
priorityQueue<T>::~priorityQueue() {
	delete[] values;		//deallocate memory taken by the new keyword  
	delete[] priorityValues; //deallocate memory taken by the new keyword  
	capacity = 0;
	front = 0;
	back = 0;
}

template <typename T>
void priorityQueue<T>::push_back(const T& value) {
	if (front == back && priorityValues[front] != 0) { //if full, throw an error  
		throw 1;
	}
	else {
		values[back] = value;	//insert at the back the value passed in  
		priorityValues[back] = 16; //set default value of 16 at the index  
		back++;					//move back one so at next available index  
		if (back == capacity) { //allows for looping  
			back = 0;
		}
	}
	  
}

template <typename T>
void priorityQueue<T>::push_back(const T& value, int priority) {    
	if (front == back && priorityValues[front] != 0) {              
		throw 1;
	}
	else {
		values[back] = value;
		priorityValues[back] = priority;	//set to a different priority  
		back++;
		if (back == capacity) {
			back = 0;
		}
	}
}

template <typename T>
T priorityQueue<T>::pop_front() {
	if (front == back && priorityValues[front] == 0) { //if empty, throw the error  
		throw 21;
	}
	else {
		int index = front;	//reset to front  
		do {
			front++;	//move front to compare  
			if (front == capacity) { //loop around list if have to  
				front = 0;
			} if (front == back && priorityValues[index] != 0) {  
				priorityValues[index] = 0;
				return values[index];
			}
		} while (priorityValues[front] == 0); //keep moving until a nonzero  
		priorityValues[index] = 0;			//set the priority to zero  
		return values[index];				//return value  
	}
}

template <typename T>
T priorityQueue<T>::pop_highest_priority() {
	if (front == back && priorityValues[front] == 0) { //if empty, throw error  
		throw 21;
	}
	bool ok = true;   
	int biggest = front; //store index  
	int scan = front;	//store index again  
	while (scan != back || ok) {
		ok = false;		//if scan doesn't equal back, keep looping  
		if (scan == capacity) { //to loop around  
			scan = 0;
		}
		else if (priorityValues[biggest] < priorityValues[scan]) { //finds the first largest value  
			biggest = scan;					//store index  
			scan++;							//keep moving   
		}
		else {
			scan++; //else keep moving  
		}
	}			 
	if (biggest == front) { //at the front, call pop_front()  
		pop_front();
		return values[biggest];
	}
	else if ((biggest + 1) % capacity == back) { // else if at the back, pop 
		back = biggest;
		priorityValues[biggest] = 0;
		while (priorityValues[back] == 0) {
			back--;
		}
		back++;
		if (back == capacity) {
			back = 0;
		}
		return values[biggest];
	}
	else { //pop it at that value  
		priorityValues[biggest] = 0;
		return values[biggest];
	}
}


	//**********************
	//INSERT ABOVE CODE HERE
	//**********************
	//This helps with testing, do not modify.
	bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		if (whatItShouldBe == "") {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
		}
		else {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
		}
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
void testQueueSimple() {

	string result;
	string caughtError;
	priorityQueue<string> *pQueue = new priorityQueue<string>(5);

	//Tests push_back
	pQueue->push_back("penny");
	pQueue->push_back("nickel");
	pQueue->push_back("dime");
	pQueue->push_back("quarter");

	checkTest("testQueueSimple #1", "penny", pQueue->pop_front());
	checkTest("testQueueSimple #2", "nickel", pQueue->pop_front());
	checkTest("testQueueSimple #3", "dime", pQueue->pop_front());
	checkTest("testQueueSimple #4", "quarter", pQueue->pop_front());
	caughtError = "not caught";
	try {
		result = pQueue->pop_front();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueueSimple #5", "caught", caughtError);

	//Try it again.  This should make it wrap around, and fill up.
	pQueue->push_back("penny");
	pQueue->push_back("nickel");
	pQueue->push_back("dime");
	pQueue->push_back("quarter");

	checkTest("testQueueSimple #6", "penny", pQueue->pop_front());
	pQueue->push_back("half dollar");
	pQueue->push_back("silver dollar");

	//It should be full, no more room to add more.
	caughtError = "not caught";
	try {
		pQueue->push_back("million dollar bill");
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueueSimple #7", "caught", caughtError);

	checkTest("testQueueSimple #8", "nickel", pQueue->pop_front());
	checkTest("testQueueSimple #9", "dime", pQueue->pop_front());
	checkTest("testQueueSimple #10", "quarter", pQueue->pop_front());
	checkTest("testQueueSimple #11", "half dollar", pQueue->pop_front());
	checkTest("testQueueSimple #12", "silver dollar", pQueue->pop_front());
	caughtError = "not caught";
	try {
		result = pQueue->pop_front();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueueSimple #13", "caught", caughtError);

	//Test adding and removing back and forth
	pQueue->push_back("penny");
	checkTest("testQueueSimple #14", "penny", pQueue->pop_front());
	pQueue->push_back("nickel");
	checkTest("testQueueSimple #15", "nickel", pQueue->pop_front());
	pQueue->push_back("dime");
	checkTest("testQueueSimple #16", "dime", pQueue->pop_front());
	pQueue->push_back("quarter");
	checkTest("testQueueSimple #17", "quarter", pQueue->pop_front());
	pQueue->push_back("half dollar");
	checkTest("testQueueSimple #18", "half dollar", pQueue->pop_front());
	pQueue->push_back("silver dollar");
	checkTest("testQueueSimple #19", "silver dollar", pQueue->pop_front());
	caughtError = "not caught";
	try {
		result = pQueue->pop_front();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueueSimple #20", "caught", caughtError);

	delete pQueue;

}

//This helps with testing, do not modify.
void testQueuePriority() {

	string result;
	string caughtError;
	priorityQueue<string> *pQueue = new priorityQueue<string>(6);

	//Testing priorities
	pQueue->push_back("Michael Jordan", 1);
	pQueue->push_back("Tim Duncan");
	pQueue->push_back("Lebron James");
	pQueue->push_back("Carmelo Anthony");
	pQueue->push_back("John Stockton", 32);
	pQueue->push_back("Karl Malone", 31);

	checkTest("testQueuePriority #1", "John Stockton", pQueue->pop_highest_priority());
	checkTest("testQueuePriority #2", "Karl Malone", pQueue->pop_highest_priority());
	checkTest("testQueuePriority #3", "Tim Duncan", pQueue->pop_highest_priority());
	checkTest("testQueuePriority #4", "Lebron James", pQueue->pop_highest_priority());
	checkTest("testQueuePriority #5", "Carmelo Anthony", pQueue->pop_highest_priority());
	checkTest("testQueuePriority #6", "Michael Jordan", pQueue->pop_highest_priority());
	caughtError = "not caught";
	try {
		result = pQueue->pop_highest_priority();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueuePriority #7", "caught", caughtError);


	//put in a couple of fillers so this wraps around
	pQueue->push_back("Filler spot 1", 1);
	pQueue->push_back("Filler spot 2", 1);
	//get Michael Jordan to start front at index 2
	pQueue->push_back("Michael Jordan", 1);
	//remove those two at the front, so only Michael Jordan remains
	pQueue->pop_front();
	pQueue->pop_front();
	pQueue->push_back("Lebron James");
	pQueue->push_back("Tim Duncan");
	pQueue->push_back("John Stockton", 32);
	//this should wrap around the array here
	pQueue->push_back("Damian Lillard", 30);
	pQueue->push_back("Karl Malone", 31);

	//removing an item in the middle 
	checkTest("testQueuePriority #8", "John Stockton", pQueue->pop_highest_priority());
	//Test trying to force in room, but there shouldn't be room. (Don't use the 
	//prior middle space opened up by the last pop.)
	caughtError = "not caught";
	try {
		pQueue->push_back("Jeff Hornacek", 29);
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueuePriority #9", "caught", caughtError);

	//Make room at the end
	checkTest("testQueuePriority #10", "Karl Malone", pQueue->pop_highest_priority());
	//Now Jeff Hornaceck should go on just fine.  This should take the end space
	pQueue->push_back("Jeff Hornacek", 29);

	checkTest("testQueuePriority #11", "Damian Lillard", pQueue->pop_highest_priority());
	checkTest("testQueuePriority #12", "Jeff Hornacek", pQueue->pop_highest_priority());
	checkTest("testQueuePriority #13", "Lebron James", pQueue->pop_highest_priority());
	checkTest("testQueuePriority #14", "Tim Duncan", pQueue->pop_highest_priority());
	checkTest("testQueuePriority #15", "Michael Jordan", pQueue->pop_front());

	//it should be empty now
	caughtError = "not caught";
	try {
		result = pQueue->pop_front();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueuePriority #16", "caught", caughtError);

	delete pQueue;
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

	testQueueSimple();
	pressAnyKeyToContinue();
	//Checking if you have any memory leaks...
	checkTestMemory("Memory Leak/Allocation Test #1", 0, manageMemory::getTotalSize());
	testQueuePriority();
	//Checking if you have any memory leaks...
	checkTestMemory("Memory Leak/Allocation Test #2", 0, manageMemory::getTotalSize());
	pressAnyKeyToContinue();

	return 0;
}