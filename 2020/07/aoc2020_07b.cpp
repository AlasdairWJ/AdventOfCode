#include <cstdio>
#include <cstring>

#include <iostream>
#include <string>
#include <map>
#include <vector>

const std::string shiny_gold = "shiny gold";

using bag_list_type = std::vector<std::pair<int, std::string>>;

std::map<std::string, bag_list_type> bags_map;

int count_bag_contents(const std::string& bag_colour);
int count_bag_contents(const std::string& bag_colour, const bag_list_type& bag_list)
{
	int count = 0;
	for (const auto& count_colour_pair : bag_list)
		count += count_colour_pair.first * (1 + count_bag_contents(count_colour_pair.second));
	return count;
}

int count_bag_contents(const std::string& bag_colour)
{
	const auto it = bags_map.find(bag_colour);
	return it == bags_map.end() ? 0 : count_bag_contents(it->first, it->second);
}

int main(int argc, const char* argv[])
{
	char line[128];
	while (gets_s(line))
	{
		char colour[64], colour_base[32];

		int offset;
		sscanf_s(line,
				 "%s %s bags contain%n",
				 colour, (unsigned)_countof(colour),
				 colour_base, (unsigned)_countof(colour_base),
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
					 colour_base, (unsigned)_countof(colour_base),
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

	printf("%d", count_bag_contents(shiny_gold));

	return 0;	
}