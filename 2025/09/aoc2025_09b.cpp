#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>

#include "../util/separate.hpp"
#include "../util/charconv.hpp"

struct Point
{
	int x, y;

	Point perp() const
	{
		return Point{ y, -x };
	}
};

Point operator-(const Point a, const Point b)
{
	return Point{ a.x - b.x, a.y - b.y };
}

int dot(const Point a, const Point b)
{
	return a.x * b.x + a.y * b.y;
}

struct Rect
{
	int x1, y1, x2, y2;

	Rect(const Point& a, const Point& b)
	{
		x1 = std::min(a.x, b.x);
		y1 = std::min(a.y, b.y);
		x2 = std::max(a.x, b.x);
		y2 = std::max(a.y, b.y);
	}

	bool strictly_intersects(const Rect& other) const
	{
		return (other.x1 < x2) && (x1 < other.x2)
	 		&& (other.y1 < y2) && (y1 < other.y2);
	}

	long long area() const
	{
		return long long{ x2 - x1 + 1 } * long long{ y2 - y1 + 1 };
	}
};

bool is_counter_clockwise(const Point& a, const Point& b, const Point& c)
{
	return dot(b - a, (c - b).perp()) < 0;
}

int main()
{
	std::vector<Point> tiles;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto [x_str, y_str] = util::separate(line, ',');
		tiles.push_back(Point{ *util::parse(x_str), *util::parse(y_str) });
	}

	// add so we can go over all adjacent triples
	tiles.push_back(tiles[0]);
	tiles.push_back(tiles[1]);

	std::vector<Rect> to_avoid;

	for (const auto& [a, b, c] : tiles | std::views::adjacent<3>)
	{
		if (is_counter_clockwise(a, b, c))
			to_avoid.push_back(Rect{ a, c });
	}

	std::vector<long long> areas;

	// ignore the ones i added
	const auto end = tiles.end() - 2;

	for (auto it_a = tiles.begin(); it_a != end; ++it_a)
	for (auto it_b = it_a + 1; it_b != end; ++it_b)
	{
		const Rect rect{ *it_a, *it_b };

		const auto valid = std::ranges::none_of(
			to_avoid,
			[=](const auto& r) { return rect.strictly_intersects(r); }
		);

		if (valid)
			areas.push_back(rect.area());
	}

	std::cout << *std::ranges::max_element(areas);
}