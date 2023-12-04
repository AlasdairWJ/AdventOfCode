#include <iostream>
#include <string>
#include <regex>
#include <ranges>
#include <charconv>
#include <vector>
#include <set>

#include "../../util/charconv.hpp" // util::from_chars

const std::regex card_pattern{ "Card \\s*\\d+\\: (.*) \\| (.*)" };

struct Card
{
	int matches;
	int count;
};

int main(int _, const char*[])
{
	std::vector<Card> cards;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::smatch match;
		std::regex_match(line, match, card_pattern);

		const std::string_view winning_numbers_str{ match[1].first, match[1].second };
		const std::string_view numbers_str{ match[2].first, match[2].second };

		std::set<int> winning;
		for (const auto winning_number_str : winning_numbers_str | std::views::split(' '))
		{
			if (!winning_numbers_str.empty())
			{
				if (int number; util::from_chars(winning_number_str, number))
				{
					winning.insert(number);
				}
			}
		}

		int matches = 0;
		for (const auto number_str : numbers_str | std::views::split(' '))
		{
			if (!numbers_str.empty())
			{
				if (int number; util::from_chars(number_str, number))
				{
					if (winning.contains(number))
						matches++;
				}
			}
		}

		cards.emplace_back(matches, 1);
	}

	int total = 0;

	for (int i = 0; i < cards.size(); i++)
	{
		total += cards[i].count;

		for (int j = 1; j <= cards[i].matches; j++)
			cards[i + j].count += cards[i].count;
	}

	std::cout << total;
}