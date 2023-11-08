#include <iostream>
#include <string> // std::getline
#include <map>
#include <algorithm> // std::ranges::minmax_element
#include <ranges> // std::views::values

constexpr int Steps = 10;

int main(int _, const char*[])
{
	std::string polymer;
	std::getline(std::cin, polymer);

	std::string line;
	std::getline(std::cin, line); // skip nl

	std::map<std::pair<char, char>, char> rules;

	while (std::getline(std::cin, line) && !line.empty())
		rules.emplace(std::make_pair(line[0], line[1]), line[6]);

	for (int step = 0; step < Steps; step++)
	{
		for (std::size_t i = 1; i < polymer.size(); i++)
		{
			auto rule_it = rules.find(std::make_pair(polymer[i - 1], polymer[i]));
			if (rule_it != rules.end())
			{
				polymer.insert(i, 1, rule_it->second);
				i++;
			}
		}
	}

	std::map<char, int> distribution{};

	for (const char letter : polymer)
		distribution[letter]++;

	const auto [min_it, max_it] = std::ranges::minmax_element(distribution | std::views::values);
	std::cout << (*max_it - *min_it);
}