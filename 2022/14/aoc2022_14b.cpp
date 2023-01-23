#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> //std::vector
#include <regex> // std::regex, std::sregex_token_iterator
#include <ranges> // std::ranges::subrange, std::views::drop, std::views::elements
#include <algorithm> // std::ranges::minmax_element

int compare(const int a, const int b) { return (a > b) - (a < b); }

int main(int argc, const char* argv[])
{
	using point = std::pair<int, int>;
	std::vector<std::vector<point>> all_lines;

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::vector<point> lines;

		const std::regex lines_pattern{ "\\d+,\\d+(?= \\-\\> |$)" };

		const auto begin = std::sregex_token_iterator(line.begin(), line.end(), lines_pattern);
		const auto end = std::sregex_token_iterator();

		for (const auto& match : std::ranges::subrange(begin, end))
		{
			int x, y;
			sscanf_s(match.str().c_str(), "%d,%d", &x, &y);
			lines.emplace_back(x, y);
		}

		all_lines.push_back(lines);
	}

	auto all_points = all_lines | std::views::join;

	auto all_y = std::views::elements<1>(all_points);

	const int bottom = *std::ranges::max_element(all_y) + 2;

	const int left = 500 - bottom - 1;
	const int right = 500 + bottom + 1;

	const int width = right - left + 1;
	const int height = bottom + 1;

	const auto at = [&](const int x, const int y) -> int8_t&
	{
		static std::vector<int8_t> data(width * height);
		return data[y * width + x - left];
	};

	for (int x = left; x <= right; x++)
		at(x, bottom) = true;

	for (const auto& lines : all_lines)
	{
		auto [x, y] = lines.front();
		for (const auto& [dst_x, dst_y] : lines | std::views::drop(1))
		{
			for (const int dx = compare(dst_x, x), dy = compare(dst_y, y);
				x != dst_x || y != dst_y; x += dx, y += dy)
				at(x, y) = true;
			at(x, y) = true;
		}
	}

	int units_at_rest = 0;
	int moves;
	do
	{
		int x = 500, y = 0;

		bool at_rest = false;
		moves = 0;
		while (!at_rest)
		{
			if (!at(x, y + 1))
			{
				y++;
				moves++;
			}
			else if (!at(x - 1, y + 1))
			{
				x--;
				y++;
				moves++;
			}
			else if (!at(x + 1, y + 1))
			{
				x++;
				y++;
				moves++;
			}
			else
			{
				at_rest = true;
			}
		}

		at(x, y) = true;
		units_at_rest++;
	}
	while (moves > 0);

	std::cout << units_at_rest;

	return 0;
}