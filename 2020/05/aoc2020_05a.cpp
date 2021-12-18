#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	int max_seat_id = -1;

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

		if (seat_id > max_seat_id)
			max_seat_id = seat_id;
	}

	std::cout << max_seat_id;

	return 0;
}