#include <iostream>
#include <string>
#include <vector>
#include <set>

struct Point
{
	int x, y;
};

int main(int _, const char*[])
{
	std::vector<Point> galaxies;
	std::set<int> xs, ys;

	int y = 0;

	for (std::string line; std::getline(std::cin, line); y++)
	{
		for (int x = 0; x < static_cast<int>(line.size()); x++)
		{
			if (line[x] == '#')
			{
				galaxies.emplace_back(x, y);
				xs.insert(x);
				ys.insert(y);
			}
		}
	}

	const int max_x = *xs.rbegin();
	const int max_y = *ys.rbegin();

	std::vector<int> cumulative_dist_x, cumulative_dist_y;
	int cdx = 0, cdy = 0;

	for (int x = 0; x <= max_x; x++)
	{
		cumulative_dist_x.push_back(cdx);
		cdx += xs.contains(x) ? 1 : 1'000'000;
	}

	for (int y = 0; y <= max_y; y++)
	{
		cumulative_dist_y.push_back(cdy);
		cdy += ys.contains(y) ? 1 : 1'000'000;
	}

	long long total = 0;

	for (auto a = galaxies.begin(); a != galaxies.end(); ++a)
	{
		for (auto b = std::next(a); b != galaxies.end(); ++b)
		{
			const int dx = cumulative_dist_x[b->x] - cumulative_dist_x[a->x];
			const int dy = cumulative_dist_y[b->y] - cumulative_dist_y[a->y];

			total += std::abs(dx) + std::abs(dy);
		}
	}

	std::cout << total;
}