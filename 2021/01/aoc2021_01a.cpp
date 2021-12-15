#include <iostream>

int main(int argc, const char* argv[])
{
	int count = 0;

	int previous_level;
	std::cin >> previous_level;

	int level;
	while (std::cin >> level)
	{
		if (level > previous_level)
			count++;

		previous_level = level;
	}

	std::cout << count;

	return 0;
}