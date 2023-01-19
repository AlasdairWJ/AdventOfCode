#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> //std::vector
#include <regex> // std::regex, std::smatch, std::regex_match
#include <optional> // std::optional
#include <algorithm> // std::sort

struct Monkey
{
	int id;

	std::vector<__int64> items;

	std::optional<__int64> first_operand;
	char operation;
	std::optional<__int64> second_operand;

	__int64 test_value;

	int target_if_true;
	int target_if_false;

	__int64 operate(const __int64 old_value) const
	{
		const __int64 a = first_operand.value_or(old_value);
		const __int64 b = second_operand.value_or(old_value);
		switch (operation)
		{
		case '+': return a + b;
		case '*': return a * b;
		default: return 0;
		}
	}

	int target_of(__int64 item) const
	{
		return (item % test_value == 0) ? target_if_true : target_if_false;
	}
};

int main(int argc, const char* argv[])
{
	std::vector<Monkey> monkeys;

	__int64 modulo = 1;

	std::string line;
	while (std::getline(std::cin, line))
	{
		Monkey monkey;

		// Id

		sscanf_s(line.c_str(), "Monkey %d:", &monkey.id);

		// Starting Items

		std::getline(std::cin, line);

		static const std::regex starting_items_pattern{ "\\d+(?=, |$)" };

		const auto starting_items_begin = std::sregex_iterator(line.begin(), line.end(), starting_items_pattern);
		const auto starting_items_end = std::sregex_iterator();

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
		sscanf_s(line.c_str(), "  Test: divisible by %lld", &monkey.test_value);

		modulo *= monkey.test_value;

		std::getline(std::cin, line);
		sscanf_s(line.c_str(), "    If true: throw to monkey %d", &monkey.target_if_true);

		std::getline(std::cin, line);
		sscanf_s(line.c_str(), "    If false: throw to monkey %d", &monkey.target_if_false);

		std::getline(std::cin, line);

		monkeys.push_back(monkey);
	}

	std::vector<int> inspection_counts(monkeys.size());
	for (int round = 0; round < 10'000; round++)
	{
		for (auto& monkey : monkeys)
		{
			inspection_counts[monkey.id] += monkey.items.size();

			for (__int64 item : monkey.items)
			{
				item = monkey.operate(item) % modulo;
				const int target = monkey.target_of(item);
				monkeys[target].items.push_back(item);
			}

			monkey.items.clear();
		}
	}

	std::sort(inspection_counts.rbegin(), inspection_counts.rend());

	std::cout << (__int64)inspection_counts[0] * inspection_counts[1];

	return 0;
}