#include <iostream>

constexpr int size = 3;

int main(int argc, const char* argv[])
{
	int count = 0;
	int total = 0;
	int offset = 0;
	int buffer[size];

	for (int& v : buffer)
	{
		std::cin >> v;
		buffer[offset++] = v;
		total += v;
	}

	offset = 0;

	int level;
	while (std::cin >> level)
	{
		int new_total = total + level - buffer[offset];

		if (new_total > total)
			count++;

		total = new_total;
		buffer[offset] = level;

		if (++offset == size)
			offset = 0;
	}

	std::cout << count;

	return 0;
}