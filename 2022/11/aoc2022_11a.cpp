#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> //std::vector
#include <regex> // std::regex, std::smatch, std::regex_match
#include <optional> // std::optional
#include <algorithm> // std::sort
#include <ranges> // std::ranges::subrange, std::views::transform

struct Monkey
{
	int id;

	std::vector<int> items;

	std::optional<int> first_operand;
	char operation;
	std::optional<int> second_operand;

	int test_value;

	int target_if_true;
	int target_if_false;

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

	int target_of(int item) const
	{
		return (item % test_value == 0) ? target_if_true : target_if_false;
	}
};

int main(int argc, const char* argv[])
{
	std::vector<Monkey> monkeys;

	std::string line;
	while (std::getline(std::cin, line))
	{
		Monkey monkey;

		// Id

		sscanf_s(line.c_str(), "Monkey %d:", &monkey.id);

		// Starting Items

		std::getline(std::cin, line);

		static const std::regex starting_items_pattern{ "\\d+(?=, |$)" };

		auto begin = std::sregex_iterator(line.begin(), line.end(), starting_items_pattern);
		auto end = std::sregex_iterator();

		auto to_int = [](const auto match) { return std::stoi(match.str()); };

		const auto items = std::ranges::subrange(begin, end) | std::views::transform(to_int);

		monkey.items.assign(items.begin(), items.end());

		// Operation

		static const std::regex operation_pattern{ "^  Operation: new = (\\d+|old) (\\+|\\*) (\\d+|old)$" };

		std::getline(std::cin, line);

		std::smatch match;
		if (std::regex_match(line, match, operation_pattern))
		{
			if (match.str(1) != "old") monkey.first_operand = std::stoi(match.str(1));
			monkey.operation = match.str(2).front();
			if (match.str(3) != "old") monkey.second_operand = std::stoi(match.str(3));
		}

		// Test

		std::getline(std::cin, line);
		sscanf_s(line.c_str(), "  Test: divisible by %d", &monkey.test_value);

		std::getline(std::cin, line);
		sscanf_s(line.c_str(), "    If true: throw to monkey %d", &monkey.target_if_true);

		std::getline(std::cin, line);
		sscanf_s(line.c_str(), "    If false: throw to monkey %d", &monkey.target_if_false);

		std::getline(std::cin, line);

		monkeys.push_back(monkey);
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

	std::sort(inspection_counts.rbegin(), inspection_counts.rend());

	std::cout << inspection_counts[0] * inspection_counts[1];

	return 0;
}