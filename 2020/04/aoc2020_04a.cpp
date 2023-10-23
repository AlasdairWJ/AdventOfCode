#include <iostream>
#include <string>
#include <string_view>
#include <set>
#include <ranges> // std::views::split

const std::set<std::string_view> essential_fields{
	"byr",
	"iyr",
	"eyr",
	"hgt",
	"hcl",
	"ecl",
	"pid",
	"cid"
};

int main(int _, const char* [])
{
	int valid_passports = 0;

	while (std::cin)
	{
		int field_count = 0;
		
		for (std::string line; std::getline(std::cin, line) && !line.empty(); )
		{
			for (auto && r : std::views::split(line, ' '))
			{
				const std::string_view key_val_str{ r.begin(), r.end() };

				const std::size_t separator_ix = key_val_str.find(':');
				const std::string_view field = key_val_str.substr(0, separator_ix);

				if (field != "cid" && essential_fields.contains(field))
					field_count++;
			}
		}

		if (field_count == 7)
			valid_passports++;
	}

	std::cout << valid_passports;

	return 0;
}