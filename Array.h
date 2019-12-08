#ifndef ARRAY_H
#define ARRAY_H

template <class T>
class Array
{
public:
	Array();
	Array(int n);
	~Array();

	T* sortedArray(int n);
	T* reverseArray(int n);
	T* randomArray(int n);
	T* sortaShuffled(int n);
	void displayArray(T* A, int n);
	void swapArray(T* A, int i, int j);

private:
	T* elements;
	//int size;
};

#endif
