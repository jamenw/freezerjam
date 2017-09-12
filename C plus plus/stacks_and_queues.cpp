#include <iostream> 
#include <string> 
#include <sstream> 
//To prevent those using g++ from trying to use a library 
//they don't have 
#ifndef __GNUC__ 
#include <conio.h> 
#endif 

using namespace std;


//********************************** 
//Write your code below here 
//********************************** 

// Stack2420 

template <typename T>
class Stack2420  {
public:
	Stack2420(unsigned int size1);// constructor 
	~Stack2420();// destructor 
	// other stuff 
	void push(const T& value);
	T pop();
	unsigned int size();

private:
	T *internalArray;
	unsigned int currentSize;
	unsigned int capacity;
};


template <typename T>
Stack2420<T>::Stack2420(unsigned int size1)  {
	//constructor stuff 

	internalArray = new T[size1];   //allocate new array 
	this->capacity = size1;          //save results in a pointer 
	currentSize = 0;                //set currentSize to 0 
	capacity = size1;               //set capacity to passed in value 
}

template <typename T>
Stack2420<T>::~Stack2420()  {
	//destructor stuff 
	delete[] internalArray;
	internalArray = NULL;
	currentSize = 0;
	capacity = 0;
}

template <typename T>
void Stack2420<T>::push(const T& value)  {
	// currentSize = capacity??  if so throw an error 1 code 
	if (currentSize == capacity) {
		cout << "stack is full!" << endl;
		throw 1;
	}
	else {

		// insert value 
		internalArray[currentSize] = value;
		cout << "push --> " << internalArray[currentSize] << endl;
		currentSize++;  //increment currentSize 
	}
}


template <typename T>
T Stack2420<T>::pop() {
	if (size() == 0) {  //check stack to see if empty 
		cout << "stack is empty!" << endl;
		throw 1;

	}
	else {
		// return correct value...decrement currentSize 

		currentSize--;
		cout << "pop ---> " << internalArray[currentSize] << endl;
		return internalArray[size()];

	}

}

template <typename T>
unsigned int Stack2420<T>::size() {
	return currentSize;
}


//*************************************************** 
// Queue2420 

template <typename T>
class Queue2420  {
public:
	Queue2420(unsigned int size1);// constructor 
	~Queue2420();// destructor 
	// other stuff 
	void push_back(const T& value);
	T pop_front();
	unsigned int size();

private:
	T *internalArray;
	unsigned int currentSize;
	unsigned int capacity;
	unsigned int front;
	unsigned int back;
};


template <typename T>
Queue2420<T>::Queue2420(unsigned int size1)  {
	//constructor stuff 

	internalArray = new T[size1];   //allocate new array 
	this->capacity = size1;          //save results in a pointer 
	currentSize = 0;                //set currentSize to 0 
	capacity = size1;               //set capacity to passed in value 
	front = 0;
	back = 0;
}

template <typename T>
Queue2420<T>::~Queue2420()  {
	//destructor stuff 
	delete[] internalArray;
	internalArray = NULL;
	currentSize = 0;
	capacity = 0;
	front = 0;
	back = 0;

}

template <typename T>
void Queue2420<T>::push_back(const T& value)  {
	// currentSize = capacity??  if so throw an error 1 code 
	if (currentSize == capacity) {
		cout << "stack is full!" << endl;
		throw 1;
	}
	else {

		// insert value 
		internalArray[back] = value;
		cout << "push --> " << internalArray[back] << endl;
		currentSize++;  //increment currentSize 
		back++;         //increment back 
		if (back == capacity) {
			back = 0;
		}

	}
}


template <typename T>
T Queue2420<T>::pop_front() {


	if (size() == 0) {  //check stack to see if empty 
		cout << "stack is empty!" << endl;
		throw 1;

	}
	else {
		// return front of array...decrement currentSize 


		T temp = internalArray[front++];
		currentSize--;

		if (front == capacity) {
			front = 0;
		}

		cout << "pop ---> " << temp << endl;
		return temp;

	}

}

template <typename T>
unsigned int Queue2420<T>::size() {
	return currentSize;
}


//********************************** 
//Write your code above here 
//********************************** 

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
		cout << "***Failed test " << testName << " *** " << endl << ".  ";
		cout << "You are manually managing " << whatItIs << " bytes in memory, but it should be " << whatItShouldBe << " bytes." << endl;
		return false;
	}
}



