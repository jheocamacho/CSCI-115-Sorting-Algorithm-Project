// Jheovanny Camacho 109697217
// CSCI 115 Project 1
#include "Array.h"
#include "Array.cpp"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <Windows.h>

using namespace std;

int sizeSelector(char choice);
void selectionSort(int* A, int n);
void insertionSort(int* A, int n);
void bubbleSort(int* A, int n);
void merge(int a[], int leftBottom, int leftTop, int rightBottom, int rightTop);
void mergeSort(int A[], int left, int right);
int partition(int* A, int start, int end);
void quickSort(int* A, int left, int right);

int main()
{
    LARGE_INTEGER StartingTime, EndingTime, Frequency, ElapsedMicroseconds; // variables for holding timestamps
    QueryPerformanceFrequency(&Frequency);

	// initializing all input cases
	char sortSelection;
	char typeSelection;
	char sizeSelection;
	int* arr;       // pointer for array

	cout << "Welcome to the Sorting Algorithm Testbench" << endl;

	cout << "Select an sorting algorithm: " << endl;
	cout << "a) Selection Sort" << endl;
	cout << "b) Insertion Sort" << endl;
	cout << "c) Bubble Sort" << endl;
	cout << "d) Merge Sort" << endl;
	cout << "e) Quick Sort" << endl;
	cin >> sortSelection;
	cout << endl;

	cout << "Select a type of array: " << endl;
	cout << "a) Already Sorted" << endl;
	cout << "b) Reversed" << endl;
	cout << "c) Completely Shuffled" << endl;
	cout << "d) 10% Shuffled" << endl;
	cin >> typeSelection;
	cout << endl;

	cout << "Select an array size: " << endl;
	cout << "a) 10" << endl;
	cout << "b) 1000" << endl;
	cout << "c) 10000" << endl;
	cout << "d) 100000" << endl;
	cout << "e) 1000000" << endl;
	cin >> sizeSelection;
	cout << endl;

	int size = sizeSelector(sizeSelection); 		// size is a variable that contains the actual size of array, determined by the sizeSelector and sizeSelection
                                                    // sizeSelector will determine what size array to create given the choice (sizeSelection), and is assigned to size

    // the following will run this snippet of code 100 (unless specified otherwise) times and gather all elapsed times as well as a mean at the end
    int numberOfTests = 100; // adjustable to determine how many times we want to run the scenario

    double mean, accumulator; // accumulator will gather continuously add on each time then divided by 100 to get the mean
    int allTimes[numberOfTests]; // this array will keep every time as an element,
                       // and will be used to calculate the variance and ultimately the standard deviation

	for(int i = 0; i < numberOfTests; i++)
    {
        Array <int> A(size);  // Array class object, size variable determines the size of array created

        if      (typeSelection == 'A' || typeSelection == 'a') {arr = A.sortedArray(size);}     // this creates an array with size as its parameter, which is assigned to arr
        else if (typeSelection == 'B' || typeSelection == 'b') {arr = A.reverseArray(size);}
        else if (typeSelection == 'C' || typeSelection == 'c') {arr = A.randomArray(size);}
        else if (typeSelection == 'D' || typeSelection == 'd') {arr = A.sortaShuffled(size);}
        else {cout << "not valid. try again." << endl; return 0;}

        //cout << "Before" << endl;
        //A.displayArray(arr, size);					   // we first display the array using arr and the size

        // array will get sorted
        if      (sortSelection == 'A' || sortSelection == 'a')
                {
                    QueryPerformanceCounter(&StartingTime);
                    selectionSort(arr, size);
                    QueryPerformanceCounter(&EndingTime);
                }
        else if (sortSelection == 'B' || sortSelection == 'b')
                {
                    QueryPerformanceCounter(&StartingTime);
                    insertionSort(arr, size);
                    QueryPerformanceCounter(&EndingTime);
                }
        else if (sortSelection == 'C' || sortSelection == 'c')
                {
                    QueryPerformanceCounter(&StartingTime);
                    bubbleSort(arr, size);
                    QueryPerformanceCounter(&EndingTime);
                }
        else if (sortSelection == 'D' || sortSelection == 'd')
                {
                    QueryPerformanceCounter(&StartingTime);
                    mergeSort(arr, 0, size-1);
                    QueryPerformanceCounter(&EndingTime);
                }
        else if (sortSelection == 'E' || sortSelection == 'e')
                {
                    QueryPerformanceCounter(&StartingTime);
                    quickSort(arr, 0, size-1);
                    QueryPerformanceCounter(&EndingTime);
                }
        else {cout << "not valid. try again." << endl; return 0;}

        //cout << endl << "After" << endl;
        //A.displayArray(arr, size);					   	// show how array looks after sorting has finished

        // find elapsed time by subtracting starting time from ending time
        ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

        // now convert from ticks/ticks-per-second to microseconds
        ElapsedMicroseconds.QuadPart *= 1000000; // first convert to microseconds to avoid loss of precision
        ElapsedMicroseconds.QuadPart /= Frequency.QuadPart; // now divide by ticks-per-second
        cout << ElapsedMicroseconds.QuadPart << " microseconds" << endl; // print out total time that had elapsed in microseconds

        allTimes[i] = ElapsedMicroseconds.QuadPart;
        accumulator += ElapsedMicroseconds.QuadPart;
    }
    mean = accumulator/numberOfTests; //calculating mean
    cout << "Mean time was: " << fixed << setprecision(2) << mean << " microseconds" << endl;


    // calculating standard deviation
    double variance = 0.0;   // calculate variance by using the following three lines of code
    for(int i = 0; i < numberOfTests; i++)
        {variance += (allTimes[i] - mean) * (allTimes[i] - mean);} // find difference of each time from the mean time, then square it, then add onto the variance variable
    variance /= numberOfTests; // divide the average of those to find the variance
    double standardDeviation = sqrt(variance); // find standard deviation by calculating square root of variance

    cout << "Standard Deviation was: " << fixed << setprecision(2) << standardDeviation << " microseconds" << endl;

    // mean (and as a result, standard deviation) may sometimes run into the issue of integer overflow, repeating the experiment will eventually give the correct answer
	return 0;
}

