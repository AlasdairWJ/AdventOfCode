#include <iostream>
#include <string> // std::getline
#include <string_view>
#include <vector>
#include <map>
#include <ranges> // std::views::split, std::views::values
#include <algorithm> // std::ranges::all_of

#include "../../util/numeric.hpp" // util::lcm

enum class Type
{
	None,
	FlipFlop,
	Conjunction
};

constexpr bool Low = false;
constexpr bool High = true;

constexpr char Broadcaster[]{ "broadcaster" };
constexpr char KJ[]{ "kj" };

const std::string_view delim{ ", " };

struct Module
{
	Type type;
	std::vector<std::string> connections;
	bool state;

	std::map<std::string, bool> inputHistory;
};

int main(int _, const char*[])
{
	std::map<std::string, Module> modules;

	// not a general case solution!
	std::map<std::string, long long> outputsToKJ;

	std::vector<std::string> broadcasterConnections;

	for (std::string line; std::getline(std::cin, line); )
	{
		if (line.starts_with(Broadcaster))
		{
			const std::size_t ix = line.find(" -> ");

			const auto connections_str = std::string_view{ line }.substr(ix + 4);
			
			for (auto && r : connections_str | std::views::split(delim))
			{
				broadcasterConnections.emplace_back(r.begin(), r.end());
			}
		}
		else
		{
			const std::size_t ix = line.find(" -> ");
			const auto name = line.substr(1, ix - 1);

			auto& module = modules[name];
			module.type = (line[0] == '%') ? Type::FlipFlop : Type::Conjunction;
			module.state = false;

			const auto connections_str = std::string_view{ line }.substr(ix + 4);
			for (auto && r : connections_str | std::views::split(delim))
			{
				const auto& newConnection = module.connections.emplace_back(r.begin(), r.end());

				if (newConnection == KJ)
				{
					outputsToKJ.emplace(name, 0);
				}
			}
		}
	}

	for (const auto& connection : broadcasterConnections)
	{
		if (auto it = modules.find(connection); it != modules.end())
		{
			it->second.inputHistory[Broadcaster] = false;
		}
	}

	for (const auto& [moduleName, module] : modules)
	{
		for (const auto& connection : module.connections)
		{
			if (auto it = modules.find(connection); it != modules.end())
			{
				it->second.inputHistory[moduleName] = false;
			}
		}
	}

	int output_pulses_found = 0;

	for (int buttonPresses = 1; output_pulses_found != 4; buttonPresses++)
	{
		std::vector<std::pair<std::string, bool>> pulseBuffer;
		
		pulseBuffer.emplace_back(Broadcaster, Low);

		while (!pulseBuffer.empty())
		{
			decltype(pulseBuffer) nextPulseBuffer;

			for (const auto& [source, state] : pulseBuffer)
			{
				const auto& destinations = (source == Broadcaster)
					? broadcasterConnections
					: modules.find(source)->second.connections;

				for (const auto& destination : destinations)
				{
					auto it = modules.find(destination);
					if (it == modules.end())
						continue;

					if (auto it = outputsToKJ.find(destination); it != outputsToKJ.end() && state == Low)
					{
						it->second = buttonPresses;
						output_pulses_found++;
					}

					auto& module = it->second;

					switch (module.type)
					{
					case Type::FlipFlop:
						if (state == Low)
						{
							module.state ^= true;
							nextPulseBuffer.emplace_back(destination, module.state);
						}
						break;
					case Type::Conjunction:
						module.inputHistory[source] = state;
						module.state = std::ranges::all_of(module.inputHistory | std::views::values, std::identity{});
						if (modules.contains(destination))
							nextPulseBuffer.emplace_back(destination, !module.state);
						break;
					default:
						break;
					}
				}
			}

			pulseBuffer.swap(nextPulseBuffer);
		}
	}

	std::cout << util::lcm(outputsToKJ | std::views::values);
}