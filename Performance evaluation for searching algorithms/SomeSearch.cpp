#include "SomeSearch.h"

//////binary search tree 定義//////////////////
template<class T>
void BST<T>::createBST(const T* data, const int datasize)
{
	if (root != NULL)
	{
		std::cout << "BST has been created\n";
		return;
	}
	else
	{
		root = new BSTNode<T>(data[0]);
		for (int i = 1; i < datasize; i++)
			Insert(root, data[i]);
	}

	return;
}


template<class T>
BSTNode<T>* BST<T>::Insert(BSTNode<T>* root, const T data) {
	if (root == NULL)
		root = new BSTNode<T>(data);
	else if (data < root->data)
		root->leftchild = Insert(root->leftchild, data);
	else if (data > root->data)
		root->rightchild = Insert(root->rightchild, data);
	//data == root->data 跳出,使資料不重複
	return root;
}

template<class T>
bool BST<T>::Search(BSTNode<T>* root, const T key)
{
	if (root == NULL)
		return false;
	else if (key == root->data)
		return true;
	else if (key < root->data)
		return Search(root->leftchild, key);
	else // if(key > root -> data)
		return Search(root->rightchild, key);
}

template<class T>
void BST<T>::Visit(BSTNode<T>* root)
{
	std::cout << root->data << " ";
}

template<class T>
void BST<T>::PreOrder(BSTNode<T>* root)
{
	if (root != NULL) {
		Visit(root);
		PreOrder(root->leftchild);
		PreOrder(root->rightchild);
	}
}

template<class T>
void BST<T>::DeleteBST(BSTNode<T>* root)
{
	////利用後序法
	if (root != NULL) {
		DeleteBST(root->leftchild);
		DeleteBST(root->rightchild);
		delete root;
	}
}

template<class T>
bool BST<T>::Search(const T key)
{
	return Search(root, key);
}


/////////Hash with chain/////////////////////////
HTNode<std::string>::HTNode() {
	//string初質不能為空,會出錯
	data.clear();
	next = NULL;
}

template<class T>
void HashChain<T>::Insert(const T data, const int HashNum)
{
	HTNode<T>* temp = new HTNode<T>(data);

	temp->next = first[HashNum].next;
	first[HashNum].next = temp;

}

template<class T>
bool HashChain<T>::IsInChain(const T key, const int HashNum)
{
	HTNode<T>* temp = first[HashNum].next;
	while (temp) {
		if (key == temp->data)
			return true;
		else
			temp = temp->next;
	}

	return false;
}

template<class T>
void HashChain<T>::CreateHT(const T* data, const int datasize, const int HTsize)
{
	first = new HTNode<T>[HTsize];
	HTSize = HTsize;

	for (int i = 0; i < datasize; i++)
	{
		int hashnum = FindHashNumber(data[i], HTsize);
		bool check = IsInChain(data[i], hashnum);
		if (!check)  //false is not data in chain
			Insert(data[i], hashnum);
	}
}

