#include "SomeThreadSort.h"

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

	//std::cout << "資料複製完成\n";

}

void StringCompare(std::string* list1, std::string* list2, const int size)
{
	bool equal = true;

	for (int i = 0; i < size; i++)
	{
		if (list1[i] != list2[i])
		{
			equal = false;
			std::cout << "no equal\n";
			break;
		}
	}

	if (equal == true)
		std::cout << "equal\n";
}

void project()
{
	srand(time(NULL));
	std::string* Data = new std::string[10000000];
	std::string* CopyData;
	int Datasize[5] = { 2000000,4000000,6000000,8000000,10000000 };
	double TimeStart, TimeEnd;
	double ProjectOneTime[10][5] = { 0 };

	create_string(Data, 0, 10000000);

	for (int n = 0; n < 5; n++)
	{
		int size = Datasize[n];
		CopyData = new std::string[size];

///////////////OpenMP///////////////////////////////////////////
		string_copy(Data, CopyData, size);
		TimeStart = clock();
		OpenMPReMergeSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[0][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		string_copy(Data, CopyData, size);
		TimeStart = clock();
		OpenMPIteMergeSort(CopyData, size - 1);
		TimeEnd = clock();
		ProjectOneTime[1][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		string_copy(Data, CopyData, size);
		TimeStart = clock();
		OpenMPReQuickSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[2][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		string_copy(Data, CopyData, size);
		TimeStart = clock();
		OpenMPIteQuickSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[3][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

/////////////////////////////Thread///////////////////////////////////////////////////////////////
		string_copy(Data, CopyData, size);
		TimeStart = clock();
		ThreadReMergeSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[4][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		string_copy(Data, CopyData, size);
		TimeStart = clock();
		ThreadIteMergeSort(CopyData, size - 1);
		TimeEnd = clock();
		ProjectOneTime[5][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		string_copy(Data, CopyData, size);
		TimeStart = clock();
		ThreadReQuickSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[6][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		string_copy(Data, CopyData, size);
		TimeStart = clock();
		ThreadIteQuickSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[7][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		///////////////////// One Thread /////////////////////////////////////
		string_copy(Data, CopyData, size);
		TimeStart = clock();
		ReMergeSort(CopyData, 0, size - 1);
		TimeEnd = clock();
		ProjectOneTime[8][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		string_copy(Data, CopyData, size);
		TimeStart = clock();
		IteMergeSort(CopyData, size - 1, 0);
		TimeEnd = clock();
		ProjectOneTime[9][n] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		delete[] CopyData;
	}
	for (int i = 0; i < 10; i++)
	{
		switch (i)
		{
		case 0:
			std::cout << "OpenMPReMergeSort:" << "\n";
			break;
		case 1:
			std::cout << "OpenMPIteMergeSort:" << "\n";
			break;
		case 2:
			std::cout << "OpenMPReQuickSort:" << "\n";
			break;
		case 3:
			std::cout << "OpenMPIteQuickSort:" << "\n";
			break;
		case 4:
			std::cout << "ThreadReMergeSort:" << "\n";
			break;
		case 5:
			std::cout << "ThreadIteMergeSort:" << "\n";
			break;
		case 6:
			std::cout << "ThreadReQuickSort:" << "\n";
			break;
		case 7:
			std::cout << "ThreadIteQuickSort:" << "\n";
			break;
		case 8:
			std::cout << "ReMergeSort:" << "\n";
			break;
		case 9:
			std::cout << "IteMergeSort:" << "\n";
			break;
		}
		for (int j = 0; j < 5; j++)
		{
			std::cout << "第" << j << "個sort time:" << ProjectOneTime[i][j]  << "\n";
		}
		std::cout << "\n";
	}
	delete[] Data;
}
