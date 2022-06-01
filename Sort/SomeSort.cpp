#include "SomeSort.h"

void create_string(std::string* list, int left, int n)
{
	std::cout << "資料創造中\n";
	for (int i = left; i < n; i++)
		for (int j = 0; j < 6; j++)
			list[i] += rand() % 26 + 97;

	std::cout << "資料創造完成\n";
}

void string_copy(std::string* original, std::string* copy, int size)
{
	for (int i = 0; i < size; i++)
		copy[i] = original[i];

	std::cout << "資料複製完成\n";

}
////////////////////////////////Data text///////////////////////////

void project_one()
{	
	srand(time(NULL));
	std::string* Data = new std::string[1200];     //120*10
	create_string(Data, 0, 1200);					//之後改多現成創造
	std::string* CopyData;
	int Datasize[6] = { 200,400,600,800,1000,1200 };
	double TimeStart, TimeEnd;
	double ProjectOneTime[9][6] = {0};

	for (int n = 0; n < 5; n++)
	{
		int size = Datasize[n];
		CopyData = new std::string[size];

		string_copy(Data, CopyData, size);
		TimeStart = clock();
		InsertionSort(CopyData, size);
		TimeEnd = clock();
		ProjectOneTime[0][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		string_copy(Data, CopyData, size);
		TimeStart = clock();
		SelectionSort(CopyData, size);
		TimeEnd = clock();
		ProjectOneTime[1][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		string_copy(Data, CopyData, size);
		TimeStart = clock();
		BubbleSort(CopyData, size);
		TimeEnd = clock();
		ProjectOneTime[2][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;
		
		
		string_copy(Data, CopyData, size);
		TimeStart = clock();
		ReMergeSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[3][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;
		
		
		string_copy(Data, CopyData, size);
		TimeStart = clock();
		IteMergeSort(CopyData, size - 1);
		TimeEnd = clock();
		ProjectOneTime[4][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;
		
		
		string_copy(Data, CopyData, size);
		TimeStart = clock();
		ReQuickSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[5][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;
		
		
		string_copy(Data, CopyData, size);
		TimeStart = clock();
		IteQuickSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[6][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		string_copy(Data, CopyData, size);
		TimeStart = clock();
		HeapSort(CopyData, size);
		TimeEnd = clock();
		ProjectOneTime[7][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		string_copy(Data, CopyData, size);
		TimeStart = clock();
		sort(CopyData, CopyData + size);
		TimeEnd = clock();
		ProjectOneTime[8][n] += (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;
	
		delete[] CopyData;
	}

	for (int i = 0; i < 9; i++)
	{
		switch (i)
		{
		case 0:
			std::cout << "InsertionSort:" << "\n";
			break;
		case 1:
			std::cout << "SelectionSort:" << "\n";
			break;
		case 2:
			std::cout << "BubbleSort:" << "\n";
			break;
		case 3:
			std::cout << "ReMergeSort:" << "\n";
			break;
		case 4:
			std::cout << "IteMergeSort:" << "\n";
			break;
		case 5:
			std::cout << "ReQuickSort:" << "\n";
			break;
		case 6:
			std::cout << "IteQuickSort:" << "\n";
			break;
		case 7:
			std::cout << "HeapSort:" << "\n";
			break;
		case 8:
			std::cout << "Built sort:" << "\n";
		}
		for (int j = 0; j < 6; j++)
		{
			std::cout << "第" << Datasize[j] << "個 time:" << ProjectOneTime[i][j] << "\n";
		}
		std::cout << "\n";
	}
		
		
	delete[] Data;
	Data = NULL;
	CopyData = NULL;
}

void project_two()
{
	srand(time(NULL));
	std::string* Data = new std::string[10000000];     
	std::string* CopyData;
	int Datasize[5] = { 2000000,4000000,6000000,8000000,10000000 };
	double TimeStart, TimeEnd;
	double ProjectOneTime[6][5] = { 0 };

	for (int round = 0; round < 50; round++)
	{
		if(round == 0)
			create_string(Data, 0, 10000000);					//之後改多現成創造
		else
		{
			Data = new std::string[10000000];
			create_string(Data, 0, 10000000);					//之後改多現成創造
		}
		for (int n = 0; n < 5; n++)
		{
			int size = Datasize[n];
			CopyData = new std::string[size];

			
			string_copy(Data, CopyData, size);
			TimeStart = clock();
			ReMergeSort(CopyData, 0, size - 1);
			TimeEnd = clock();
			ProjectOneTime[0][n] += (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


			string_copy(Data, CopyData, size);
			TimeStart = clock();
			IteMergeSort(CopyData, size - 1);
			TimeEnd = clock();
			ProjectOneTime[1][n] += (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


			string_copy(Data, CopyData, size);
			TimeStart = clock();
			ReQuickSort(CopyData, 0, size - 1);
			TimeEnd = clock();
			ProjectOneTime[2][n] += (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


			string_copy(Data, CopyData, size);
			TimeStart = clock();
			IteQuickSort(CopyData, 0, size - 1);
			TimeEnd = clock();
			ProjectOneTime[3][n] += (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


			string_copy(Data, CopyData, size);
			TimeStart = clock();
			HeapSort(CopyData, size);
			TimeEnd = clock();
			ProjectOneTime[4][n] += (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

			string_copy(Data, CopyData, size);
			TimeStart = clock();
			sort(CopyData, CopyData + size);
			TimeEnd = clock();
			ProjectOneTime[5][n] += (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

			delete[] CopyData;
		}

		std::cout << "第"<< round <<"次"<< "\n";
		delete[] Data;
	}
	
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			std::cout << "ReMergeSort:" << "\n";
			break;
		case 1:
			std::cout << "IteMergeSort:" << "\n";
			break;
		case 2:
			std::cout << "ReQuickSort:" << "\n";
			break;
		case 3:
			std::cout << "IteQuickSort:" << "\n";
			break;
		case 4:
			std::cout << "HeapSort:" << "\n";
			break;
		case 5:
			std::cout << "Built sort:" << "\n";
		}
		for (int j = 0; j < 5; j++)
		{
			std::cout << "第" << j << "個sort time:" << ProjectOneTime[i][j] / (double)50.0 << "\n";
		}
		std::cout << "\n";
	}
	Data = NULL;
	CopyData = NULL;
}
