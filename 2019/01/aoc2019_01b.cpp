#include <iostream>

int main(int _, const char*[])
{
	int total = 0;

	for (int value; std::cin >> value; )
	{
		while (value /= 3, value -= 2, value > 0)
			total += value;
	}

	std::cout << total;
}