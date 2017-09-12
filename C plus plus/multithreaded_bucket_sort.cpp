#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread> //C++11 support!   Visual studio 2012+ users can use this if they want.
#include <mutex> 


//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using namespace std;

//*** Prototypes ***
void recQuickSort(unsigned long *arr, int first, int last);


//***************************************
//TIMING CODE
#ifndef _RCTIMER_H_
#define _RCTIMER_H_

// By Rolando Collantes
// Windows:     QueryPerformanceCounter()
// Mac:         mach_absolute_time()
// Linux:       clock_gettime()
// NOTE: it needs to be linked with librt on Linux.
// $ g++ -o out <sources> -lrt

// How to use it in code:
// 1: Create RCTimer object
// 2: Call start(); before the code to be timed.
// 3: Call stop(); after running the code.
// 4: Get the elapsed time with getElapsedSeconds(), getElapsedMilliseconds(), getElapsedMicroseconds()

/*
RCTimer* timer = new RCTimer();
timer->start();
// Do something
timer->stop();
cout << "Elapsed time is: " << timer->getElapsedMilliseconds() << " ms" << endl;
*/


#if defined(_WIN32) || defined(WIN32)
#define ONWINDOWS
#define BIGNUM ULONG64
#elif defined(__APPLE__) || defined(__MACH__)
#define ONMAC
#define BIGNUM uint64_t
#elif defined(unix) || defined(__unix) || defined (__unix__) // Includes Linux.
// Looks like Mac OS X doesn't define any of these ^^. Yay!
#define ONUNIX
#define BIGNUM uint64_t
#warning "Gotta link it with librt on Linux."
#warning "g++ -o out <sources> -lrt"
#endif

extern "C" { // They're C headers, but we're using them in a C++ program.
#if defined(ONWINDOWS)
#include <windows.h>
#elif defined(ONMAC)
	// Mac Time: https://developer.apple.com/library/mac/#qa/qa1398/_index.html  (#2)
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <stdint.h> // uint64_t (for nanoseconds)
#elif defined(ONUNIX)
#include <time.h>
#include <stdint.h> // uint64_t (for nanoseconds)
#endif
}

class RCTimer{
public:
	RCTimer();
	~RCTimer();
	void clear();
	void start();
	void stop();
	double getElapsedSeconds();
	double getElapsedMilliseconds();
	double getElapsedMicroseconds();
private:
#if defined(ONWINDOWS)
	LARGE_INTEGER begin;
	LARGE_INTEGER end;
	LARGE_INTEGER frequency;
	void setCurrentTime(LARGE_INTEGER&);
#elif defined(ONMAC)
	uint64_t begin;
	uint64_t end;
	mach_timebase_info_data_t sTimebaseInfo;
	void setCurrentTime(uint64_t&);
#elif defined(ONUNIX)
	timespec begin;
	timespec end;
	void setCurrentTime(timespec&);
#endif
	BIGNUM getElapsedNanoseconds();
};

RCTimer::RCTimer(){
#if defined(ONWINDOWS)
	QueryPerformanceFrequency(&this->frequency);
#elif defined(ONMAC)
	mach_timebase_info(&this->sTimebaseInfo);
#endif
	this->clear();
}
RCTimer::~RCTimer(){
}

void RCTimer::clear(){
#if defined(ONWINDOWS)
	this->begin.QuadPart = 0;
	this->end.QuadPart = 0;
#elif defined(ONMAC)
	this->begin = 0;
	this->end = 0;
#elif defined(ONUNIX)
	this->begin.tv_sec = 0;
	this->begin.tv_nsec = 0;
	this->end.tv_sec = 0;
	this->end.tv_nsec = 0;
#endif
}

void RCTimer::start(){
	setCurrentTime(this->begin);
}

void RCTimer::stop(){
	setCurrentTime(this->end);
}

double RCTimer::getElapsedSeconds(){
	return ((double)this->getElapsedMilliseconds() / 1000.0);
}

double RCTimer::getElapsedMilliseconds(){
	return ((double)this->getElapsedMicroseconds() / 1000.0);
}

double RCTimer::getElapsedMicroseconds(){
	return ((double)this->getElapsedNanoseconds() / 1000.0);
}

