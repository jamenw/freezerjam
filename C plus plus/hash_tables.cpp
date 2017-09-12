#include <iostream> 
#include <string> 
#include <sstream> 
#include <time.h> 
#include <stdlib.h> 
#include <map> 

//To prevent those using g++ from trying to use a library 
//they don't have 
#ifndef __GNUC__ 
#include <conio.h> 
#else 
#include <stdio.h> 
#endif 

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
std::map<void *, std::size_t> manageMemory::mapOfAllocations;



//-------------------------------------------- 
//A quick and dirty class that simulates a product object. 
//-------------------------------------------- 
class product : public manageMemory {
public:
	void setCost(int cost);
	void setName(const string&);
	string getName();
	int getCost();
	string getAllInfo();
private:
	string name;
	int cost;
};
void product::setCost(int cost) {
	this->cost = cost;
}
void product::setName(const string& name) {
	this->name = name;
}
string product::getName() {
	return name;
}
int product::getCost() {
	return cost;
}
string product::getAllInfo() {
	stringstream ss;
	ss << "Name: " << name << ", Cost: " << cost << endl;
	return ss.str();
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
bool checkEmpty(string testName, string whatItIs) {

	if (whatItIs != "") {
		cout << "Passed " << testName << ", the data was " << whatItIs << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "   No data was found! " << endl;
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
		cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
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


//******************************************** 
//TODO:  
// Put all of your code below here.   
// Your hashTable class does need two specific methods.  I've provided them for you. 
// Remember that each class needs to inherit manageMemory.  For example, class nodeType : public manageMemory 

//******************************************** 
template <typename T>
class Node : public manageMemory { //making the node class 
public:
	Node *forward; //decided to use a doubly linked list 
	Node *backward;
	string key;  //holds the key 
	T info;  //whatever info is stored 
};

template <typename T>
class LinkedList : public manageMemory { //my doubly linked list class 
public:
	LinkedList();  //create an empty linked list 
	~LinkedList();  //destroy all the nodes left 
	void insertKey(const string, const T&); //used to create a node with data 
	bool checkForKey(const string); //used to check if a key exists 
	void deleteMatchingKey(const string);   //deletes matching key 
	T& findAndReturnValue(const string);    //returns value of matching key 
	int getCount() const;   //gets count of all nodes in the list 

protected:
	Node<T> *first;   //first of the list 
	Node<T> *last;    //last of the list 
	int count;  //number of nodes in the list 
};

template <typename T>
class hashTable : public manageMemory {
public:
	hashTable();
	void add(const string, const T&);   //add our node to our linked list at the correct spot 
	T item(const string);   //return item with the key 
	T& operator[](const string);    //same as item 
	void remove(const string);  //deletes node 
	bool exists(const string);  //finds if node with key exists 
	int getWorstClump() const;  //to find worst clump 
	int getTotalCount() const;  //to get total count of nodes 

private:
	LinkedList<T> linkedListArray[1000];  //our array of linked lists 
	int hash(const string); //our private hash function 
};

template <typename T>
LinkedList<T>::LinkedList() { //our constructor creates an empty linked list 
	first = NULL;
	last = NULL;
	count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() { //our destructor will delete all nodes and reset our list to zero everything 
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
void LinkedList<T>::insertKey(const string key, const T& value) { //our insert node into the linked list function 
	Node<T> *temp = new Node<T>();  //create our new node 
	temp->info = value;  //set all the values here 
	temp->key = key;
	temp->forward = NULL;
	if (first == NULL) { //if our list is empty, do this 
		first = temp;
	}
	else { //else, add onto the end of the list 
		temp->backward = last;
		last->forward = temp;
	}
	last = temp;
	count++; //one more node was added 
}

template <typename T>
bool LinkedList<T>::checkForKey(const string key) {
	Node<T> *temp = first;    //make our checking node start at the beginning 
	while (temp != NULL) { //while it isn't at the end, keep looping 
		if (temp->key == key) { //if the key equals our node key, return true 
			return true;
		}
		else {
			temp = temp->forward; //else, let's keep moving 
		}
	}
	return false; //if we didn't find our key, return false 
}

template <typename T>
void LinkedList<T>::deleteMatchingKey(const string key) { //deleting nodes always has more work involved 
	Node<T> *temp = first;
	if (first == NULL) { //if list is empty, just return 
		return;
	}
	else if (first == last && first->key == key) { //if we have one node and it is our key, delete it 
		delete first;
		first = NULL;
		last = NULL;
		count = 0;
		return;
	}
	else {
		while (temp != NULL) { //while it isn't the end, let's loop 
			if (temp->key == key) { //if this is our node, break out of the loop 
				break;
			}
			else {
				temp = temp->forward; //just keep going through the list 
			}
		}
		if (temp->key == key && temp == first) { //if our node is at the front 
			first->forward->backward = NULL;
			first = first->forward;
		}
		else if (temp->key == key && temp == last) { //if our node is at the end 
			last->backward->forward = NULL;
			last = last->backward;
		}
		else if (temp->key == key) { //means our node is somewhere in between 
			temp->backward->forward = temp->forward;
			temp->forward->backward = temp->backward;
		}
		delete temp; //delete the node 
		count--;
	}
}

template <typename T>
T& LinkedList<T>::findAndReturnValue(const string key) {
	Node<T> *temp = first;
	while (temp != NULL) { //just looping here 
		if (temp->key == key) { //if our key was found, return the info of that key 
			return temp->info;
		}
		else {
			temp = temp->forward; //else, move forward 
		}
	}
	return temp->info; //if not found, we'll just return whatever our temp has 
}

template <typename T>
int LinkedList<T>::getCount() const{
	return this->count; //just return the count of our linked list 
}

template <typename T>
hashTable<T>::hashTable() { //it was needed to compile 
}

template <typename T>
void hashTable<T>::add(const string key, const T& value){ //call our hash function and then call our linked list code at the proper array bucket 
	int index = hash(key);
	linkedListArray[index].insertKey(key, value);
}

template <typename T>
T hashTable<T>::item(const string key) { //same for this one 
	int index = hash(key);
	return linkedListArray[index].findAndReturnValue(key);
}

template <typename T>
T& hashTable<T>::operator[](const string key) { //and this one 
	int index = hash(key);
	return linkedListArray[index].findAndReturnValue(key);
}

template <typename T>
void hashTable<T>::remove(const string key) { //and this one 
	int index = hash(key);
	linkedListArray[index].deleteMatchingKey(key);
}

template <typename T>
bool hashTable<T>::exists(const string key) { //and even this one 
	int index = hash(key);
	return linkedListArray[index].checkForKey(key);
}

template <typename T>
int hashTable<T>::getWorstClump() const{
	int count;
	int highest = 0;
	for (int i = 0; i < 1000; i++) {
		count = linkedListArray[i].getCount(); //change this to the name of your linked list array 
		//Also, your linked list needs a method called getCount()  
		//which returns the number of nodes in that linked list. 
		if (count > highest) {
			highest = count;
		}
	}
	return highest;
}

template <typename T>
int hashTable<T>::getTotalCount() const{
	int count;
	int sum = 0;
	for (int i = 0; i < 1000; i++) {
		count = linkedListArray[i].getCount(); //change this to the name of your linked list array. 
		//Also, your linked list needs a method called getCount()  
		//which returns the number of nodes in that linked list. 
		sum += count;
	}
	return sum;
}

template <typename T>
int hashTable<T>::hash(const string key) { //hash function that just does our math and returns our index for our array of linked lists 
	int counter = 0;
	int everyFourth = -2;
	for (size_t i = 0; i < key.length(); i++) {
		if (everyFourth != 0) {
			counter += key.at(i) * 21;
			counter += key.at(i) + 43;
			counter += key.at(i) - 65;
			counter += key.at(i) / 7;
			counter += key.at(i) * 34;
			counter += key.at(i) % 82;
			counter += key.at(i) * 21;
		} if (everyFourth != 1) {
			counter += key.at(i) * 234;
			counter += key.at(i) + 80;
			counter += key.at(i) - 34;
			counter += key.at(i) / 3;
			counter += key.at(i) * 89;
			counter += key.at(i) % 12;
			counter += key.at(i) * 91;
		} if (everyFourth != 2) {
			counter += key.at(i) * 67;
			counter += key.at(i) + 345;
			counter += key.at(i) - 1;
			counter += key.at(i) / 6;
			counter += key.at(i) * 3433;
			counter += key.at(i) % 68;
			counter += key.at(i) * 48;
		} if (everyFourth != 3) {
			counter += key.at(i) * 343;
			counter += key.at(i) + 123;
			counter += key.at(i) - 90;
			counter += key.at(i) / 4;
			counter += key.at(i) * 298;
			counter += key.at(i) % 91;
			counter += key.at(i) * 231;
		}
		if (everyFourth == 3) {
			everyFourth = -1;
		}
		else {
			everyFourth++;
		}
	}
	counter = counter % 1000;
	return counter;
}


//******************************************** 
// Do not add any of your own code after this point. 
//******************************************** 



//This helps with testing, do not modify. 
void testSimpleIntHash() {

	//Create a hashTable. We want this to be a hash table with int keys, string object values, 
	//And we also supply the hash function we want to use for integers.. 
	hashTable<string> myHash;

	//Test #1, add "Jazz" into our hash with a key of 6.  Try to retrieve it.   
	myHash.add("6", "Jazz");
	checkTest("testSimpleIntHash #1", "Jazz", myHash.item("6"));

	//Test #2, attempt to get the Jazz using the operator[] code. 
	checkTest("testSimpleIntHash #2", "Jazz", myHash["6"]);

	//Test #3, attempt to change the value at this location: 
	myHash["6"] = "Nuggets";
	checkTest("testSimpleIntHash #3", "Nuggets", myHash["6"]);

	//Test #4,  
	//See if we can find it 
	if (myHash.exists("6")) {
		checkTest("testSimpleIntHash #4", "", "");
	}
	else {
		checkTest("testSimpleIntHash #4", "This test should have found an item with key \"6\"", "This test did NOT find an item with key \"6\"");
	}

	//Test #5, see if we can find something that doesn't exist yet. 
	if (myHash.exists("1234")) {
		checkTest("testSimpleIntHash #5", "This test should NOT have found an item with key \"1234\".", "This test found an item with key \"1234\"");
	}
	else {
		checkTest("testSimpleIntHash #5", "", "");
	}

	//Test #6, removing it from the hash 
	myHash.remove("6");
	if (myHash.exists("6")) {
		checkTest("testSimpleIntHash #6", "This test should NOT have found an item with key \"6\".", "This test found an item with key \"6\"");
	}
	else {
		checkTest("testSimpleIntHash #6", "", "");
	}

	//Add more into the hash 
	myHash.add("13", "Lakers");
	myHash.add("25", "Bulls");
	myHash.add("101", "Pelicans");
	myHash.add("77", "Bucks");
	myHash.add("12", "Thunder");
	myHash.add("42", "Nets");
	myHash.add("97", "Timberwolves");
	myHash.add("123", "Bobcats");
	myHash.add("500", "Mavericks");

	//Attempt to retrieve some 
	checkTest("testSimpleIntHash #7", "Thunder", myHash.item("12"));
	checkTest("testSimpleIntHash #8", "Bucks", myHash.item("77"));
	checkTest("testSimpleIntHash #9", "Bobcats", myHash.item("123"));

	//Now count up how many are in there 
	checkTest("testSimpleIntHash #10", 9, myHash.getTotalCount());

	//Now just verify that they aren't clumping up badly. 
	int worst = 0;
	worst = myHash.getWorstClump();
	if (worst > 4) {
		cout << "Failed testSimpleIntHash #11!  There exists a clump of " << worst << " consecutive items, it shouldn't be worse than 4." << endl;
	}
	else {
		cout << "Passed testSimpleIntHash #11. Highest clumping is " << worst << "." << endl;
	}

	//Now go crazy and throw in 1000 more items. 
	int key = 0;
	stringstream out;
	for (int i = 0; i < 1000; i++){

		//this next part just helps create some variation in generated W#s... 
		if (i % 2 == 0) {
			key += 17;
		}
		else if (i % 3 == 0) {
			key += 23;
		}
		else if (i % 5 == 0) {
			key += 51;
		}
		else if (i % 7 == 0) {
			key += 13;
		}
		else {
			key += 71;
		}
		//convert an int to a string via help from the stringstream class 
		out.str("");
		out << key;
		string temp = out.str();

		myHash.add(temp, "a"); //Just add a bunch of letter a's 
	}

	//Make sure they all go in there.  We put in 9 manually, then we added in 1000 more.   
	checkTest("testSimpleIntHash #12", 1009, myHash.getTotalCount());

	worst = myHash.getWorstClump();
	if (worst > 10) {
		cout << "Failed testSimpleIntHash #13!  There exists a clump of " << worst << " consecutive items, it shouldn't be worse than 10." << endl;
	}
	else {
		cout << "Passed testSimpleIntHash #13. Highest clumping is " << worst << "." << endl;
	}

}


void testHashOfObjects() {

	//Create a hashTable. We want this to be a hash table with int keys, string object values, 
	//And we also supply the hash function we want to use for integers.. 

	hashTable<product> myHash;

	//Test #1, add in a studentObject.  Try to retrive it.   
	product tempProduct;
	tempProduct.setCost(5);
	tempProduct.setName("Silly string");
	myHash.add("12341-51231", tempProduct);
	checkTest("testHashOfObjects #1", "Silly string", myHash.item("12341-51231").getName());

	//Test #2, attempt to get the product using its ID code 
	checkTest("testHashOfObjects #2", "Silly string", myHash["12341-51231"].getName());

	//Test #3, see what happens if two products have the same ID code.  This should overwrite the former. 
	tempProduct.setCost(18);
	tempProduct.setName("Novelty foam hat");
	myHash["12341-51231"] = tempProduct;
	checkTest("testHashOfObjects #3", "Novelty foam hat", myHash["12341-51231"].getName());

	//Test #4,  
	//See if we can find it 
	if (myHash.exists("12341-51231")) {
		checkTest("testHashOfObjects #4", "", "");
	}
	else {
		checkTest("testHashOfObjects #4", "This test should have found an item with key 12341-51231", "This test did NOT find an item with key 12341-51231");
	}

	//Test #5, see if we can find something that doesn't exist yet. 
	if (myHash.exists("56756-75675")) {
		checkTest("testHashOfObjects #5", "This test should NOT have found an item with key 56756-75675.", "This test found an item with key56756-75675");
	}
	else {
		checkTest("testHashOfObjects #5", "", "");
	}

	//Test #6, removing it from the hash 
	myHash.remove("12341-51231");
	if (myHash.exists("12341-51231")) {
		checkTest("testHashOfObjects #6", "This test should NOT have found an item with key 12341-51231.", "This test found an item with key 12341-51231");
	}
	else {
		checkTest("testHashOfObjects #6", "", "");
	}



	//Now throw in 1000 more items. 
	int value = 0;
	string key;
	stringstream out;
	for (int i = 0; i < 1000; i++){
		//this next part just helps create some variation for our produce ID codes. 
		if (i % 2 == 0) {
			value += 107;
		}
		else if (i % 3 == 0) {
			value += 83;
		}
		else if (i % 5 == 0) {
			value += 47;
		}
		else if (i % 7 == 0) {
			value += 131;
		}
		else {
			value += 53;
		}
		key = "12345-";
		out.str("");
		if (value < 10000)
			key = key + "0";
		if (value < 1000)
			key = key + "0";
		if (value < 100)
			key = key + "0";
		if (value < 10)
			key = key + "0";
		out << value;
		string temp = out.str();
		if (temp.length() > 5) {
			temp = temp.substr(0, 5);
		}
		key = key + temp;
		//Whew, that took a while, but the W# is in key, and is ready to go 

		//Create the student record, and load in values. 
		tempProduct.setName("Acme product");
		tempProduct.setCost(rand() % 41);

		//Testing the hash table "add" method 
		myHash.add(key, tempProduct);
	}

	//Make sure one went in correctly.  Retrieve it. 
	checkEmpty("testHashOfObjects #7", myHash["12345-02112"].getAllInfo());

	//Make sure they all go in there. 
	checkTest("testHashOfObjects #8", 1000, myHash.getTotalCount());

	//Now test how good your int hash function is.   
	int worst = myHash.getWorstClump();
	if (worst > 15) {
		cout << "Failed testSimpleIntHash #9!  There exists a clump of " << worst << " consecutive items, it shouldn't be worse than 15." << endl;
	}
	else {
		cout << "Passed testSimpleIntHash #9. Highest clumping is " << worst << "." << endl;
	}
}


//This helps with testing, do not modify. 
void testHashofHashes() {

	//A rather complicated declaration, but it works! 
	hashTable< hashTable<int> > studentAssignments;
	hashTable<int> tempHash1;
	studentAssignments.add("Alice", tempHash1);

	hashTable<int> tempHash2;
	studentAssignments.add("Bob", tempHash2);

	hashTable<int> tempHash3;
	studentAssignments.add("Karl", tempHash3);

	//Give alice some assignment scores 
	studentAssignments["Alice"].add("1", 73);
	studentAssignments["Alice"].add("2", 65);
	studentAssignments["Alice"].add("4", 91);
	//Ensure it went in 
	checkTest("testHashofHashes #1", 65, studentAssignments["Alice"]["2"]);

	//And Bob 
	studentAssignments["Bob"].add("1", 90);
	studentAssignments["Bob"].add("3", 84);
	studentAssignments["Bob"].add("4", 99);

	//And Karl 
	studentAssignments["Karl"].add("1", 92);
	studentAssignments["Karl"].add("2", 92);
	studentAssignments["Karl"].add("3", 87);
	studentAssignments["Karl"].add("4", 10);

	//Now find the average of assignment 4 scores 
	int average = (studentAssignments["Alice"]["4"] + studentAssignments["Bob"]["4"] + studentAssignments["Karl"]["4"]) / 3;
	checkTest("testHashofHashes #2", 66, average);

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


int main(){

	//Each of these checks how many bytes you have used. 
	checkTestMemory("Memory Leak/Allocation Test #1", 0, manageMemory::getTotalSize());

	testSimpleIntHash();

	//Checking if you have any memory leaks... 
	checkTestMemory("Memory Leak/Allocation Test #2", 0, manageMemory::getTotalSize());

	testHashOfObjects();

	//Checking if you have any memory leaks... 
	checkTestMemory("Memory Leak/Allocation Test #3", 0, manageMemory::getTotalSize());

	testHashofHashes();

	//Checking if you have any memory leaks... 
	checkTestMemory("Memory Leak/Allocation Test #4", 0, manageMemory::getTotalSize());


	pressAnyKeyToContinue();

	return 0;
}