#include <iostream>
#include <string>
#include <regex>
#include <charconv> // std::from_chars

const std::regex policy_password_re{ "^(\\d+)\\-(\\d+) (\\w): (\\w+)$" };

int main(int _, const char*[])
{
	int valid_count = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::cmatch match;
		if (std::regex_match(line.c_str(), match, policy_password_re))
		{
			int lower;
			std::from_chars(match[1].first, match[1].second, lower);

			int upper;
			std::from_chars(match[2].first, match[2].second, upper);

			const char letter = *match[3].first;

			const std::string password = match[4];

			if ((password[lower-1] == letter) != (password[upper-1] == letter))
				valid_count++;
		}		
	}

	std::cout << valid_count;
}