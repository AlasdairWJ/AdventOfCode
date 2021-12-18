#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm> // std::any_of, std::count_if

using BagList = std::vector<std::pair<int, std::string>>;

const std::string shiny_gold("shiny gold");

std::map<std::string, BagList> bags_map;

bool contains_shiny_gold(const std::string& bag_colour);
bool contains_shiny_gold(const BagList& bag_list)
{
	return std::any_of(bag_list.begin(), bag_list.end(),
		[] (const auto pair) { return pair.second == shiny_gold ||
									  contains_shiny_gold(pair.second); });
}

bool contains_shiny_gold(const std::string& bag_colour)
{
	const auto it = bags_map.find(bag_colour);
	return it != bags_map.end() && contains_shiny_gold(it->second);
}

int main(int argc, const char* argv[])
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::stringstream ss(line);

		std::string adj, colour;

		ss >> adj;
		ss >> colour;

		auto& bag_list = bags_map[adj + " " + colour];

		std::string ignore;
		ss >> ignore; // bags
		ss >> ignore; // contain

		do
		{
			std::string bag_count_str_or_no;
			ss >> bag_count_str_or_no;

			if (bag_count_str_or_no == "no") // no other bags
				break;

			const int bag_count = std::stoi(bag_count_str_or_no);

			ss >> adj;
			ss >> colour;
			
			bag_list.emplace_back(bag_count, adj + " " + colour);

			ss >> ignore; // bags[,.]
		}
		while (ignore.back() != '.');
	}

	std::cout << std::count_if(bags_map.begin(), bags_map.end(),
		[](const auto pair) { return contains_shiny_gold(pair.second); });

	return 0;	
}