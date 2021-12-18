#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using BagList = std::vector<std::pair<int, std::string>>;

const std::string shiny_gold("shiny gold");

std::map<std::string, BagList> bags_map;

int count_bag_contents(const std::string& bag_colour);
int count_bag_contents(const BagList& bag_list)
{
	int count = 0;
	for (const auto& pair : bag_list)
		count += pair.first * (1 + count_bag_contents(pair.second));
	return count;
}

int count_bag_contents(const std::string& bag_colour)
{
	const auto it = bags_map.find(bag_colour);
	return it == bags_map.end() ? 0 : count_bag_contents(it->second);
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

	std::cout << count_bag_contents(shiny_gold);

	return 0;	
}