#include "SomeSort.h"
#include<iostream>
//#include<string>
//#include<cstdlib>


int main() {
	std::ios::sync_with_stdio(false);        //�_�}C++��C��������X�O�@�˸m,����cout�t��

	char input;
	std::cout << "If you want to test the project one,you can input 1.\n";
	std::cout << "If you want to test the project two,you can input 2.\n";

	input = std::cin.get();
	
	if (input == '1')
		project_one();
	else if (input == '2')
		project_two();

	
	return 0;
}