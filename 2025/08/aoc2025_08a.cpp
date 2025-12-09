#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <set>

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

int main(const int argc, const char* argv[])
{
	int connection_count = 1'000;

	if (argc >= 2)
		connection_count = util::parse(argv[1]).value_or(connection_count);

	// ========

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

		connections.resize(connection_count);
	}

	// ========

	util::symmetric_grid<bool> grid(size);
	
	for (const auto& c : connections)
		grid[c.ix_a, c.ix_b] = true;

	int total = 1;

	std::multiset<int, std::greater<int>> sizes;

	for (int i = 0; i < size; i++)
	{
		std::set<int> all;
		
		for (std::set<int> current{ i }; !current.empty(); )
		{
			all.insert_range(current);

			decltype(current) next;

			for (const int ix : current)
			{
				for (int ix2 = 0; ix2 < size; ix2++)
				{
					if (ix != ix2 && grid[ix, ix2])
					{
						grid[ix, ix2] = false;
						next.insert(ix2);
					}
				}
			}

			current.swap(next);
		}

		if (all.size() != 1)
			sizes.insert(static_cast<int>(all.size()));
	}

	std::cout << std::accumulate(sizes.begin(), std::next(sizes.begin(), 3), 1, std::multiplies{});
}

// bad: 694157312
// bad: 12688