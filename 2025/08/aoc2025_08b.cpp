#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "../util/separate.hpp"
#include "../util/charconv.hpp"
#include "../util/symmetric_grid.hpp"

struct Point
{
	int x, y, z;
};

constexpr double sqr(const int x) { return static_cast<double>(x) * x; }

double distance(const Point& a, const Point& b)
{
	return std::sqrt(sqr(b.x - a.x) + sqr(b.y - a.y) + sqr(b.z - a.z));
}

struct Connection
{
	int ix_a;
	int ix_b;
	double distance;
};

int main()
{
	std::vector<Point> points;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto [x_str, y_str, z_str] = util::separate<3>(line, ',');
		points.push_back(Point{ *util::parse(x_str), *util::parse(y_str), *util::parse(z_str) });
	}

	const int size = static_cast<int>(points.size());

	// ========

	std::vector<Connection> connections(size * (size - 1) / 2);

	{
		auto it = connections.begin();

		for (int x = 0; x < size; x++)
		for (int y = x + 1; y < size; y++)
		{
			*(it++) = Connection{
				x, y,
				distance(points[x], points[y])
			};
		}

		std::ranges::sort(
			connections,
			[](const auto& c1, const auto& c2) { return c1.distance < c2.distance; }
		);
	}

	// ========

	util::symmetric_grid<bool> grid(size);
	std::vector<bool> visited(size);

	auto visit = [&](this auto self, const int ix) -> void
	{
		visited[ix] = true;

		for (int other_ix = 0; other_ix < size; other_ix++)
		{
			if (ix != other_ix && grid[ix, other_ix] && !visited[other_ix])
				self(other_ix);
		}
	};

	auto it = connections.begin();

	visited[it->ix_a] = true;
	visited[it->ix_b] = true;
	grid[it->ix_a, it->ix_b] = true;

	do
	{
		++it;

		grid[it->ix_a, it->ix_b] = true;

		if (visited[it->ix_a] && !visited[it->ix_b])
			visit(it->ix_b);

		if (!visited[it->ix_a] && visited[it->ix_b])
			visit(it->ix_a);
	}
	while (std::ranges::count(visited, true) != size);

	std::cout << (points[it->ix_a].x * points[it->ix_b].x);
}
