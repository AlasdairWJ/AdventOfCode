#include <iostream>
#include <string>
#include <regex>
#include <ranges>
#include <charconv>
#include <set>

const std::regex card_pattern{ "Card \\s*\\d+\\: (.*) \\| (.*)" };

bool from_chars(auto && r, auto& value)
{
	const char* data = std::ranges::data(r);
	return std::from_chars(data, data + std::ranges::size(r), value).ec == std::errc{};
}

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
		for (const auto winning_number_str : winning_numbers_str | std::views::split(' '))
		{
			if (!winning_numbers_str.empty())
			{
				if (int number; from_chars(winning_number_str, number))
				{
					winners.insert(number);
				}
			}
		}

		int match_count = 0;
		for (const auto number_str : numbers_str | std::views::split(' '))
		{
			if (!numbers_str.empty())
			{
				if (int number; from_chars(number_str, number))
				{
					if (winners.contains(number))
					{
						match_count++;
					}
				}
			}
		}

		if (match_count != 0)
		{
			total += (1 << (win_count - 1));
		}
	}

	std::cout << total;
}