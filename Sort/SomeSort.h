#ifndef SOMESORT_H
#define SOMESORT_H
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include <algorithm>

template<class T>
const T& min(const T& x, const T& y) { return (x < y) ? x : y; };

template<class T>
void swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

template<class T>
void InsertionSort(T* list, const int size)
{
	for (int i = 1; i < size; i++)
	{
		T key = list[i];
		int j = i - 1;
		while (j >= 0 && key < list[j])
		{
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = key;
	}
}

template<class T>
void SelectionSort(T* list, const int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int mid = i;
		for (int j = i + 1; j < size; j++)
			if (list[mid] > list[j])
				mid = j;
		swap(list[i], list[mid]);
	}
}

template<class T>
void BubbleSort(T* list, const int size)
{
	int wall = 0;
	while (wall < size)
	{
		int cur = size - 1;
		while (cur > wall)
		{
			if (list[cur] < list[cur - 1])
				swap(list[cur], list[cur - 1]);
			cur--;
		}
		wall++;
	}
}

template<class T>
void Merge(T* list, const int l, const int m, const int r)
{
	long long int i, j, k;
	long long int n1 = m - l + 1;
	long long int n2 = r - m ;

	T* L = new T[n1];
	T* R = new T[n2];

	for (i = 0; i < n1; i++)
		L[i] = list[l + i];
	for (j = 0; j < n2; j++)
		R[j] = list[m + 1 + j];

	j = 0;
	i = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] < R[j])
		{
			list[k] = L[i];
			i++;
		}

		else
		{
			list[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		list[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		list[k] = R[j];
		j++;
		k++;
	}
	delete[] R;
	delete[] L;
}

template<class T>
void ReMergeSort(T* list, const int l, const int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		ReMergeSort(list, l, m);
		ReMergeSort(list, m + 1, r);
		Merge(list, l, m, r);
	}
}

template<class T>
void IteMergeSort(T* list, const int n)
{
	int current, left;

	for (current = 1; current <= n ; current = 2 * current)
	{
		for (left = 0; left < n ; left += 2 * current)
		{
			int mid = min(left + current - 1, n );

			int right = min(left + 2 * current - 1, n );

			Merge(list, left, mid, right);
		}
	}
}

template<class T>
void MaxHeapify(T* list, const int n, const int root)
{
	int largest = root;
	int left = 2 * root + 1;
	int right = 2 * root + 2;

	if (left < n && list[left] > list[largest])
		largest = left;
	if (right < n && list[right] > list[largest])
		largest = right;
	if (largest != root)
	{
		swap(list[root], list[largest]);
		MaxHeapify(list, n, largest);
	}
}

template<class T>
void HeapSort(T* list, const int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		MaxHeapify(list, n, i);
	for (int i = n - 1; i >= 1; i--)
	{
		swap(list[0], list[i]);
		MaxHeapify(list, i, 0);
	}
}

template<class T>
const int Partition(T* list, const int left, const int right)
{
	int i = left - 1;
	T pivot = list[right];

	for (int j = left; j <= right - 1; j++) {
		if (list[j] <= pivot) {
			i++;
			swap(list[i], list[j]);
		}
	}
	swap(list[i + 1], list[right]);
	return (i + 1);

}

template<class T>
void ReQuickSort(T* list, const int left, const int right)
{
	if (left < right)
	{
		int p = Partition(list, left, right);
		ReQuickSort(list, left, p - 1);
		ReQuickSort(list, p + 1, right);
	}
}

template<class T>
void IteQuickSort(T* list, int left, int right)
{
	int* stack = new int[right - left + 1];

	// initialize top of stack 
	int top = -1;

	// push initial values of l and h to stack 
	stack[++top] = left;
	stack[++top] = right;

	// Keep popping from stack while is not empty 
	while (top >= 0) {
		// Pop h and l 
		right = stack[top--];
		left = stack[top--];

		// Set pivot element at its correct position 
		// in sorted array 
		int p = Partition(list, left, right);

		// If there are elements on left side of pivot, 
		// then push left side to stack 
		if (p - 1 > left) {
			stack[++top] = left;
			stack[++top] = p - 1;
		}

		// If there are elements on right side of pivot, 
		// then push right side to stack 
		if (p + 1 < right) {
			stack[++top] = p + 1;
			stack[++top] = right;
		}
	}
	delete[] stack;
}

template<class T>
void PrintArray(T* arr, const int size) {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

/////////////////////////////////////////////////////////////////////////

void create_string(std::string* list, int left, int n);

void string_copy(std::string* list1, std::string* list2, int size);

void project_one();

void project_two();


#endif