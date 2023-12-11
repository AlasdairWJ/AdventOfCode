#include <iostream>

int main(int _, const char*[])
{
	int total = 0;

	for (int value; std::cin >> value; )
		total += (value / 3) - 2;

	std::cout << total;
}