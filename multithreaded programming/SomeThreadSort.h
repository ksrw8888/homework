#ifndef SOMETHREADSORT_H
#define SOMETHREADSORT_H
#include<omp.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<thread>

#endif

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
void PrintArray(T* arr, const int size) {
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

template<class T>
void Merge(T* list, const int l, const int m, const int r)
{
	unsigned int i, j, k;
	unsigned int n1 = m - l + 1;
	unsigned int n2 = r - m;

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
void IteMergeSort(T* list, const int n, const int d)		///加上差在不破壞次數下給正確位置
{
	int current, left;

	for (current = 1; current <= n; current = 2 * current)
	{
		//#pragma omp parallel for               //加上這行是全部執行緒分配去跑
		for (left = 0; left < n; left += 2 * current)
		{
			int mid = min(left + current - 1 + d, n + d);

			int right = min(left + 2 * current - 1 + d, n + d);

			Merge(list, left + d, mid, right);
		}
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




/////////////// OpenMP ///////////////////////////////////////////////

template<class T>
void OpenMPReMergeSort(T* list, const int l, const int r)
{
	if (l < r)					//四執行緒
	{
		int m = l + (r - l) / 2;

		#pragma omp parallel sections
		{
		#pragma omp section
			ReMergeSort(list, l, m / 2);
		#pragma omp section
			ReMergeSort(list, m / 2 + 1, m);
		#pragma omp section
			ReMergeSort(list, m + 1, m + m / 2);
		#pragma omp section
			ReMergeSort(list, m + m / 2 + 1, r);
		}

		#pragma omp parallel sections
		{
		#pragma omp section
			Merge(list, l, m / 2, m);
		#pragma omp section
			Merge(list, m + 1, m + m / 2, r);
		}

		Merge(list, l, m, r);
	}

}

template<class T>
void OpenMPIteMergeSort(T* list, const int n)
{
	int m = (n + 1) / 4 - 1;
	int r = (n + 1) % 4;

	//目前是四執行緒
	#pragma omp parallel sections
	{	
		#pragma omp section
		{
			IteMergeSort(list, m, 0);
		}

		#pragma omp section
		{
			IteMergeSort(list, m, m + 1);
		}

		#pragma omp section
		{
			IteMergeSort(list, m, 2 * (m + 1));
		}
		#pragma omp section
		{
			IteMergeSort(list, m + r, 3 * (m + 1));
		}
	}

	if (r == 0 || r == 1)				//////////這邊R的餘數判斷分兩組 0、1 ，2、3因為後續又將M放大所以R也放大成0跟1兩組,
		m = ((n + 1) / 2);								/////////但原R還須用到所以不乘並將0、1、2、3分成兩組
		
	else
		m = ((n + 1) / 2) - 1;
		
	//目前是雙執行
	#pragma omp parallel sections
	{										
		#pragma omp section
		{
			Merge(list, 0, (m - 1) / 2, m - 1);
		}

		#pragma omp section
		{
			Merge(list, m, m + (n - r - m) / 2, n);
		}

	}

	Merge(list, 0, m - 1, n);
}

template<class T>
void OpenMPReQuickSort(T* list, const int left, const int right)
{
	if (left < right)
	{
		int p = Partition(list, left, right);
	
		int pl = Partition(list, left, p - 1);
		int pr = Partition(list, p + 1, right);
		

		#pragma omp parallel sections
		{
			#pragma omp section
			ReQuickSort(list, left, pl - 1);
			#pragma omp section
			ReQuickSort(list, pl + 1, p - 1);
			#pragma omp section
			ReQuickSort(list, p + 1, pr - 1);
			#pragma omp section
			ReQuickSort(list, pr + 1, right);
		}
	}
}

template<class T>
void OpenMPIteQuickSort(T* list, int left, int right)
{
	int p, pl, pr;

	p = Partition(list, left, right);

	pl = Partition(list, left, p - 1);   //left
	pr = Partition(list, p + 1, right); //right

	#pragma omp parallel sections
	{
		#pragma omp section
		IteQuickSort(list, pl + 1, p - 1); //left chain to right chain
		#pragma omp section
		IteQuickSort(list, left, pl - 1); //left chain to left chain
		#pragma omp section
		IteQuickSort(list, p - 1, pr - 1); //right chain to left chain
		#pragma omp section
		IteQuickSort(list, pr + 1, right); //right chain to right chain
	}


}


////////////// Thread ///////////////////////////////////////////////

template<class T>
void ThreadReMergeSort(T* list, const int l, const int r)
{

	if (l < r)					//四執行緒
	{
		int m = l + (r - l) / 2;

		std::thread t1, t2, t3, t4;

		//先拆成4調執行緒執行Recursive Mergesort
		t1 = std::thread(ReMergeSort<T>, list, l, m / 2);

		t2 = std::thread(ReMergeSort<T>, list, m / 2 + 1, m);

		t3 = std::thread(ReMergeSort<T>, list, m + 1, m + m / 2);

		t4 = std::thread(ReMergeSort<T>, list, m + m / 2 + 1, r);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		//再將4條的結果合併成兩條
		t1 = std::thread(Merge<T>, list, l, m / 2, m);

		t2 = std::thread(Merge<T>, list, m + 1, m + m / 2, r);

		t1.join();
		t2.join();

		//再將2條的結果合併
		Merge(list, l, m, r);
	}

}

template<class T>
void ThreadIteMergeSort(T* list, const int n)
{
	std::thread t1, t2, t3, t4;

	int m = (n + 1) / 4 - 1;
	int r = (n + 1) % 4;

	//先拆成4調執行緒執行Iterate Mergesort
	t1 = std::thread(IteMergeSort<T>, list, m, 0);

	t2 = std::thread(IteMergeSort<T>, list, m, m + 1);

	t3 = std::thread(IteMergeSort<T>, list, m, 2 * (m + 1));

	t4 = std::thread(IteMergeSort<T>, list, m + r, 3 * (m + 1));

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	if (r == 0 || r == 1)			//////////這邊R的餘數判斷分兩組 0、1 ，2、3因為後續又將M放大所以R也放大成0跟1兩組,
	{								/////////但原R還須用到所以不乘並將0、1、2、3分成兩組
		m = ((n + 1) / 2);
	}

	else
	{
		m = ((n + 1) / 2) - 1;
	}


	//再將4條的結果合併成兩條
	t1 = std::thread(Merge<T>, list, 0, (m - 1) / 2, m - 1);

	t2 = std::thread(Merge<T>, list, m, m + (n - r - m) / 2, n);

	t1.join();
	t2.join();
	//再將2條的結果合併
	Merge(list, 0, m - 1, n);
}

template<class T>
void ThreadReQuickSort(T* list, const int left, const int right)
{
	if (left < right)
	{
		std::thread t1, t2, t3, t4;
		int p = Partition(list, left, right);

		int pl = Partition(list, left, p - 1);
		int pr = Partition(list, p + 1, right);

		t1 = std::thread(ReQuickSort<T>, list, left, pl - 1);

		t2 = std::thread(ReQuickSort<T>, list, pl + 1, p - 1);

		t3 = std::thread(ReQuickSort<T>, list, p + 1, pr - 1);

		t4 = std::thread(ReQuickSort<T>, list, pr + 1, right);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}
}

template<class T>
void ThreadIteQuickSort(T* list, int left, int right)
{
	int p, pl, pr;

	p = Partition(list, left, right);

	pl = Partition(list, left, p - 1);   //left
	pr = Partition(list, p + 1, right); //right

	std::thread t1, t2, t3, t4;

	t1 = std::thread(IteQuickSort<T>, list, pl + 1, p - 1); //left chain to right chain

	t2 = std::thread(IteQuickSort<T>, list, left, pl - 1); //left chain to left chain

	t3 = std::thread(IteQuickSort<T>, list, p - 1, pr - 1); //right chain to left chain

	t4 = std::thread(IteQuickSort<T>, list, pr + 1, right); //right chain to right chain

	t1.join();
	t2.join();
	t3.join();
	t4.join();

}

////////////////////////////////////////////////////////////////////
void create_string(std::string* list, int left, int n);
void string_copy(std::string* original, std::string* copy, int size);
void StringCompare(std::string* list1, std::string* list2, const int size);

void project();

