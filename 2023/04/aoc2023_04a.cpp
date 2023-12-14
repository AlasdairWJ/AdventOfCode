#include <iostream>
#include <string> // std::getline
#include <regex>
#include <ranges> // std::views::split
#include <set>

#include "../../util/charconv.hpp" // util::from_chars

const std::regex card_pattern{ "Card \\s*\\d+\\: (.*) \\| (.*)" };

int main(int _, const char*[])
{
	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::smatch match;
		std::regex_match(line, match, card_pattern);

		const std::string_view winning_numbers_str{ match[1].first, match[1].second };
		const std::string_view numbers_str{ match[2].first, match[2].second };

		std::set<int> winners;
		for (const auto number_str : winning_numbers_str | std::views::split(' '))
		{
			if (int number; util::from_chars(number_str, number))
			{
				winners.insert(number);
			}
		}

		int match_count = 0;
		for (const auto number_str : numbers_str | std::views::split(' '))
		{
			if (int number; util::from_chars(number_str, number))
			{
				if (winners.contains(number))
				{
					match_count++;
				}
			}
		}

		if (match_count != 0)
		{
			total += (1 << (match_count - 1));
		}
	}

	std::cout << total;
}