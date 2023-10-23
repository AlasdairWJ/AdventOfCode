#include <iostream>
#include <string>
#include <regex>
#include <bitset>
#include <map>
#include <algorithm> // std::count, std::ranges::reverse
#include <numeric> // std::accumulate
#include <ranges> // std::views::values

const std::regex mem_re{ "mem\\[(\\d+)\\] \\= (\\d+)" };

int main(int _, const char*[])
{
	std::map<unsigned long long, unsigned long long> memory;

	unsigned limit;

	std::string mask;
	for (std::string line; std::getline(std::cin, line); )
	{
		if (line.starts_with("mask"))
		{
			mask = line.substr(7);
			std::ranges::reverse(mask);

			limit = 1u << std::count(mask.begin(), mask.end(), 'X');
		}
		else
		{
			std::cmatch match;
			if (std::regex_match(line.c_str(), match, mem_re))
			{
				std::bitset<64> position{ std::strtoull(match[1].first, nullptr, 10) };
				const unsigned long long value = std::strtoull(match[2].first, nullptr, 10);

				for (unsigned x = 0; x < limit; x++)
				{
					unsigned bit = 1;
					for (int i = 0; i < mask.size(); i++)
					{
						switch (mask[i])
						{
						case 'X':
							position.set(i, (x & bit) != 0);
							bit <<= 1;
							break;

						case '1':
							position.set(i);
							break;

						default:
							break;
						}
					}

					memory[position.to_ullong()] = value;
				}
			}
		}
	}

	auto values = memory | std::views::values;
	std::cout << std::accumulate(values.begin(), values.end(), 0ull);
}