BIGNUM RCTimer::getElapsedNanoseconds(){
	BIGNUM elapsedNano;
#if defined(ONWINDOWS)
	elapsedNano = (double)(end.QuadPart - begin.QuadPart) / (double)frequency.QuadPart * 1000000000;
#elif defined(ONMAC)
	elapsedNano = (end - begin) * this->sTimebaseInfo.numer / this->sTimebaseInfo.denom;
#elif defined(ONUNIX)
	elapsedNano = (end.tv_sec - begin.tv_sec) * 1000000000;
	elapsedNano += (end.tv_nsec - begin.tv_nsec);
#endif
	return elapsedNano;
}

#if defined(ONWINDOWS)
void RCTimer::setCurrentTime(LARGE_INTEGER& t){
	QueryPerformanceCounter(&t);
}

#elif defined(ONMAC)
void RCTimer::setCurrentTime(uint64_t& t){
	t = mach_absolute_time();
}

#elif defined(ONUNIX)
void RCTimer::setCurrentTime(timespec& t){
	clock_gettime(CLOCK_MONOTONIC_RAW, &t);
}
#endif
#endif // _RCTIMER_H_
//END OF TIMING CODE
//***************************************



class Buckets{
public:
	Buckets(int listSize, int numBuckets);
	~Buckets();
	void addItem(int bucket, unsigned long item);
	int getNumBuckets();
	int getNumItemsInABucket(int bucket);
	unsigned long * getBucketArray(int bucket);
	void copyBucketToAnotherArray(int bucket, unsigned long * destinationArray, int destinationArrayOffsetIndex);
	void appendSmallBucketIntoBiggerBucket(int bucketNumber, Buckets& smallBucket);
	void printAllBuckets();

private:
	unsigned long **buckets;
	int *itemCounter;
	int bucketSize;
	int numBuckets;
	//TODO: //For the assignment, you need an array of these mutexes.  Comment this back in to get started.
	mutex *mutexes;
};


//***GLOBAL VARIABLES***
unsigned long *list;
int listSize;
int numBuckets;
int numThreads;
Buckets *globalBuckets;


//*** Provide methods for the bucket class ***
Buckets::Buckets(int listSize, int numBuckets) {

	//Each bucket should be as bg as roughly the size of the list divided by number of buckets.
	//But some buckets will be bigger than others, so give an extra room.
	this->numBuckets = numBuckets;
	//Worst case scenario is that every value falls into one bucket.  Assume the worst case could 
	//happen and make sure each bucket could handle that much data.
	bucketSize = listSize;

	buckets = new unsigned long*[numBuckets];
	for (int i = 0; i < numBuckets; i++) {
		//printf("Requsting %d items for this bucket\n", listSize);
		buckets[i] = new unsigned long[bucketSize];
	}

	itemCounter = new int[numBuckets];
	for (int i = 0; i < numBuckets; i++) {
		itemCounter[i] = 0;
	}

	//TODO: Create an array of mutexes
	mutexes = new mutex[numBuckets];
	//for (int i = 0; i < numBuckets; i++)  {
	//	mutexes = new mutex[bucketSize];  
	//}

}

Buckets::~Buckets() {
	for (int i = 0; i < numBuckets; i++) {
		delete[] buckets[i];
	}
	delete[] buckets;
	delete[] itemCounter;
	//TODO: Make sure you deallocate these if you created them.
	delete[] mutexes;
}

void Buckets::addItem(int bucket, unsigned long item) {
	//Pass in a bucket #, and the data, and it assigns that data to the bucket.

	buckets[bucket][itemCounter[bucket]] = item;
	itemCounter[bucket]++;
}

int Buckets::getNumBuckets() {
	return numBuckets;
}

int Buckets::getNumItemsInABucket(int bucket) {
	//You pass in the bucket #, it returns how many items that bucket contains.

	return itemCounter[bucket];
}

void Buckets::printAllBuckets() {
	//Displays the contents of all buckets to the screen.

	printf("******\n");
	for (int i = 0; i < numBuckets; i++) {
		printf("Bucket number %d\n", i);
		for (int j = 0; j < itemCounter[i]; j++) {
			//cout << buckets[i][j] << " ";
			printf("%08X ", buckets[i][j]);

		}
		printf("\n");
	}
	printf("\n");
}

unsigned long * Buckets::getBucketArray(int bucket) {
	//You pass in the bucket #, it returns the array that contains the bucket's data.

	return buckets[bucket];
}