template<class T>
void HashChain<T>::OutputChain(const int n)
{
	if (n >= HTSize)
	{
		std::cout << "Hash Table size exceed max size \n";
		return;
	}
	else
	{
		HTNode<T>* temp = first[n].next;

		std::cout << "[ " << n << " ] :";
		while (temp)
		{
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << "\n";
	}
}

template<class T>
void HashChain<T>::OutputHT()
{
	for (int i = 0; i < HTSize; i++)
	{
		OutputChain(i);
	}
}

template<class T>
void HashChain<T>::DeleteChain(const int n)
{
	if (n >= HTSize)
	{
		std::cout << "Hash Table size exceed max size \n";
		return;
	}
	else
	{
		HTNode<T>* temp = first[n].next;
		HTNode<T>* current;
		while (temp)
		{
			current = temp->next;
			delete temp;
			temp = current;
		}
	}
}

template<class T>
void HashChain<T>::DeleteHT()
{
	for (int i = 0; i < HTSize; i++)
		DeleteChain(i);

	delete[] first;
}

/////////////DataCreate///////////////////////////////////////////////////////

void create_string(std::string* list, int n)
{
	std::cout << "資料創造中\n";
	for (int i = 0; i < n; i++)
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

//////////////////////////////////Searching///////////////////////////////////////

void Searching()
{
	srand(time(NULL));

	int DataSize[5] = {2000000,4000000,6000000,8000000,10000000}, SearchingData = 10000000;
	double TimeStart, TimeEnd;
	double RunTime[5][6];
	double ConstructingTime[5][6];

	std::string* Searching = new std::string[SearchingData];
	create_string(Searching, SearchingData);


	for (int n = 0; n < 5; n++)
	{
		std::string* str = new std::string[DataSize[n]];
		
		std::string* copy = new std::string[DataSize[n]];

		create_string(str, DataSize[n]);

		//////  IterativeBinarySearch  ///////////////////////////////
		string_copy(str, copy, DataSize[n]);
		TimeStart = clock();
		sort(copy, copy + DataSize[n]);
		TimeEnd = clock();
		ConstructingTime[n][0] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		TimeStart = clock();
		for (int i = 0; i < SearchingData; i++)
		{
			IteBinarySearch(copy, DataSize[n], Searching[i]);

		}
		TimeEnd = clock();
		RunTime[n][0] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		////////  RecursiveBinarySearch  /////////////////////////////
		string_copy(str, copy, DataSize[n]);
		TimeStart = clock();
		sort(copy, copy + DataSize[n]);
		TimeEnd = clock();
		ConstructingTime[n][1] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		TimeStart = clock();
		for (int i = 0; i < SearchingData; i++)
		{
			ReBinarySearch(copy, 0, DataSize[n] - 1, Searching[i]);
		}
		TimeEnd = clock();
		RunTime[n][1] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		//////  BST  ///////////////////////////////////////////////////////
		string_copy(str, copy, DataSize[n]);
		BST<std::string>* BSTRoot = new BST<std::string>;

		TimeStart = clock();
		BSTRoot->createBST(copy, DataSize[n]);
		TimeEnd = clock();
		ConstructingTime[n][2] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		TimeStart = clock();
		for (int i = 0; i < SearchingData; i++)
		{
			BSTRoot->Search(Searching[i]);
		}

		TimeEnd = clock();
		RunTime[n][2] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		delete BSTRoot;

		//////  HT  ///////////////////////////////////////////////////////
		string_copy(str, copy, DataSize[n]);
		int HTlength = int(DataSize[n] * 2);
		HashChain<std::string>* HT = new HashChain<std::string>;
		TimeStart = clock();
		HT->CreateHT(copy, DataSize[n], HTlength);
		TimeEnd = clock();
		ConstructingTime[n][3] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		TimeStart = clock();
		for (int i = 0; i < SearchingData; i++)
		{
			HT->IsInChain(Searching[i], FindHashNumber(Searching[i], HTlength));
		}
		TimeEnd = clock();
		RunTime[n][3] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		delete HT;

		////////// STL map ///////////////////////////////////
		string_copy(str, copy, DataSize[n]);
		std::map<std::string, int> BKT;
		typename std::map<std::string, int>::iterator iter;

		TimeStart = clock();
		CreateMap<std::string>(BKT, copy, DataSize[n]);
		TimeEnd = clock();
		ConstructingTime[n][4] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		TimeStart = clock();
		for (int i = 0; i < SearchingData; i++) {
			iter = BKT.find(Searching[i]);
			//if (iter != BKT.end())
		}
		TimeEnd = clock();
		RunTime[n][4] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		BKT.clear();

		////////// STL UNMap ////////////////////////////////
		string_copy(str, copy, DataSize[n]);
		std::unordered_map<std::string, int> STL_HT;
		typename std::unordered_map<std::string, int>::iterator iter2;
		int count = 0;

		TimeStart = clock();
		CreateUNMap<std::string>(STL_HT, copy, DataSize[n]);
		TimeEnd = clock();
		ConstructingTime[n][5] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;


		TimeStart = clock();
		for (int i = 0; i < SearchingData; i++) {
			iter2 = STL_HT.find(Searching[i]);
			//if (iter2 != STL_HT.end())
		}
		TimeEnd = clock();
		RunTime[n][5] = (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC;

		STL_HT.clear();



		delete[] copy;
		delete[] str;
	}
	
	delete[] Searching;

	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			std::cout << "Recursive binary search :";
			break;
		case 1:
			std::cout << "Iterative binary search :";
			break;
		case 2:
			std::cout << " Binary tree search:";
			break;
		case 3:
			std::cout << " Hashing with chain:";
			break;
		case 4:
			std::cout << "C++ built-in map :";
			break;
		case 5:
			std::cout << "C++ built-in unoredered_map :";
			break;
		}
		for (int j = 0; j < 5; j++)
			std::cout << RunTime[j][i] << " ";
		std::cout << "\n Constructing time:";
		for (int j = 0; j < 5; j++)
			std::cout << ConstructingTime[j][i] << " ";
		std::cout << "\n\n";
	}
}

