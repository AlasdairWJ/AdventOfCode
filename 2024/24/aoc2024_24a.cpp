#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <ranges>

using Node = std::array<char, 3>;

std::ostream& operator<<(std::ostream& os, const Node& node)
{
	return os.write(node.data(), node.size());
}

Node parse(const std::string_view line)
{
	return Node{ line[0], line[1], line[2] };
}

enum class Operation : char { OR = '|', AND = '&', XOR = 'x' };

bool exec(const Operation op, const bool a, const bool b)
{
	switch (op)
	{
	case Operation::OR:
		return (a || b);
	case Operation::AND:
		return (a && b);
	case Operation::XOR:
		return (a != b);
	default:
		return false;
	}
}

struct Gate
{
	Node inputs[2];
	Operation op;
	Node output;
	bool current_value;
	bool next_value;

	void set(const bool a, const bool b)
	{
		next_value = exec(op, a, b);
	}
};

void parse(std::string_view line, Gate& gate)
{
	gate.inputs[0] = parse(line);

	line = line.substr(4);

	if (line.starts_with("OR"))
	{
		gate.op = Operation::OR;
		line = line.substr(3);
	}
	else if (line.starts_with("AND"))
	{
		gate.op = Operation::AND;
		line = line.substr(4);
	}
	else if (line.starts_with("XOR"))
	{
		gate.op = Operation::XOR;
		line = line.substr(4);
	}

	gate.inputs[1] = parse(line);

	line = line.substr(7);

	gate.output = parse(line);
}

int main(int _, const char*[])
{
	std::map<Node, bool> state;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
		state.emplace(parse(line), (line[5] == '1'));

	std::vector<Gate> gates;

	for (std::string line; std::getline(std::cin, line); )
	{
		auto& gate = gates.emplace_back();
		parse(line, gate);

		state.emplace(gate.output, false);
	}

	for (;;)
	{
		for (auto& gate : gates)
		{
			const bool a = state[gate.inputs[0]];
			const bool b = state[gate.inputs[1]];

			gate.set(a, b);
		}

		bool any_updates = false;

		for (auto& gate : gates)
		{
			if (gate.current_value != gate.next_value)
			{
				any_updates = true;
				state[gate.output] = gate.next_value;
				gate.current_value = gate.next_value;
			}
		}

		if (!any_updates)
			break;
	}

	const auto lower_it = state.lower_bound(Node{ 'z', '0', '0' });
	const auto upper_it = state.upper_bound(Node{ 'z', '9', '9' });

	const auto zs = std::ranges::subrange(lower_it, upper_it);

	long long x = 0;

	for (const bool v : zs | std::views::values | std::views::reverse)
	{
		x <<= 1;
		x |= v;
	}

	std::cout << x;
}
