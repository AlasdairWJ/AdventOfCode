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

	const int svr_ix = node_to_ix.find("svr")->second;
	const int dac_ix = node_to_ix.find("dac")->second;
	const int fft_ix = node_to_ix.find("fft")->second;
	const int out_ix = node_to_ix.find("out")->second;

	constexpr int NONE = 0x0;
	constexpr int DAC = 0x1;
	constexpr int FFT = 0x2;
	constexpr int BOTH = 0x3;

	using State = std::array<long long, 4>;

	std::map<int, State> current { { svr_ix, { 1, 0, 0, 0 } } };

	long long total = 0;

	while (!current.empty())
	{
		decltype(current) next;

		for (const auto& [ix, counts] : current)
		{
			if (ix == out_ix)
				total += counts[BOTH];

			for (const int next_ix : connections[ix])
			{
				auto& next_counts = next[next_ix];

				if (next_ix == dac_ix)
				{
					next_counts[DAC] += counts[NONE] + counts[DAC];
					next_counts[BOTH] += counts[FFT] + counts[BOTH];
				}
				else if (next_ix == fft_ix)
				{
					next_counts[FFT] += counts[NONE] + counts[FFT];
					next_counts[BOTH] += counts[DAC] + counts[BOTH];
				}
				else
				{
					next_counts[NONE] += counts[NONE];
					next_counts[DAC] += counts[DAC];
					next_counts[FFT] += counts[FFT];
					next_counts[BOTH] += counts[BOTH];
				}
			}
		}

		next.swap(current);
	}

	std::cout << total;
}
