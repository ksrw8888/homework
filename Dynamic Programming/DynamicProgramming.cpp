#include "DynamicProgramming.h"
#include<cstdlib>
#include<ctime>

void PrintOptimalPattern(int** s, int i, int j)
{
	if (i == j)
	{
		std::cout << "A" << i;
	}
	else
	{
		std::cout << "(";
		PrintOptimalPattern(s, i, s[i][j]);
		PrintOptimalPattern(s, s[i][j] + 1, j);
		std::cout << ")";
	}
	return;
}

void ProjectOne()
{
	srand(time(0));
	double TimeStart, TimeEnd;
	int n[5] = { 10,20,30,40,50};

	for (int i = 0; i < 5; i++)
	{
		int* p = new int[n[i] + 1];

		for (int j = 0; j <= n[i]; j++)
		{
			p[j] = rand() % 100 + 1;
			//std::cout << p[j] << " ";
		}
		std::cout << "\n";

		std::cout << "Round n =" << n[i] << ":\n";

		RecursiveMatrixChain RMC(n[i] + 1);
		MemorizedMatrixChain MMC(n[i] + 1);
		MatrixChainOrder MCO(n[i] + 1);
		
		
		TimeStart = clock();
		RMC.RMC(p, 1, n[i]);
		TimeEnd = clock();
		std::cout << "RecursiveMatrixChain = "  << (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC << "\n";
		
		TimeStart = clock();
		MMC.MMC(p,n[i]+1);
		TimeEnd = clock();
		std::cout << "MemorizedMatrixChain = " << (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC << "\n";

		TimeStart = clock();
		MCO.MCO(p, n[i]+1);
		TimeEnd = clock();
		std::cout << "MatrixChainOrder = " << (double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC << "\n";

		//PrintOptimalPattern(MCO.S, 1, n[i]);

		std::cout << "----------------------------------------------------"  "\n";
	}
}

void ProjectTwo()
{
	srand(time(0));
	float Num = 0.001;    //不確定數值是否要特別設計,所以採用範例給的值
	double TimeStart, TimeEnd;
	int n[5] = { 100,200,300,400,500 };

	for (int i = 0; i < 5; i++)
	{
		float* p = new float[n[i]], * q = new float[n[i]];

		for (int j = 0; j <= n[i]; j++)
		{
			if (j != 0) 
			{
				p[j] = Num;
			}

			q[j] = Num;
			
		}

		for (int j = 0; j <= (1000 - 2 * n[i] - 1); j++)
		{
			//最隨機增加 p or q的值達到加總為1
			switch (rand() % 2)							
			{
			case 0:
				p[(rand() % n[i]) + 1] += Num;
				break;
			case 1:
				q[rand() % (n[i] + 1)] += Num;
				break;
			}
			
		}
	
		OPTIMAL_BST OBST(n[i]);

		TimeStart = clock();
		OBST.BST(p, q, n[i]);
		TimeEnd = clock();
		std::cout<<"Round n ="<<n[i]<<"time ="<<(double)(TimeEnd - TimeStart) / CLOCKS_PER_SEC<<"\n";

		delete[] p;
		delete[] q;
	}

	return ;
}


RecursiveMatrixChain::RecursiveMatrixChain(int n)
{
	M = new int*[n];
	for (int i = 0; i < n; i++)
		M[i] = new int[n];
	
	S = new int*[n];
	for (int i = 0; i < n; i++)
		S[i] = new int[n];
}


int RecursiveMatrixChain::RMC(int* p, int i, int j)
{
	if (i == j)
		return 0;

	M[i][j] = 2147483647;

	for (int k = i; k < j; k++)
	{
		int q = RMC(p, i, k) + RMC(p, k + 1, j) + p[i - 1] * p[k] * p[j];
		if (q < M[i][j])
		{
			M[i][j] = q;
			S[i][j] = k;
		}
	}
	return M[i][j];
}


MemorizedMatrixChain::MemorizedMatrixChain(int n)
{
	M = new int* [n];
	for (int i = 0; i < n; i++)
		M[i] = new int[n];

	S = new int* [n];
	for (int i = 0; i < n; i++)
		S[i] = new int[n];
}

int MemorizedMatrixChain::MMC(int* p, int n)
{
	 n -=1;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			M[i][j] = 2147483647;
		}
	}

	return LC(p, 1, n);
}

int MemorizedMatrixChain::LC(int* p, int i, int j)
{
	if (M[i][j] < 2147483647)
		return M[i][j];
	if (i == j)
	{
		M[i][j] = 0;
	}
	else
	{
		for (int k = i; k < j; k++)
		{
			int q = LC(p, i, k) + LC(p, k + 1, j) + p[i - 1] * p[k] * p[j];
			if (q < M[i][j])
			{
				M[i][j] = q;
				S[i][j] = k;
			}
		}
	}

	return M[i][j];
}


MatrixChainOrder::MatrixChainOrder(int n)
{
	M = new int* [n];
	for (int i = 0; i < n; i++)
		M[i] = new int[n];

	S = new int* [n];
	for (int i = 0; i < n; i++)
		S[i] = new int[n];
}

void MatrixChainOrder::MCO(int* p,int n)
{
	n -= 1;

	for (int i = 1; i <= n; i++)
	{
		M[i][i] = 0;
	}

	for (int len = 2; len <= n; len++)
	{
		for (int i = 1; i <= (n - len + 1); i++)
		{
			int j = i + len - 1;
			M[i][j] = 2147483647;
			for (int k = i; k < j; k++)
			{
				int q = M[i][k] + M[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < M[i][j])
				{
					M[i][j] = q;
					S[i][j] = k;
				}
			}
		}
	}

	return;
}



OPTIMAL_BST::OPTIMAL_BST(int InputN)
{
	n = InputN + 1;
	e = new float* [n];
	for (int i = 0; i <= n; i++)
		e[i] = new float[n];

	w = new float* [n];
	for (int i = 0; i <= n; i++)
		w[i] = new float[n];

	root = new float* [n];
	for (int i = 0; i <= n; i++)
		root[i] = new float[n];
}

void OPTIMAL_BST::BST(float* p, float* q, int n)
{
	for (int i = 1; i <= n + 1; i++)
	{
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (int len = 1; len <= n;len++)
	{
		for (int i = 1; i <= (n - len + 1);i++)
		{
			int j = i + len - 1;
			e[i][j] = 2147483647;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int r = i; r <= n; r++)
			{
				int t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
}

OPTIMAL_BST::~OPTIMAL_BST()
{
	for (int i = 0; i <= n; i++)
	{
		delete[] e[i];
		delete[] w[i];
		delete[] root[i];
	}

}
