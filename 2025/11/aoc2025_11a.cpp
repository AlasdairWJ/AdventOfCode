#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <array>
#include <ranges>

auto read_all_outputs()
{
	std::map<std::string, std::set<std::string>> all_outputs;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto key = line.substr(0, 3);
		auto& outputs = all_outputs[key];

		for (std::size_t ix = 5; ix < line.size(); ix += 4)
			outputs.insert(line.substr(ix, 3));
	}

	return all_outputs;	
}

auto convert_to_ix_map(const auto& all_outputs)
{
	std::set<std::string> all_nodes;
	
	for (const auto& [key, outputs] : all_outputs)
	{
		all_nodes.insert(key);
		all_nodes.insert_range(outputs);
	}

	std::map<std::string, int> node_to_ix;

	for (const auto& [ix, node] : all_nodes | std::views::enumerate)
		node_to_ix.emplace(node, ix);

	std::vector<std::set<int>> connections(all_nodes.size());
	
	for (const auto& [ix, node] : all_nodes | std::views::enumerate)
	{
		auto& output_ixs = connections[ix];
		if (const auto it = all_outputs.find(node); it != all_outputs.end())
		{
			for (const auto& output : it->second)
				output_ixs.insert(node_to_ix[output]);
		}
	}

	return std::make_pair(node_to_ix, connections);
}

int main()
{
	const auto [node_to_ix, connections] = convert_to_ix_map(read_all_outputs());

	const int you_ix = node_to_ix.find("you")->second;
	const int out_ix = node_to_ix.find("out")->second;

	std::map<int, int> current { { you_ix, 1 } };

	int total = 0;

	while (!current.empty())
	{
		decltype(current) next;

		for (const auto& [ix, count] : current)
		{
			if (ix == out_ix)
				total += count;

			for (const int next_ix : connections[ix])
				next[next_ix] += count;
		}

		next.swap(current);
	}

	std::cout << total;
}
