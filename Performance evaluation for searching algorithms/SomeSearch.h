#pragma once     //防命名碰撞
#ifndef SOMESEARCH_H_
#define SOMESEARCH_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include <map>
#include <unordered_map>
#endif
const int CharacterSize = 6;

//////binary search tree 宣告////////////////////
template<class T>
class BSTNode {
public:
	BSTNode() :leftchild(0), rightchild(0), data(0) {};
	BSTNode(T value) :leftchild(0), rightchild(0), data(value) {};
	template<class T> friend class BST;
private:
	BSTNode* leftchild;
	BSTNode* rightchild;
	T data;
};

template<class T>
class BST {
public:
	BST() :root(0) {};
	void createBST(const T* data, const int datasize);
	BSTNode<T>* Insert(BSTNode<T>* root, const T data);
	bool Search(BSTNode<T>* root, const T key);
	void Visit(BSTNode<T>* root);
	void PreOrder(BSTNode<T>* root);
	void DeleteBST(BSTNode<T>* root);
	////驅動程式//////
	bool Search(const T key);
	void PreOrder() { PreOrder(root); };
	void DeleteBST() { DeleteBST(root); };
	~BST() { DeleteBST();/* std::cout << "\nBST移除\n";*/ };
private:
	BSTNode<T>* root;
};

/////////////Hash with chain//////////////////////////////////////
template<class T>
class HTNode {
public:
	HTNode() :data(0), next(0) {};			//string 版本額外寫在.cpp
	HTNode(T value) :data(value), next(0) {};
	template<class T> friend class HashChain;
private:
	HTNode* next;
	T data;
};

template<class T>
class HashChain {
public:
	HashChain() :first(0), HTSize(0) {};
	void Insert(const T data, const int HashNum);
	bool IsInChain(const T key, const int HashNum);
	void CreateHT(const T* data, const int datasize, const int HTsize);
	void OutputChain(const int n);
	void OutputHT();
	void DeleteChain(const int n);
	void DeleteHT();
	~HashChain() { DeleteHT(); /*std::cout << "\nHT移除\n";*/ };
private:
	HTNode<T>* first;
	int HTSize;
};

template<class T>
int FindHashNumber(const T key, const int HTsize)
{
	//////參考網路寫法////////////////
	unsigned int hashNum = 0;
	unsigned int highorder;
	for (int i = 0; i < CharacterSize; i++) {
		highorder = hashNum & 0xF8000000;
		hashNum = hashNum << 5;
		hashNum = hashNum ^ (highorder >> 27);
		hashNum = hashNum ^ key[i];
	}
	return hashNum % HTsize;
}

////////////////////////two binary search//////////////////////////

template<class T>
bool IteBinarySearch(T* list, int length, T key) {
	int bottom = 0;
	int top = length - 1;
	int mid;
	while (bottom <= top) {
		mid = bottom + (top - bottom) / 2;

		if (key == list[mid])
			return true;
		else if (key > list[mid])
			bottom = mid + 1;
		else
			top = mid - 1;

	}

	return false;
}

template<class T>
bool ReBinarySearch(T* list, int bottom, int top, T key) {
	if (bottom <= top) {

		int mid = bottom + (top - bottom) / 2;

		if (key == list[mid])
			return true;
		else if (key > list[mid])
			return ReBinarySearch(list, mid + 1, top, key);
		else
			return ReBinarySearch(list, bottom, mid - 1, key);

	}
	return false;
}

///////////////////////two STL Map /////////////////////////////

template<class T>
void CreateMap(std::map<T, int>& BKT, T* data, int dataSize) {
	for (int i = 0; i < dataSize; i++)
		BKT.insert(std::pair<T, int>(data[i], i + 1));
}

template<class T>
void CreateUNMap(std::unordered_map<T, int>& HT, T* data, int dataSize) {
	for (int i = 0; i < dataSize; i++)
		HT.insert(std::pair<T, int>(data[i], i + 1));
}
/////////////////DataCreate///////////////////////////////////////////
void create_string(std::string* list, int n);

void string_copy(std::string* original, std::string* copy, int size);

void StringCompare(std::string* list1, std::string* list2, const int size);

template<class T>
void PrintArray(T* arr, const int size) {
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
////////////////////////////Searching//////////////////////////////////

void Searching();





