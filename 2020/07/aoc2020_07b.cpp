#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <numeric>
#include <ranges>
#include <regex>

const std::regex description_re{ "^(\\w+ \\w+) bags contain (.*)$" };
const std::regex contents_re{ "(\\d+) (\\w+ \\w+) bags?" };

const std::string shiny_gold{ "shiny gold" };

using sub_bag_list_t = std::vector<std::pair<int, std::string>>;
using bag_map_t = std::map<std::string, sub_bag_list_t>;

bag_map_t bag_map;

int count_bag_contents(const std::string& bag);

int count_bag_contents(const sub_bag_list_t& sub_bags)
{
	auto r = sub_bags | std::views::transform([](const auto& pair)
	{
		return pair.first * (1 + count_bag_contents(pair.second));
	});

	return std::accumulate(r.begin(), r.end(), 0);
}

int count_bag_contents(const std::string& bag)
{
	return count_bag_contents(bag_map[bag]);
}

int main(int argc, const char* argv[])
{
	for (std::string line; std::getline(std::cin, line); )
	{
		std::smatch desc_match;
		if (std::regex_match(line, desc_match, description_re))
		{
			std::string bag = desc_match[1];

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

	std::cout << count_bag_contents(shiny_gold);
}