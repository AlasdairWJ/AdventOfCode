#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	bool seated[1000] = {};

	std::string line;
	while (std::getline(std::cin, line))
	{
		int lower = 0, upper = 128;

		for (int i = 0; i < 7; i++)
			(line[i] == 'F' ? upper : lower) = (lower + upper) / 2;

		const int row = lower;

		lower = 0, upper = 8;

		for (int i = 7; i < 11; i++)
			(line[i] == 'L' ? upper : lower) = (lower + upper) / 2;

		const int column = lower;

		const int seat_id = 8 * row + column;

		seated[seat_id] = true;
	}

	for (int n = 1; n < 999; n++)
		if (!seated[n] && seated[n+1] && seated[n-1])
		{
			std::cout << n;
			break;
		}

	return 0;
}