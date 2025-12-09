#include <iostream>
#include <string>
#include <vector>

#include "../util/separate.hpp"
#include "../util/charconv.hpp"

struct Point
{
	int x, y;
};

int main()
{
	std::vector<Point> tiles;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto [x_str, y_str] = util::separate(line, ',');
		tiles.push_back(Point{ *util::parse(x_str), *util::parse(y_str) });
	}

	const auto size = tiles.size();
	std::vector<long long> areas((size * (size - 1) / 2));
	auto areas_it = areas.begin();

	for (auto it_a = tiles.begin(); it_a != tiles.end(); ++it_a)
	for (auto it_b = it_a + 1; it_b != tiles.end(); ++it_b)
		*(areas_it++) = long long{ std::abs(it_b->x - it_a->x) + 1 } * long long{ std::abs(it_b->y - it_a->y) + 1 };

	std::cout << *std::ranges::max_element(areas);
}