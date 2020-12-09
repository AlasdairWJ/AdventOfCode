#include <cstdio>
#include <cstring>

#include <iostream>
#include <string>

#include <map>
#include <vector>

const std::string shiny_gold = "shiny gold";

using bag_list_type = std::vector<std::pair<int, std::string>>;

std::map<std::string, bag_list_type> bags_map;

bool contains_shiny_gold(const std::string& bag_colour);
bool contains_shiny_gold(const std::string& bag_colour, const bag_list_type& bag_list)
{
	for (const auto& count_colour_pair : bag_list)
		if (count_colour_pair.second == shiny_gold || contains_shiny_gold(count_colour_pair.second))
			return true;
	return false;
}

bool contains_shiny_gold(const std::string& bag_colour)
{
	const auto it = bags_map.find(bag_colour);
	return it != bags_map.end() && contains_shiny_gold(bag_colour, it->second);
}

int main(int argc, const char* argv[])
{
	char line[128];
	while (gets_s(line, (unsigned)_countof(line)))
	{
		char colour[64], colour_base[32];

		int offset;
		sscanf_s(line,
				 "%s %s bags contain%n",
				 colour, (unsigned)_countof(colour),
				 colour_base, (unsigned)_countof(colour),
				 &offset);

		strcat(strcat(colour, " "), colour_base);

		if (strcmp(line + offset, " no other bags.") == 0)
			continue;
		
		auto& bag_list = bags_map[colour];

		char terminator;
		do
		{
			int bag_count, n;
			sscanf_s(line + offset, " %d %s %s %n",
					 &bag_count,
					 colour, (unsigned)_countof(colour),
					 colour_base, (unsigned)_countof(colour),
					 &n);
			
			strcat(strcat(colour, " "), colour_base);

			bag_list.emplace_back(bag_count, colour);

			offset += n;

			if (bag_count == 1)
				sscanf_s(line + offset, "bag%c%n", &terminator, 1u, &n);
			else
				sscanf_s(line + offset, "bags%c%n", &terminator, 1u, &n);

			offset += n;
		}
		while(terminator != '.');
	}

	int count = 0;
	for (const auto& colour_bags_pair : bags_map)
		if (contains_shiny_gold(colour_bags_pair.first, colour_bags_pair.second))
			count++;

	printf("%d", count);
	return 0;	
}