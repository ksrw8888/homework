#include<iostream>
#include<cstdlib>
#include<ctime>
#include"DynamicProgramming.h"






int main() {
	//�_�}C++��C��������X�O�@�˸m,����cout�t��
	std::ios::sync_with_stdio(false);
	
	int input;
	
	std::cout << "project one input 1\nproject two input 2\n";
	std::cout << "input :";
	std::cin >> input;

	switch (input)
	{
	case 1:
		ProjectOne();
		break;

	case 2:
		ProjectTwo();
		break;

	default:

		break;
	}
	return 0;
}
