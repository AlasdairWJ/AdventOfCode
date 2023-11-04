#include <iostream>
#include <string> // std::getline
#include <vector>
#include <regex>
#include <optional>
#include <algorithm> // std::ranges::sort
#include <ranges> // std::ranges::subrange, std::views::reverse

#include "../../util/charconv.hpp" // util::from_chars

const std::regex monkey_id_re{ "^Monkey (\\d+):$"};
const std::regex starting_items_re{ "^\\s+Starting items: (.*)$"};
const std::regex operation_re{ "^\\s+Operation: new = (.+) ([+*]) (.+)$"};
const std::regex test_divisible_re{ "^\\s+Test: divisible by (\\d+)$"};
const std::regex outcome_re{ "^\\s+If .+: throw to monkey (\\d+)$"};

struct Monkey
{
	int id;

	std::vector<int> items;

	std::optional<int> first_operand;
	char operation;
	std::optional<int> second_operand;

	int test_value;

	int targets[2];

	int operate(const int old_value) const
	{
		const int a = first_operand.value_or(old_value);
		const int b = second_operand.value_or(old_value);
		switch (operation)
		{
		case '+': return a + b;
		case '*': return a * b;
		default: return 0;
		}
	}

	int target_of(const int item) const
	{
		return targets[item % test_value == 0];
	}
};

int main(int _, const char*[])
{
	std::vector<Monkey> monkeys;

	for (std::string line; std::getline(std::cin, line); )
	{
		auto& monkey = monkeys.emplace_back();

		// Id
		std::smatch match;
		std::regex_match(line, match, monkey_id_re);
		util::from_chars(match[1], monkey.id);

		// Starting Items
		std::getline(std::cin, line);
		std::regex_match(line, match, starting_items_re);
		for (auto && r : match.str(1) | std::views::split(std::string{ ", " }))
		{
			if (int value; util::from_chars(r, value))
				monkey.items.push_back(value);
		}

		// Operation
		std::getline(std::cin, line);
		std::regex_match(line, match, operation_re);

		if (const auto first_op = match.str(1); first_op != "old")
			monkey.first_operand = std::stoi(first_op);

		monkey.operation = *match[2].first;
		
		if (const auto second_op = match.str(3); second_op != "old")
			monkey.second_operand = std::stoi(second_op);

		// Test
		std::getline(std::cin, line);
		std::regex_match(line, match, test_divisible_re);
		util::from_chars(match[1], monkey.test_value);

		// If true
		std::getline(std::cin, line);
		std::regex_match(line, match, outcome_re);
		util::from_chars(match[1], monkey.targets[true]);

		// If false
		std::getline(std::cin, line);
		std::regex_match(line, match, outcome_re);
		util::from_chars(match[1], monkey.targets[false]);

		std::getline(std::cin, line);
	}

	std::vector<int> inspection_counts(monkeys.size());
	for (int round = 0; round < 20; round++)
	{
		for (auto& monkey : monkeys)
		{
			inspection_counts[monkey.id] += monkey.items.size();

			for (int item : monkey.items)
			{
				item = monkey.operate(item);
				item /= 3;
				const int target = monkey.target_of(item);
				monkeys[target].items.push_back(item);
			}

			monkey.items.clear();
		}
	}

	std::ranges::sort(inspection_counts | std::views::reverse);

	std::cout << inspection_counts[0] * inspection_counts[1];
}