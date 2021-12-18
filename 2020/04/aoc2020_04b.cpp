#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <cctype>
#include <algorithm> // std::all_of

const std::set<std::string> valid_eye_colours
{
	"amb",
	"blu",
	"brn",
	"gry",
	"grn",
	"hzl",
	"oth"
};

const std::map<std::string, bool(*)(const std::string&)> validators
{
	{
		"byr",
		[](const std::string& value) -> bool
		{
			const int year = std::stoi(value);
			return year >= 1920 && year <= 2002;
		}
	},
	{
		"iyr",
		[](const std::string& value) -> bool
		{
			const int year = std::stoi(value);
			return year >= 2010 && year <= 2020;
		}
	},
	{
		"eyr",
		[](const std::string& value) -> bool
		{
			const int year = std::stoi(value);
			return year >= 2020 && year <= 2030;
		}
	},
	{
		"hgt",
		[](const std::string& value) -> bool
		{
			std::stringstream ss(value);

			int x;
			ss >> x;

			std::string unit;
			ss >> unit;

			if (unit == "in")
				return 59 <= x && x <= 76;

			if (unit == "cm")
				return 150 <= x && x <= 193;

			return false;
		}
	},
	{
		"hcl",
		[](const std::string& value) -> bool
		{
			if (value.size() != 7)
				return false;

			if (value[0] != '#')
				return false;

			return std::all_of(value.begin() + 1, value.end(), isxdigit);
		}
	},
	{
		"ecl",
		[](const std::string& value) -> bool
		{
			return valid_eye_colours.find(value) != valid_eye_colours.end();
		}
	},
	{
		"pid",
		[](const std::string& value) -> bool
		{
			return value.size() == 9 && std::all_of(value.begin(), value.end(), isdigit);
		}
	}
};

int main(int argc, const char* argv[])
{
	int valid_passports = 0;
	int valid_field_count = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
		{
			if (valid_field_count == 7)
				valid_passports++;

			valid_field_count = 0;
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

			const std::string value = property.substr(ix + 1);

			const auto validator = validators.find(field);
			if (validator != validators.end() && validator->second(value))
				valid_field_count++;
		}
	}

	if (valid_field_count == 7)
		valid_passports++;

	std::cout << valid_passports;

	return 0;
}