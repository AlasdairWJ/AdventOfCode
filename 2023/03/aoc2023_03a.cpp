#include <iostream>
#include <string> // std::getline
#include <vector>
#include <algorithm> // std::min
#include <charconv> // std::from_chars
#include <cctype> // std::isdigit

constexpr char digits[]{ "0123456789" };

bool test(const char c) { return !std::isdigit(c) && c != '.'; }

int main(int _, const char*[])
{
	std::vector<std::string> board;
	for (std::string line; std::getline(std::cin, line); )
		board.push_back(line);

	int total = 0;

	std::size_t y = 0;
	for (const auto& line : board)
	{
		for (std::size_t ix = 0; ix < line.size(); )
		{
			const std::size_t digit_ix = line.find_first_of(digits, ix);
			if (digit_ix == std::string::npos)
				break;

			std::size_t first_nondigit_ix = line.find_first_not_of(digits, digit_ix);
			if (first_nondigit_ix == std::string::npos)
				first_nondigit_ix = line.size();

			bool is_included = false;

			const std::size_t i1 = digit_ix != 0 ? digit_ix - 1 : 0ull;
			const std::size_t i2 = std::min(first_nondigit_ix, line.size() - 1);

			if (y != 0)
			{
				for (std::size_t i = i1; i <= i2; i++)
					is_included |= test(board[y - 1][i]);
			}

			if (digit_ix != 0) is_included |= test(line[i1]);
			if (first_nondigit_ix != line.size()) is_included |= test(line[i2]);

			if (y + 1 < board.size())
			{
				for (std::size_t i = i1; i <= i2; i++)
					is_included |= test(board[y + 1][i]);
			}

			if (is_included)
			{
				int value{};
				std::from_chars(
					&line[digit_ix],
					&line[first_nondigit_ix],
					value
				);

				total += value;
			}

			ix = first_nondigit_ix;
		}
		y++;
	}

	std::cout << total;
}