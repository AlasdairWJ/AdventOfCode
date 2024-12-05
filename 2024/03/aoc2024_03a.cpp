#include <iostream>
#include <string>
#include <regex>
#include <ranges>

#include "../util/charconv.hpp"
#include "../util/regex.hpp"

int main(int _, const char*[])
{
	const std::regex pattern{ "mul\\((\\d+),(\\d+)\\)" };

	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		for (const auto match : util::all_matches(line, pattern))
		{
			total += util::from_chars(match[1]) * util::from_chars(match[2]);
		}
	}

	std::cout << total;
}