void Buckets::copyBucketToAnotherArray(int bucket, unsigned long * destinationArray, int destinationArrayOffsetIndex) {
	//Copies a bucket to an array.  You pass in the bucket #, the array, and the starting index (offset) or the array you are copying to
	//This then copies that bucket # into that array starting at that index (offset).

	for (int j = 0; j < itemCounter[bucket]; j++) {
		destinationArray[destinationArrayOffsetIndex + j] = buckets[bucket][j];
	}

}

void Buckets::appendSmallBucketIntoBiggerBucket(int bucket, Buckets& smallBucket) {
	//Copies a single small bucket into a single large bucket.  It does NOT copy all small buckets into corresponding large buckets.
	//Parameters are the bucket # to copy between, and the small buckets object.

	//TODO: Wait until the mutex lets us continue
	//.lock
	mutexes[bucket].lock();


	unsigned long * smallBucketArray = smallBucket.getBucketArray(bucket);
	//printf("Copying %d items between bucket %d\n", getNumItemsInABucket(bucket), bucket);
	for (int i = 0; i < smallBucket.getNumItemsInABucket(bucket); i++) {
		//printf("Copying %8X at index %d from small into big between bucket %d\n", smallBucketArray[i], i, bucket);
		addItem(bucket, smallBucketArray[i]);
	}

	//TODO: Release the mutex.
	//.unlock
	mutexes[bucket].unlock();

}




//***Functions that help our bucket sort work.***
void printList() {
	for (int i = 0; i < listSize; i++) {
		//cout << list[i] << " ";
		printf("%08X ", list[i]);
	}
}

void createList() {

	list = new unsigned long[listSize];

	//generate random numbers
	srand(time(NULL));

	unsigned long num1;
	unsigned long num2;
	unsigned long num3;

	//generates 32 bit numbers
	for (int i = 0; i < listSize; i++) {
		//Make 15 bit numbers.  On Windows they're already 15 bit.
		//But in case the rand() gives us bigger random numbers, lets just make
		//everything 15 bit by only preserving the last 15 bits.  Then work with
		//what we've got and combine it back into a 32 bit number.
		num1 = rand() & 0x00007FFF;
		num2 = rand() & 0x00007FFF;
		num3 = rand() & 0x00007FFF;

		//shift num1 over 15 bits
		num1 = num1 << 15;
		//make a 30 bit number
		num1 = num1 | num2;

		//get two more bits
		num3 = num3 << 30;
		//make it a 32 bit number
		list[i] = num3 | num1;

	}
}

void placeIntoBuckets(int threadID) {

	//TODO: Compute how big these thread buckets should be.
	//If each thread is working with listSize / numBuckets amount of data, then...
	int threadBucketsSizes = listSize / numBuckets;   // 250000 = 1M / 4

	//TODO: Create some individual buckets or these threads.  The first argument specifies how big
	//each our sublist is.  The second specifies how many buckets we want for this sublist.  
	Buckets threadBuckets(threadBucketsSizes, numBuckets);

	//TODO: Figure out where we start from.  Use threadID and sublistSize to get this index.

	//int listStartIndex = threadID * threadBucketsSizes;

	int listStartIndex = listSize / numBuckets * threadID;
	//int startingIndex = arrSize / numThreads * threadID;

	//TODO:Figure out the index we compute to.  We go sublistSize indexes beyond listStartIndex 
	//int listEndIndex = listStartIndex + listSize;  //?????????????????

	int listEndIndex = listSize / numBuckets * (threadID + 1);
	//int listEndIndex = threadBucketsSizes / numBuckets * (threadID + 1);




	//printf("In thread %d, starting at: %d ending at: %d\n", threadID, listStartIndex, listEndIndex);
	int bucketNumber = 0;
	//TODO: Loop over just the sublist we are in.  Not over the entire thing.  Make the appropriate change.
	for (int i = listStartIndex; i < listEndIndex; i++) {

		//Do some creative work with bit shifting to determine which bucket it should go in.
		//This will only work with 1, 2, 4, 8, or 16 buckets.  
		if (numBuckets == 1) {
			bucketNumber = 0;
		}
		else if (numBuckets == 2) {
			bucketNumber = (list[i] & 0x80000000) >> 31; //preserve 1 bit, shift it to the right
		}
		else if (numBuckets == 4) {
			bucketNumber = (list[i] & 0xC0000000) >> 30; //preserve 2 bits, shift them to the right
		}
		else if (numBuckets == 8) {
			bucketNumber = (list[i] & 0xE0000000) >> 29; //preserve 3 bits, shift them to the right
		}
		else if (numBuckets == 16) {
			bucketNumber = (list[i] & 0xF0000000) >> 28; //preserve 4 bits, shift them to the right
		}

		//TODO: Instead of writing to a global bucket, we need to add to thread bucket.
		threadBuckets.addItem(bucketNumber, list[i]);
		//addItem(int bucket, unsigned long item)

	}

	//TODO: Now write the threadBuckets to the globalBuckets.

	for (int i = 0; i < numBuckets; i++)  {
		globalBuckets->appendSmallBucketIntoBiggerBucket(i, threadBuckets);
	}
}