//This helps with testing, do not modify. 
void testStackSimple() {

	string result;
	string caughtError;
	Stack2420<int> *stack = new Stack2420<int>(5);

	stack->push(1);
	int data = stack->pop();
	checkTest("testStackSimple #1", 1, data);

	stack->push(1);
	stack->push(2);
	stack->push(3);
	stack->push(4);
	stack->push(5);
	checkTest("testStackSimple #2", 5, stack->pop());
	checkTest("testStackSimple #3", 4, stack->pop());
	checkTest("testStackSimple #4", 3, stack->pop());
	checkTest("testStackSimple #5", 2, stack->pop());
	checkTest("testStackSimple #6", 1, stack->pop());

	//now cover error handling 
	try {
		result = stack->pop();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testStackSimple #7", "caught", caughtError);

	//check currentSize 
	stack->push(12);
	stack->push(32);
	checkTest("testStackSimple #8", 2, stack->size());

	//now test filling it up 
	stack->push(14);
	stack->push(53);
	stack->push(47);


	//now cover error handling 
	try {
		stack->push(8);
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testStackSimple #9", "caught", caughtError);

	delete stack;

	//test some strings 
	Stack2420<string> *sstack = new Stack2420<string>(10);

	sstack->push("apple");
	sstack->push("banana");
	sstack->push("cherry");

	checkTest("testStackSimple #10", 3, sstack->size());

	//remove banana from the stack. 
	string temp = sstack->pop();
	sstack->pop();
	sstack->push(temp);

	//see if it worked 
	checkTest("testStackSimple #11", "cherry", sstack->pop());
	checkTest("testStackSimple #12", "apple", sstack->pop());

	delete sstack;

}

//This helps with testing, do not modify. 
void testQueueSimple() {

	string result;
	string caughtError;
	Queue2420<string> *pQueue = new Queue2420<string>(5);

	//Tests push_back 
	pQueue->push_back("penny");
	pQueue->push_back("nickel");
	pQueue->push_back("dime");
	pQueue->push_back("quarter");

	checkTest("testQueueSimple #1", 4, pQueue->size());

	checkTest("testQueueSimple #2", "penny", pQueue->pop_front());
	checkTest("testQueueSimple #3", 3, pQueue->size());

	checkTest("testQueueSimple #4", "nickel", pQueue->pop_front());
	checkTest("testQueueSimple #5", "dime", pQueue->pop_front());
	checkTest("testQueueSimple #6", "quarter", pQueue->pop_front());
	checkTest("testQueueSimple #7", 0, pQueue->size());

	caughtError = "not caught";
	try {
		result = pQueue->pop_front();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueueSimple #8", "caught", caughtError);
	checkTest("testQueueSimple #9", 0, pQueue->size());

	//Try it again.  This should make it wrap around, and fill up. 
	pQueue->push_back("penny");
	pQueue->push_back("nickel");
	pQueue->push_back("dime");
	pQueue->push_back("quarter");

	checkTest("testQueueSimple #10", "penny", pQueue->pop_front());
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
	checkTest("testQueueSimple #11", "caught", caughtError);

	checkTest("testQueueSimple #12", "nickel", pQueue->pop_front());
	checkTest("testQueueSimple #13", "dime", pQueue->pop_front());
	checkTest("testQueueSimple #14", "quarter", pQueue->pop_front());
	checkTest("testQueueSimple #15", "half dollar", pQueue->pop_front());
	checkTest("testQueueSimple #16", "silver dollar", pQueue->pop_front());
	caughtError = "not caught";
	try {
		result = pQueue->pop_front();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueueSimple #17", "caught", caughtError);

	//Test adding and removing back and forth 
	pQueue->push_back("penny");
	checkTest("testQueueSimple #18", "penny", pQueue->pop_front());
	pQueue->push_back("nickel");
	checkTest("testQueueSimple #19", "nickel", pQueue->pop_front());
	pQueue->push_back("dime");
	checkTest("testQueueSimple #20", "dime", pQueue->pop_front());
	pQueue->push_back("quarter");
	checkTest("testQueueSimple #21", "quarter", pQueue->pop_front());
	pQueue->push_back("half dollar");
	checkTest("testQueueSimple #22", "half dollar", pQueue->pop_front());
	pQueue->push_back("silver dollar");
	checkTest("testQueueSimple #23", 1, pQueue->size());

	checkTest("testQueueSimple #24", "silver dollar", pQueue->pop_front());
	caughtError = "not caught";
	try {
		result = pQueue->pop_front();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testQueueSimple #25", "caught", caughtError);

	delete pQueue;

}

void pressAnyKeyToContinue() {
	cout << "******************************************************" << endl;
	cout << "Press any key to continue..." << endl;
	cout << "******************************************************" << endl;

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

	testStackSimple();
	pressAnyKeyToContinue();
	testQueueSimple();
	pressAnyKeyToContinue();

	return 0;
}