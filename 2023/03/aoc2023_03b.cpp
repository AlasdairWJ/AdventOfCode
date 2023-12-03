#include <iostream>
#include <string> // std::getline
#include <vector>
#include <algorithm> // std::min
#include <charconv> // std::from_chars
#include <map>

constexpr char digits[]{ "0123456789" };

int main(int _, const char*[])
{
	std::vector<std::string> board;
	for (std::string line; std::getline(std::cin, line); )
		board.push_back(line);

	std::map<std::pair<std::size_t, std::size_t>, std::vector<int>> gears;

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

			bool is_touching_gear = false;
			std::size_t gear_x, gear_y;

			const std::size_t i1 = digit_ix != 0 ? digit_ix - 1 : 0ull;
			const std::size_t i2 = std::min(first_nondigit_ix, line.size() - 1);

			if (y != 0)
			{
				for (std::size_t i = i1; i <= i2; i++)
					if (board[y - 1][i] == '*')
					{
						is_touching_gear = true;
						gear_x = i;
						gear_y = y - 1;
						break;
					}
			}

			if (!is_touching_gear && digit_ix != 0)
			{
				if (line[i1] == '*')
				{
					is_touching_gear = true;
					gear_x = i1;
					gear_y = y;
				}
			}

			if (!is_touching_gear && first_nondigit_ix != line.size())
			{
				if (line[i2] == '*')
				{
					is_touching_gear = true;
					gear_x = i2;
					gear_y = y;
				}
			}

			if (!is_touching_gear && y + 1 < board.size())
			{
				for (std::size_t i = i1; i <= i2; i++)
					if (board[y + 1][i] == '*')
					{
						is_touching_gear = true;
						gear_x = i;
						gear_y = y + 1;
						break;
					}
			}

			if (is_touching_gear)
			{
				int value{};
				std::from_chars(
					&line[digit_ix],
					&line[first_nondigit_ix],
					value
				);

				gears[{ gear_x, gear_y }].push_back(value);
			}

			ix = first_nondigit_ix;
		}

		y++;
	}

	int total = 0;

	for (const auto [_, values] : gears)
	{
		if (values.size() == 2)
		{
			total += values[0] * values[1];
		}
	}

	std::cout << total;
}