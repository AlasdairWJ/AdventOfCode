#include <iostream>
#include <string>

int main(int _, const char* [])
{
	bool seated[1000]{};

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

		seated[seat_id] = true;
	}

	for (int n = 1; n < 999; n++)
		if (!seated[n] && seated[n+1] && seated[n-1])
		{
			std::cout << n;
			break;
		}
}