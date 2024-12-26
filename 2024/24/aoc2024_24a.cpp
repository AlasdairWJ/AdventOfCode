#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <map>
#include <ranges>
#include <bitset>

using Node = std::array<char, 3>;

constexpr int InputCount = 45;

Node parse_node(const std::string_view line)
{
	return Node{ line[0], line[1], line[2] };
}

Node mk_node(const char c, const int n)
{
	return Node{ c, static_cast<char>('0' + (n / 10)), static_cast<char>('0' + (n % 10)) };
}

int id(const Node& node)
{
	return 10 * (node[1] - '0') + (node[2] - '0');
}

enum class Operation : char { OR = '|', AND = '&', XOR = 'x' };

bool exec(const bool a, const Operation op, const bool b)
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

auto parse_gate(std::string_view line)
{
	const auto input0 = parse_node(line);

	line = line.substr(4);

	Operation op;

	if (line.starts_with("OR"))
	{
		line = line.substr(3);
		op = Operation::OR;
	}
	else if (line.starts_with("AND"))
	{
		line = line.substr(4);
		op = Operation::AND;
	}
	else if (line.starts_with("XOR"))
	{
		line = line.substr(4);
		op = Operation::XOR;
	}

	const auto input1 = parse_node(line);

	line = line.substr(7);

	const auto output = parse_node(line);

	return std::make_pair(output, std::make_tuple(input0, op, input1));
}

std::map<Node, std::tuple<Node, Operation, Node>> gates;

bool value_of(const Node& node, const auto& xs, const auto& ys)
{
	if (node[0] == 'x')
		return xs[id(node)];

	if (node[0] == 'y')
		return ys[id(node)];

	const auto it = gates.find(node);

	if (it == gates.end())
		return false;

	const auto [left, op, right] = it->second;

	return exec(value_of(left, xs, ys), op, value_of(right, xs, ys));
}

int main(int _, const char*[])
{
	std::bitset<InputCount> xs{}; 
	std::bitset<InputCount> ys{};

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
	{
		const auto node = parse_node(line);
		(node[0] == 'x' ? xs : ys).set(id(node), line[5] == '1');
	}

	for (std::string line; std::getline(std::cin, line); )
		gates.emplace(parse_gate(line));

	std::bitset<InputCount + 1> zs{};

	for (int n = 0; n <= InputCount; n++)
		zs.set(n, value_of(mk_node('z', n), xs, ys));

	std::cout << zs.to_ullong();
}
