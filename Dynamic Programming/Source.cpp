#include<iostream>
#include<cstdlib>
#include<ctime>
#include"DynamicProgramming.h"






int main() {
	//斷開C++跟C之間的輸出保護裝置,提高cout速度
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
