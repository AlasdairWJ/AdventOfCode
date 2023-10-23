#include <iostream>
#include <string>
#include <regex>
#include <bitset>
#include <map>
#include <algorithm> // std::ranges::reverse
#include <numeric> // std::accumulate
#include <ranges> // std::views::values

const std::regex mem_re{ "mem\\[(\\d+)\\] \\= (\\d+)" };

int main(int _, const char*[])
{
	std::map<int, unsigned long long> memory;

	std::string mask;
	for (std::string line; std::getline(std::cin, line); )
	{
		if (line.starts_with("mask"))
		{
			mask = line.substr(7);
			std::ranges::reverse(mask);
		}
		else
		{
			std::cmatch match;
			if (std::regex_match(line.c_str(), match, mem_re))
			{
				const int position = std::strtol(match[1].first, nullptr, 10);
				std::bitset<64> value{ std::strtoull(match[2].first, nullptr, 10) };

				for (int i = 0; i < mask.size(); i++)
				{
					switch (mask[i])
					{
					case '0':
						value.reset(i);
						break;

					case '1':
						value.set(i);
						break;

					default:
						break;
					}
				}

				memory[position] = value.to_ullong();
			}
		}
	}

	auto values = memory | std::views::values;
	std::cout << std::accumulate(values.begin(), values.end(), 0ull);
}