#include <iostream>
#include <string>
#include <regex>
#include <ranges>

#include "../util/charconv.hpp"
#include "../../util/regex.hpp"

int main(int _, const char*[])
{
	const std::regex pattern{ "mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)" };

	int total = 0;
	bool enabled = true;

	for (std::string line; std::getline(std::cin, line); )
	{
		for (const auto match : util::matches(line, pattern))
		{
			if (match[0] == "do()")
			{
				enabled = true;
			}
			else if (match[0] == "don't()")
			{
				enabled = false;
			}
			else if (enabled)
			{
				total += util::from_chars(match[1]) * util::from_chars(match[2]);
			}
		}
	}

	std::cout << total;
}