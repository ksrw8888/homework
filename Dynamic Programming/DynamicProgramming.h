#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H
#include<iostream>

#pragma once
#endif

class RecursiveMatrixChain
{
public:
	int** M;
	int** S;

public:
	RecursiveMatrixChain(int n);
	int RMC(int* p, int i, int j);
	~RecursiveMatrixChain() { delete[]M; delete[]S; };
};


class MemorizedMatrixChain
{
public:
	int** M;
	int** S;

public:
	MemorizedMatrixChain(int n);
	int MMC(int* p,int n);
	int LC(int* p, int i, int j);
	~MemorizedMatrixChain() { delete[]M; delete[]S; };
};


class MatrixChainOrder
{
public:
	int** M;
	int** S;

public:
	MatrixChainOrder(int n);
	void MCO(int* p,int n);
	~MatrixChainOrder() { delete[]M; delete[]S; };
};


void PrintOptimalPattern(int** s, int i, int j);

class OPTIMAL_BST
{
public:
	float** e, ** w, ** root;
	int n;
public:
	OPTIMAL_BST(int InputN);
	void BST(float* p, float* q, int n);
	~OPTIMAL_BST();
};

void ProjectOne();

void ProjectTwo();