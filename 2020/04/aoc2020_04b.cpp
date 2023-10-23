#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <set>
#include <ranges> // std::views::split
#include <cctype> // std::isdigit, std::isxdigit
#include <algorithm> // std::all_of
#include <charconv> // std::from_chars

template <typename T>
auto from_chars(const std::string_view text, T& value)
{
	return std::from_chars(text.data(), text.data() + text.size(), value);
}

using validator_t = bool(*)(std::string_view);

bool validate_byr(const std::string_view text)
{
	int year{};
	const auto [_, ec] = from_chars(text, year);
	return ec == std::errc{} && year >= 1920 && year <= 2002;
}

bool validate_iyr(const std::string_view text)
{
	int year{};
	const auto [_, ec] = from_chars(text, year);
	return ec == std::errc{} && year >= 2010 && year <= 2020;
}

bool validate_eyr(const std::string_view text)
{
	int year{};
	const auto [_, ec] = from_chars(text, year);
	return ec == std::errc{} && year >= 2020 && year <= 2030;
}

bool validate_hgt(const std::string_view text)
{
	int x;
	const auto [ptr, ec] = from_chars(text, x);

	if (ec != std::errc{})
		return false;

	const std::string_view unit{ ptr, text.data() + text.size() };

	if (unit == "in")
		return 59 <= x && x <= 76;

	if (unit == "cm")
		return 150 <= x && x <= 193;

	return false;
}

bool validate_hcl(const std::string_view text)
{
	return
		(text.size() == 7) &&
		(text[0] == '#') && 
		std::all_of(text.begin() + 1, text.end(), std::isxdigit);
}

const std::set<std::string_view> valid_eye_colours
{
	"amb",
	"blu",
	"brn",
	"gry",
	"grn",
	"hzl",
	"oth"
};

bool validate_ecl(const std::string_view text)
{
	return valid_eye_colours.contains(text);
}

bool validate_pid(const std::string_view text)
{
	return 
		(text.size() == 9) && 
		std::all_of(text.begin(), text.end(), std::isdigit);
}

const std::map<std::string_view, validator_t> validators{
	{ "byr", validate_byr },
	{ "iyr", validate_iyr },
	{ "eyr", validate_eyr },
	{ "hgt", validate_hgt },
	{ "hcl", validate_hcl },
	{ "ecl", validate_ecl },
	{ "pid", validate_pid }
};

int main(int _, const char*[])
{
	int valid_passports = 0;

	while (std::cin)
	{
		int valid_field_count = 0;
		
		for (std::string line; std::getline(std::cin, line) && !line.empty(); )
		{
			for (auto && r : std::views::split(line, ' '))
			{
				const std::string_view key_val_str{ r.begin(), r.end() };

				const std::size_t separator_ix = key_val_str.find(':');
				const std::string_view field = key_val_str.substr(0, separator_ix);
				const std::string_view value = key_val_str.substr(separator_ix + 1);

				if (field != "cid")
				{
					const auto validator_it = validators.find(field);
					if (validator_it != validators.end())
					{
						if (validator_it->second(value))
							valid_field_count++;
					}
				}
			}
		}

		if (valid_field_count == 7)
			valid_passports++;
	}

	std::cout << valid_passports;
}