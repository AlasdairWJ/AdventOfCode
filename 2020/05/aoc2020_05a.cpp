#include <iostream>
#include <string>

int main(int _, const char* [])
{
	int max_seat_id = -1;

	auto reduce = [](auto begin, const int n, const char upper_letter)
	{
		int lower = 0, upper = 1 << n;
		for (auto it = begin; it != begin + n; ++it)
			(*it == upper_letter ? upper : lower) = (lower + upper) / 2;

		return lower;
	};

	for (std::string line; std::getline(std::cin, line); )
	{
		const int row = reduce(line.begin(), 7, 'F');
		const int column = reduce(line.begin() + 7, 3, 'L');

		const int seat_id = 8 * row + column;

		if (seat_id > max_seat_id)
			max_seat_id = seat_id;
	}

	std::cout << max_seat_id;}