#include <iostream>
#include <string> // std::getline

constexpr char digits[]{ "0123456789" };

int main(int _, const char*[])
{
	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto first_ix = line.find_first_of(digits);
		const auto last_ix = line.find_last_of(digits);

		const int first_digit = int{ line[first_ix] - '0' };
		const int last_digit = int{ line[last_ix] - '0' };

		total += 10 * first_digit + last_digit;
	}

	std::cout << total;
}