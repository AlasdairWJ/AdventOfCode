#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <ranges>

auto inserter(auto& c) { return std::inserter(c, c.end()); }

auto above(const auto& container, const auto& key)
{
	return std::ranges::subrange(container.lower_bound(key), container.end());
}

int main(int _, const char*[])
{
	std::set<std::string> nodes;
	std::map<std::string, std::set<std::string>> connections;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::string a = line.substr(0, 2);
		std::string b = line.substr(3, 2);

		connections[a].insert(b);
		connections[b].insert(a);
		nodes.insert(a);
		nodes.insert(b);
	}

	int count = 0;

	for (const auto& a : nodes)
	{
		const auto& a_connections = connections.find(a)->second;

		for (const auto& b : above(a_connections, a))
		{
			const auto& b_connections = connections.find(b)->second;

			std::set<std::string> ix;
			std::ranges::set_intersection(a_connections, b_connections, inserter(ix));

			for (const auto& c : above(ix, b))
			{
				if (a[0] == 't' || b[0] == 't' || c[0] == 't')
					count++;
			}
		}
	}

	std::cout << count;
}
