#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>

using Node = std::array<char, 2>;

std::ostream& operator<<(std::ostream& os, const Node& node)
{
	return os.write(node.data(), node.size());
}

std::map<Node, std::set<Node>> connections;

bool is_valid_addition(const auto& set, const auto& value)
{
	if (set.contains(value))
		return false;

	const auto& value_connections = connections.find(value)->second;

	for (const auto& item : set)
		if (!value_connections.contains(item))
			return false;

	return true;
}

auto above(const auto& container, const auto& key)
{
	return std::ranges::subrange(container.lower_bound(key), container.end());
}

int main(int _, const char*[])
{
	std::set<Node> nodes;
	std::set<std::set<Node>> groups;

	for (std::string line; std::getline(std::cin, line); )
	{
		const Node a{ line[0], line[1] };
		const Node b{ line[3], line[4] };

		connections[a].insert(b);
		connections[b].insert(a);

		nodes.insert(a);
		nodes.insert(b);

		groups.insert(std::set{ a, b });
	}

	while (groups.size() > 1)
	{
		decltype(groups) next;

		for (const auto& set : groups)
		{
			for (const auto& node : above(nodes, *set.rbegin()))
			{
				if (is_valid_addition(set, node))
				{
					auto copy = set;
					copy.insert(node);
					next.insert(copy);
				}
			}
		}

		groups.swap(next);
	}

	const auto& final_set = *groups.begin();

	auto it = final_set.begin();

	std::cout << *it;

	for (++it; it != final_set.end(); ++it)
		std::cout << ',' << *it;
}
