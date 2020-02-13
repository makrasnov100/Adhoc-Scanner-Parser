#include <string>
#include <iostream>

int main()
{
	float A = 0;
	std::cin >> A;
	std::cin.clear();
	std::cin.ignore(10000, '\n');

	float B = 0;
	std::cin >> B;
	std::cin.clear();
	std::cin.ignore(10000, '\n');

	float sum = (A+B);
	std::cout << std::to_string(sum) << std::endl;
	std::cout << std::to_string(sum/2) << std::endl;
	return 0;
}