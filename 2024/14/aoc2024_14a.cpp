#include <iostream>
#include <string>
#include <regex>

#include "../util/charconv.hpp"
#include "../../util/numeric.hpp"

constexpr int Seconds = 100;

int main(const int argc, const char* argv[])
{
	int width = 101;
	int height = 103;

	if (argc >= 3)
	{
		util::from_chars(argv[1], width);
		util::from_chars(argv[2], height);
	}

	const int half_width = width / 2;
	const int half_height = height / 2;

	const std::regex velocity_pattern{ "^p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)$" };

	int regions[3][3]{};

	for (std::string line; std::getline(std::cin, line); )
	{
		std::smatch match;
		std::regex_match(line, match, velocity_pattern);

		int px = util::from_chars(match[1]);
		int py = util::from_chars(match[2]);

		const int vx = util::from_chars(match[3]);
		const int vy = util::from_chars(match[4]);

		px += Seconds * vx;
		px %= width;

		if (px < 0)
			px += width;

		py += Seconds * vy;
		py %= height;

		if (py < 0)
			py += height;

		regions[util::sign(px - half_width) + 1][util::sign(py - half_height) + 1]++;
	}

	std::cout <<
		regions[0][0] *
		regions[2][0] *
		regions[0][2] *
		regions[2][2];
}
