#include <iostream>
#include <string> // std::getline
#include <map>
#include <algorithm> // std::ranges::minmax_element
#include <ranges> // std::views::values

constexpr int Steps = 40;

int main(int _, const char*[])
{
	std::string polymer;
	std::getline(std::cin, polymer);

	std::string line;
	std::getline(std::cin, line); // skip nl

	std::map<std::pair<char, char>, char> rules;

	while (std::getline(std::cin, line) && !line.empty())
		rules.emplace(std::make_pair(line[0], line[1]), line[6]);

	std::map<std::pair<char, char>, long long> pair_counts;

	for (std::size_t i = 1; i < polymer.size(); i++)
		pair_counts[std::make_pair(polymer[i - 1], polymer[i])]++;

	for (int step = 0; step < Steps; step++)
	{
		std::map<std::pair<char, char>, long long> next_pair_counts;

		for (const auto [pair, count] : pair_counts)
		{
			auto rule_it = rules.find(pair);
			if (rule_it != rules.end())
			{
				const auto [first, second] = pair;
				const char letter = rule_it->second;
				next_pair_counts[std::make_pair(first, letter)] += count;
				next_pair_counts[std::make_pair(letter, second)] += count;
			}
			else
			{
				next_pair_counts.emplace(pair, count);
			}
		}

		pair_counts.swap(next_pair_counts);
	}

	std::map<char, long long> distribution{};

	distribution[polymer.front()]++;
	for (const auto [pair, count] : pair_counts)
		distribution[pair.second] += count;
	
	const auto [min_it, max_it] = std::ranges::minmax_element(distribution | std::views::values);
	std::cout << (*max_it - *min_it) << '\n';
}