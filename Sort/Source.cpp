#include "SomeSort.h"
#include<iostream>
//#include<string>
//#include<cstdlib>


int main() {
	std::ios::sync_with_stdio(false);        //斷開C++跟C之間的輸出保護裝置,提高cout速度

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