void sortEachBucket(int threadID) {


	int bucketNumber = threadID;

	//printf("In thread %d, starting quicksort for my bucket.  My bucket is %d in size\n", threadID, globalBuckets->getNumItemsInABucket(bucketNumber));
	//TODO: Instead of looping over every bucket, each thread gets its own bucket, so no loop necessary.
	//for (int bucketNumber = 0; bucketNumber < numBuckets; bucketNumber++) {
	//Call the Qucksort algorithm.  Hand it the array, and the start index and end index for all the items we want to sort.
	recQuickSort(globalBuckets->getBucketArray(bucketNumber), 0, globalBuckets->getNumItemsInABucket(bucketNumber) - 1);
	//}
	//printf("In thread %d, finished quicksort for my bucket.  My bucket is %d in size\n", threadID, globalBuckets->getNumItemsInABucket(bucketNumber));
}


void combineBuckets(int threadID) {

	//TODO: Each thread has a bucket.  Each thread needs to write that bucket back into the original list array.
	//To do so,   each thread needs to know at what index in list to start writing to. Compute that value and store it in listIndex.
	int listIndex = 0;
	for (int i = 0; i < threadID; i++){			// add up the varying sizes of items within each bucket
		listIndex = listIndex + (globalBuckets->getNumItemsInABucket(i));

	}


	//printf("In thread %d, preparing to merge starting from this index in list: %d\n", threadID, listIndex);

	//TODO: Since each thread has a bucket, we only need to call copyBucketToAnotherArray() once. Make sure it sends copies the right
	//bucket to list starting at the right listIndex.
	//int listIndex = 0;
	//for (int bucketIndex = 0; bucketIndex < globalBuckets->getNumBuckets(); bucketIndex++) {
	globalBuckets->copyBucketToAnotherArray(threadID, list, listIndex);
	//listIndex += globalBuckets->getNumItemsInABucket(threadID);
	//}

	//printf("In thread %d, preparing to merge starting from this index in list: %d\n", threadID, listIndex);


}


void bucketSort() {

	//All of your multithreaded code happens here.  Take the multithread example I gave earlier, and look
	//at the code found in main().  Similar code will end up here.

	thread* threads = new thread[numThreads];

	//TODO: Create numThreads threads, each thread calls placeIntoBuckets.  
	//placeIntoBuckets(0);
	//totalCount = 0;

	for (int i = 0; i < numThreads; i++) {
		threads[i] = thread(placeIntoBuckets, i);
	}

	//TODO: Have the master thread wait until all prior threads have processed. 
	for (int i = 0; i < numThreads; i++) {
		threads[i].join();
	}

	//TODO: Each thread calls sortEachBucket.  
	//sortEachBucket(0);
	//totalCount = 0;

	for (int i = 0; i < numThreads; i++) {
		threads[i] = thread(sortEachBucket, i);
	}

	//TODO: Have the master thread wait until all prior threads have processed.  
	for (int i = 0; i < numThreads; i++) {
		threads[i].join();
	}

	//TODO: Each thread calls combineBuckets. 
	//combineBuckets(0);
	//totalCount = 0;

	for (int i = 0; i < numThreads; i++) {
		threads[i] = thread(combineBuckets, i);
	}

	//TODO: Have the master thread wait until all prior threads have processed.  
	for (int i = 0; i < numThreads; i++) {
		threads[i].join();
	}


	delete[] threads;

}


void swap(unsigned long *arr, int first, int second) {

	unsigned long temp;

	temp = arr[first];
	arr[first] = arr[second];
	arr[second] = temp;
}


int partition(unsigned long *arr, int first, int last) {
	unsigned long pivot;
	int index, smallIndex;

	//Take the middle value as the pivot.
	swap(arr, first, (first + last) / 2);
	pivot = arr[first];
	smallIndex = first;
	for (index = first + 1; index <= last; index++) {
		if (arr[index] < pivot) {
			smallIndex++;
			swap(arr, smallIndex, index);
		}
	}

	//Move pivot into the sorted location
	swap(arr, first, smallIndex);

	//Tell where the pivot is
	return smallIndex;

}


