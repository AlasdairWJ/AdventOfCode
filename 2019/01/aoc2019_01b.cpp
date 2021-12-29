#include <iostream>

int main(int argc, const char* argv[])
{
	int total = 0;

	int value;
	while (std::cin >> value)
	{
		while (((value /= 3) -= 2) > 0)
			total += value;
	}

	std::cout << total;

	return 0;
}