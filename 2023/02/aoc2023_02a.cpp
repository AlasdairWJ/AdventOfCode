#include <iostream>
#include <string> // std::getline
#include <regex>
#include <string_view>
#include <ranges>
#include <map>

#include "../../util/charconv.hpp" // util::from_chars
#include "../../util/separate.hpp" // util::separate

const std::regex game_pattern{ "Game (\\d+): (.*)" };

using namespace std::literals;
namespace views = std::views;

int main(int _, const char*[])
{
	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::map<std::string, int> max_colours;

		std::smatch match;
		std::regex_match(line, match, game_pattern);

		int game_id;
		util::from_chars(match[1], game_id);

		std::string_view all_turns_sv{ match[2].first, match[2].second };

		for (const auto turn_r : all_turns_sv | views::split("; "sv))
		{
			for (const auto cube_r : turn_r | views::split(", "sv))
			{
				const auto [count_sv, colour_sv] = util::separate(cube_r);

				int count;
				util::from_chars(count_sv, count);

				int& existing_max = max_colours[std::string{ colour_sv }];
				
				if (count > existing_max)
					existing_max = count;
			}
		}

		if (max_colours["red"] <= 12 && max_colours["green"] <= 13 && max_colours["blue"] <= 14)
			total += game_id;
	}

	std::cout << total;
}