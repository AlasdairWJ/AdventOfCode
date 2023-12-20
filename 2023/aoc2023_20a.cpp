#include <iostream>
#include <string> // std::getline
#include <string_view>
#include <vector>
#include <map>
#include <ranges> // std::views::split
#include <algorithm> // std::ranges::all_of

enum class Type
{
	None,
	FlipFlop,
	Conjunction
};

constexpr bool Low = false;
constexpr bool High = true;

constexpr char Broadcaster[]{ "broadcaster" };

const std::string_view delim{ ", " };

struct Module
{
	Type type;
	std::vector<std::string> connections;
	bool state;

	std::map<std::string, bool> inputHistory;
	std::vector<std::pair<bool, std::string>> inputQueue;
};

int main(int _, const char*[])
{
	std::map<std::string, Module> modules;

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
				module.connections.emplace_back(r.begin(), r.end());
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

	long long pulses[2]{};

	for (int i = 0; i < 1'000; i++)
	{
		pulses[Low]++; // button -> broadcaster

		for (const auto& connection : broadcasterConnections)
		{
			if (auto it = modules.find(connection); it != modules.end())
			{
				it->second.inputQueue.emplace_back(Low, Broadcaster);
			}
		}

		pulses[Low] += broadcasterConnections.size();;

		for (bool update = true; update; )
		{
			update = false;

			for (auto& [moduleName, module] : modules)
			{
				std::vector<bool> outputQueue;

				for (const auto& [pulse, from] : module.inputQueue)
				{
					switch (module.type)
					{
					case Type::FlipFlop:
						if (pulse == Low)
						{
							module.state ^= true;
							outputQueue.push_back(module.state);
						}
						break;
					case Type::Conjunction:
						module.inputHistory[from] = pulse;
						module.state = std::ranges::all_of(module.inputHistory | std::views::values, std::identity{});
						outputQueue.push_back(!module.state);
						break;
					default:
						break;
					}
				}

				module.inputQueue.clear();
				update |= !outputQueue.empty();

				for (const bool pulse : outputQueue)
				{
					for (const auto& connection : module.connections)
					{
						if (auto it = modules.find(connection); it != modules.end())
						{
							it->second.inputQueue.emplace_back(pulse, moduleName);
						}
					}

					pulses[pulse] += module.connections.size();
				}
			}
		}
	}

	std::cout << pulses[0] * pulses[1];
}