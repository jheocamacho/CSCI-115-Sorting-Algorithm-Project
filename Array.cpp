#include <iostream>
#include <math.h>
#include "Array.h"

using namespace std;

template <class T>
Array<T>::Array()
{
	elements = nullptr;
}

template <class T>
Array<T>::Array(int n)
{
    //size = n;
	elements = new T[n];
}

template <class T>
Array<T>::~Array()
{
	//delete elements;
    delete [] elements;
}

template <class T>
T* Array<T>::sortedArray(int n)
{
	for (int i = 0; i < n; i++)
	{
		elements[i] = i;
	}
	return elements;
}

template <class T>
T* Array<T>::reverseArray(int n)
{
    int number = n;
	for (int i = 0; i < n; i++)
	{
		elements[i] = number;
		number--;
	}
	return elements;
}

template <class T>
T* Array<T>::randomArray(int n)
{
	for (int i = 0; i < n; i++)
	{
		elements[i] = rand() % 100;
	}
	return elements;
}

template <class T>
T* Array<T>::sortaShuffled(int n)
{
	int m;
	m = n * 0.10;		// 10% of size
	for (int i = 0; i < m; i++) // this will be shuffled
	{
		elements[i] = rand() % 100;
	}
	for (int i = m; i < n; i++) // the rest is ordered
	{
		elements[i] = i;
	}
	return elements;
}


template <class T>
void Array<T>::displayArray(T* A, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

template <class T>
void Array<T>::swapArray(T* A, int i, int j)
{
	int temp;
	temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}
