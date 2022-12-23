#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

struct Monkey
{
	int id;
	
	std::vector<int> items;
	
	bool is_first_operand_old;
	int first_operand;

	char operation;

	bool is_second_operand_old;
	int second_operand;

	int test_value;

	int target_if_true;
	int target_if_false;

	int operate(const int old_value) const
	{
		const int a = is_first_operand_old ? old_value : first_operand;
		const int b = is_second_operand_old ? old_value : second_operand;
		switch (operation)
		{
		case '+': return a + b;
		case '*': return a * b;
		default: return 0;
		}
	}

	int target_of(int item)
	{
		return (item % test_value == 0) ? target_if_true : target_if_false;
	}
};

int main(int argc, const char* argv[])
{
	const std::regex operation_pattern("^  Operation: new = ([^ ]+) (.) ([^ ]+)$");
	std::vector<Monkey> monkeys;

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		Monkey monkey;

		// Id

		sscanf_s(buffer.c_str(), "Monkey %d:", &monkey.id);

		// Starting Items

		std::getline(std::cin, buffer);
		
		const char* ptr = &buffer[18];
		while (true)
		{
			char* end;
			const int value = std::strtol(ptr, &end, 10);
			monkey.items.push_back(value);
			ptr = end;

			if (*ptr == '\0')
				break;

			ptr += 2;
		}

		// Operation

		std::getline(std::cin, buffer);

		std::smatch match;
		if (std::regex_match(buffer, match, operation_pattern))
		{
			if (match.str(1) == "old")
			{
				monkey.is_first_operand_old = true;
				monkey.first_operand = 0;
			}
			else
			{
				monkey.is_first_operand_old = false;
				monkey.first_operand = std::stoi(match.str(1));
			}

			monkey.operation = match.str(2).front();

			if (match.str(3) == "old")
			{
				monkey.is_second_operand_old = true;
				monkey.second_operand = 0;
			}
			else
			{
				monkey.is_second_operand_old = false;
				monkey.second_operand = std::stoi(match.str(3));
			}
		}

		// Test

		std::getline(std::cin, buffer);
		sscanf_s(buffer.c_str(), "  Test: divisible by %d", &monkey.test_value);

		std::getline(std::cin, buffer);
		sscanf_s(buffer.c_str(), "    If true: throw to monkey %d", &monkey.target_if_true);
		
		std::getline(std::cin, buffer);
		sscanf_s(buffer.c_str(), "    If false: throw to monkey %d", &monkey.target_if_false);

		std::getline(std::cin, buffer);

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