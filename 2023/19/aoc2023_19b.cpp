#include <iostream>
#include <string> // std::getline
#include <ranges> // std::views::split
#include <string_view>
#include <charconv> // std::from_chars
#include <map>
#include <array>
#include <algorithm> // std::ranges::copy
#include <numeric> // std::accumulate
#include <set>

#include "../../util/charconv.hpp" // util::from_chars

constexpr std::string_view XMAS{ "xmas" };

struct Range
{
	int lower;
	int upper;

	auto operator<=>(const Range&) const = default;
};

using Part = std::array<Range, 4>;

struct Rule
{
	struct Condition {
		int field;
		char operation;
		int value;
		char destination[4];
	} conditions[3];
	int conditionCount;

	char finalDestination[4];
};

int main(int _, const char*[])
{
	std::map<std::string, Rule> rules;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
	{
		const auto ix = line.find('{');
		const auto ruleName = line.substr(0, ix);
		const auto rest = std::string_view{ line }.substr(ix + 1, line.size() - ix - 2);

		auto& rule = rules[ruleName];

		for (auto && r : rest | std::views::split(','))
		{
			const std::string_view condition_str{ r.begin(), r.end() };
			const auto ix = condition_str.find(':');

			if (ix == std::string::npos)
			{
				std::ranges::copy(condition_str, rule.finalDestination);
			}
			else
			{
				auto& condition = rule.conditions[rule.conditionCount++];
				condition.field = static_cast<int>(XMAS.find(condition_str[0]));
				condition.operation = int{ condition_str[1] };

				const auto value_str = condition_str.substr(2, ix);
				const auto destination = condition_str.substr(ix + 1);

				util::from_chars(value_str, condition.value);
				std::ranges::copy(destination, condition.destination);
			}
		}
	}

	const Range initialRange{ 1, 4000 };
	const Part initialPart{ initialRange, initialRange, initialRange, initialRange };

	std::set<Part> finalRanges;

	std::set<std::pair<Part, std::string>> parts{ { initialPart, "in" } };

	while (!parts.empty())
	{
		decltype(parts) nextParts;

		for (auto [partRanges, ruleName] : parts)
		{
			if (ruleName == "A")
			{
				finalRanges.insert(partRanges);
				continue;
			}

			if (ruleName == "R")
				continue;

			const auto& rule = rules[ruleName];

			std::string nextRule = rule.finalDestination;

			for (int i = 0; i < rule.conditionCount; i++)
			{
				const auto& condition = rule.conditions[i];

				if (condition.operation == '<')
				{
					if (partRanges[condition.field].upper < condition.value)
					{
						// always true - will never cover remaining conditions
						nextRule = condition.destination;
						break;
					}
					else if (partRanges[condition.field].lower >= condition.value)
					{
						// always false - move on to next condition
						continue;
					}
					else
					{
						// some overlap

						auto partCopy = partRanges;
						partCopy[condition.field].upper = condition.value - 1;
						partRanges[condition.field].lower = condition.value;
						nextParts.emplace(partCopy, condition.destination);
					}
				}
				else if (condition.operation == '>')
				{
					if (partRanges[condition.field].lower > condition.value)
					{
						nextRule = condition.destination;
						break;
					}
					else if (partRanges[condition.field].upper <= condition.value)
					{
						continue;
					}
					else
					{
						auto partCopy = partRanges;
						partCopy[condition.field].lower = condition.value + 1;
						partRanges[condition.field].upper = condition.value;
						nextParts.emplace(partCopy, condition.destination);
					}
				}
			}

			nextParts.emplace(partRanges, nextRule);
		}

		nextParts.swap(parts);
	}

	long long total = 0;

	for (const auto& partRanges : finalRanges)
	{
		long long count = 1;

		for (const auto& [lower, upper] : partRanges)
		{
			count *= (upper - lower + 1);
		}

		total += count;
	}

	std::cout << total;
}