int sizeSelector(char choice)	// used to determine a size of array based on user choice
{
	int n = 0;
	if      (choice == 'A' || choice == 'a') {n = 10;}
	else if (choice == 'B' || choice == 'b') {n = 1000;}
	else if (choice == 'C' || choice == 'c') {n = 10000;}
	else if (choice == 'D' || choice == 'd') {n = 100000;}
	else if (choice == 'E' || choice == 'e') {n = 1000000;}
	else cout << "nope. default to 0." << endl;

	return n;					// the result will be the input for the array generator functions
}

void selectionSort(int* A, int n)
{
	Array <int> Arr;
	int minValue; // store minimum value
	int minIndex;

	for (int i = 0; i < n; i++)
	{
		minValue = A[i];
		minIndex = i;

		for (int j = i; j < n; j++)
		{
			if (A[j] < minValue)
			{
				minValue = A[j];
				minIndex = j;
			}
		}

		if (minValue < A[i])
			Arr.swapArray(A, minIndex, i);
	}
}

void insertionSort(int* A, int n)
{
	Array <int> Arr;
	int j, value;

	for (int i = 1; i < n; i++)
	{
		value = A[i];
		j = i - 1;
		while (j >= 0 && value < A[j])
		{
			Arr.swapArray(A, j, j + 1);
			j--;
		}
	}
}

void bubbleSort(int* A, int n)
{
    Array <int> Arr;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < (n - 1); j++)
		{
			if (A[j] > A[j + 1])
				Arr.swapArray(A, j, j + 1);
		}
	}
}

void merge(int a[], int leftBottom, int leftTop, int rightBottom, int rightTop)
{
	int length = rightTop - leftBottom + 1;
	int temp[length];
	int left = leftBottom;
	int right = rightBottom;

	for (int i = 0; i < length; ++i)
	{
		if (left > leftTop)
			temp[i] = a[right++];
		else if (right > rightTop)
			temp[i] = a[left++];
		else if (a[left] <= a[right])
			temp[i] = a[left++];
		else
			temp[i] = a[right++];
	}

	for (int i = 0; i < length; ++i)
	{
		a[leftBottom++] = temp[i];
	}
}

void mergeSort(int A[], int left, int right)
{
	if (left >= right)
		return;
	else
	{
		int mid = (left + right) / 2;
		mergeSort(A, left, mid);
		mergeSort(A, mid + 1, right);
		merge(A, left, mid, mid + 1, right);
	}
}

int partition(int* A, int start, int end)
{
	Array <int> Arr;
	for (int i = start; i < end; i++)
	{
		if (A[i] <= A[end])
		{
			Arr.swapArray(A, i, start);
			start++;
		}
	}
	Arr.swapArray(A, start, end);
	return start;
}

void quickSort(int* A, int left, int right)
{
	if (left < right)
	{
		int pivot = partition(A, left, right);
		quickSort(A, left, pivot - 1);
		quickSort(A, pivot + 1, right);
	}
}