void recQuickSort(unsigned long *arr, int first, int last) {

	if (first < last) {
		//Get this sublist into two other sublists, one smaller and one bigger
		int pivotLocation = partition(arr, first, last);
		recQuickSort(arr, first, pivotLocation - 1);
		recQuickSort(arr, pivotLocation + 1, last);
	}
}

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

int main() {



	//Set the listSize, numBuckets, and numThreads global variables.  
	listSize = 100;
	RCTimer timer;


	numBuckets = 2;
	numThreads = 2;
	list = new unsigned long[listSize];

	createList();
	globalBuckets = new Buckets(listSize, numBuckets);
	printf("\nStarting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	printf("Displaying the unsorted list array:\n");
	printList(); //useful for debugging small amounts of numbers.  
	pressAnyKeyToContinue();
	bucketSort();
	printf("Displaying each bucket's contents: \n");
	globalBuckets->printAllBuckets();
	pressAnyKeyToContinue();
	printf("Displaying what is hopefully a sorted array: \n");
	printList(); //See if it's all sorted.
	pressAnyKeyToContinue();
	delete globalBuckets;
	delete[] list;


	//Now lets try 4 threads
	numBuckets = 4;
	numThreads = 4;
	list = new unsigned long[listSize];

	createList();
	printf("\nStarting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	globalBuckets = new Buckets(listSize, numBuckets);
	printf("Displaying the unsorted list array:\n");
	printList(); //useful for debugging small amounts of numbers.  
	pressAnyKeyToContinue();
	bucketSort();
	printf("Displaying each bucket's contents: \n");
	globalBuckets->printAllBuckets();
	pressAnyKeyToContinue();
	printf("Displaying what is hopefully a sorted array: \n");
	printList(); //See if it's all sorted.
	pressAnyKeyToContinue();
	delete globalBuckets;
	delete[] list;

	printf("\nFor timing purposes, please make sure all printf statements are commented out\n");
	pressAnyKeyToContinue();

	//Now lets up the values and try various thread sizes
	listSize = 4000000;
	numBuckets = 1;
	numThreads = 1;
	list = new unsigned long[listSize];
	createList();
	globalBuckets = new Buckets(listSize, numBuckets);
	printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d, this is effectively a quick sort\n", listSize, numBuckets, numThreads);
	timer.clear();
	timer.start();
	bucketSort();
	timer.stop();
	printf("Finished bucket sort in %1.3lf milliseconds\n", timer.getElapsedMilliseconds());
	delete globalBuckets;
	delete[] list;


	listSize = 4000000;
	numBuckets = 2;
	numThreads = 2;
	list = new unsigned long[listSize];
	createList();
	globalBuckets = new Buckets(listSize, numBuckets);
	printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	timer.clear();
	timer.start();
	bucketSort();
	timer.stop();
	printf("Finished bucket sort in %1.3lf milliseconds\n", timer.getElapsedMilliseconds());
	delete globalBuckets;
	delete[] list;

	numBuckets = 4;
	numThreads = 4;
	list = new unsigned long[listSize];
	createList();
	globalBuckets = new Buckets(listSize, numBuckets);
	printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	timer.clear();
	timer.start();
	bucketSort();
	timer.stop();
	printf("Finished bucket sort in %1.3lf milliseconds\n", timer.getElapsedMilliseconds());
	delete globalBuckets;
	delete[] list;

	numBuckets = 8;
	numThreads = 8;
	list = new unsigned long[listSize];
	createList();
	globalBuckets = new Buckets(listSize, numBuckets);
	printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	timer.clear();
	timer.start();
	bucketSort();
	timer.stop();
	printf("Finished bucket sort in %1.3lf milliseconds\n", timer.getElapsedMilliseconds());
	delete globalBuckets;
	delete[] list;

	numBuckets = 16;
	numThreads = 16;
	list = new unsigned long[listSize];
	createList();
	globalBuckets = new Buckets(listSize, numBuckets);
	printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	timer.clear();
	timer.start();
	bucketSort();
	timer.stop();
	printf("Finished bucket sort in %1.3lf milliseconds\n", timer.getElapsedMilliseconds());
	delete globalBuckets;
	delete[] list;




	pressAnyKeyToContinue();
	return 0;
}