#include <iostream>
#include <string> // std::getline
#include <ranges> // std::views::split
#include <string_view>
#include <charconv> // std::from_chars
#include <map>
#include <array>
#include <algorithm> // std::ranges::copy
#include <numeric> // std::accumulate

#include "../../util/charconv.hpp" // util::from_chars

constexpr std::string_view XMAS{ "xmas" };

using Part = std::array<int, 4>;

struct Rule
{
	struct Condition {
		int field;
		char operation;
		int value;
		char destination[4];
	} conditions[3];
	int condition_count;

	char final_destination[4];
};

int main(int _, const char*[])
{
	std::map<std::string, Rule> rules;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
	{
		const auto ix = line.find('{');
		const auto rulename = line.substr(0, ix);
		const auto rest = std::string_view{ line }.substr(ix + 1, line.size() - ix - 2);

		auto& rule = rules[rulename];

		for (auto && r : rest | std::views::split(','))
		{
			const std::string_view condition_str{ r.begin(), r.end() };
			const auto ix = condition_str.find(':');

			if (ix == std::string::npos)
			{
				std::ranges::copy(condition_str, rule.final_destination);
			}
			else
			{
				auto& condition = rule.conditions[rule.condition_count++];
				condition.field = static_cast<int>(XMAS.find(condition_str[0]));
				condition.operation = condition_str[1];

				const auto value_str = condition_str.substr(2, ix);
				const auto destination = condition_str.substr(ix + 1);

				util::from_chars(value_str, condition.value);
				std::ranges::copy(destination, condition.destination);
			}
		}
	}

	long long total = 0;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
	{
		Part part{};

		const std::string_view inner{ line.begin() + 1, line.end() - 1 };

		for (int n{}; auto && r : inner | std::views::split(','))
		{
			const std::string_view value_str{ r.begin() + 2, r.end() };
			from_chars(value_str, part[n++]);
		}

		std::string current_rule = "in";

		do
		{
			const auto& rule = rules[current_rule];

			current_rule = rule.final_destination;

			for (int i = 0; i < rule.condition_count; i++)
			{
				const auto& condition = rule.conditions[i];

				const int first_operand = part[condition.field];
				const int second_operand = condition.value;

				const bool result = (condition.operation == '<')
					? (first_operand < second_operand)
					: (first_operand > second_operand);

				if (result)
				{
					current_rule = condition.destination;
					break;
				}
			}
		}
		while (current_rule[0] != 'A' && current_rule[0] != 'R');

		if (current_rule[0] == 'A')
			total += std::accumulate(part.begin(), part.end(), 0);
	}

	std::cout << total;
}