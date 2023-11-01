#include <iostream>
#include <string> // std::getline
#include <regex> // std::regex_match

#include "../../util/charconv.hpp" // util::from_chars

const std::regex ranges_re{ "^(\\d+)-(\\d+),(\\d+)-(\\d+)$" };

int main(int _, const char*[])
{
	int count = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		if (std::smatch match; std::regex_match(line, match, ranges_re))
		{
			int lower1, upper1, lower2, upper2;
			util::from_chars(match[1], lower1);
			util::from_chars(match[2], upper1);
			util::from_chars(match[3], lower2);
			util::from_chars(match[4], upper2);

			if ((lower1 <= lower2 && upper2 <= upper1) ||
				(lower2 <= lower1 && upper1 <= upper2))
			{
				count++;
			}
		}
	}

	std::cout << count;
}