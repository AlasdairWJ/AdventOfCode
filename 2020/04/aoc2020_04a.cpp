#include <iostream>
#include <string>
#include <set>
#include <sstream>

const std::set<std::string> fields
{
	"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"
};

int main(int argc, const char* argv[])
{
	int valid_passports = 0;
	int field_count = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
		{
			if (field_count == 7)
				valid_passports++;

			field_count = 0;
			continue;
		}
		
		std::stringstream ss(line);

		std::string property;
		while (ss >> property)
		{
			const auto ix = property.find(':');

			const std::string field = property.substr(0, ix);

			if (field == "cid")
				continue;

			if (fields.find(field) != fields.end())
				field_count++;
		}
	}

	if (field_count == 7)
		valid_passports++;

	std::cout << valid_passports;

	return 0;
}