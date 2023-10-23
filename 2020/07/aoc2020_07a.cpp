#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm> // std::any_of, std::count_if
#include <regex>
#include <ranges>

const std::regex description_re{ "^(\\w+ \\w+) bags contain (.*)$" };
const std::regex contents_re{ "(\\d+) (\\w+ \\w+) bags?" };

const std::string shiny_gold{ "shiny gold" };

using sub_bag_list_t = std::vector<std::pair<int, std::string>>;
using bag_map_t = std::map<std::string, sub_bag_list_t>;

bag_map_t bag_map;

bool contains_shiny_gold(const sub_bag_list_t& sub_bags)
{
	const auto sub_bags_values = sub_bags | std::views::values;

	if (std::ranges::find(sub_bags_values, shiny_gold) != sub_bags_values.end())
		return true;

	return std::ranges::any_of(
		sub_bags_values,
		[&] (const auto sub_bag)
		{
			return contains_shiny_gold(bag_map[sub_bag]);
		}
	);
}

int main(int _, const char*[])
{
	for (std::string line; std::getline(std::cin, line); )
	{
		std::smatch desc_match;
		if (std::regex_match(line, desc_match, description_re))
		{
			const std::string bag = desc_match[1];

			auto& sub_bags = bag_map[bag];

			auto it = std::sregex_iterator{
				desc_match[2].first,
				desc_match[2].second,
				contents_re
			};

			for (; it != std::sregex_iterator{}; ++it)
			{
				auto match = *it;

				const int sub_bag_count = std::stoi(match[1]);
				const std::string sub_bag = match[2];

				sub_bags.emplace_back(sub_bag_count, sub_bag);
			}
		}
	}

	std::cout << std::ranges::count_if(
		bag_map | std::views::values,
		contains_shiny_gold
	);
}