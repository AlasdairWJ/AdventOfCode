#include <iostream>
#include <string>
#include <regex>
#include <ranges>

#include "../../util/charconv.hpp"

auto all_matches(const std::string& line, const std::regex& pattern)
{
	return std::ranges::subrange(
		std::sregex_iterator(line.begin(), line.end(), pattern),
		std::sregex_iterator()
	);
}

int main(int _, const char*[])
{
	const std::regex pattern{ "mul\\((\\d+),(\\d+)\\)" };

	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		for (const auto match : all_matches(line, pattern))
		{
			int a, b;

			util::from_chars(match[1], a);
			util::from_chars(match[2], b);

			total += a * b;
		}
	}

	std::cout << total;
}