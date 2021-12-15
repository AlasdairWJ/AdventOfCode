#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::find, std::sort
#include <numeric> // std::accumulate

#ifndef SIZE
#define SIZE 100
#endif

constexpr int size = SIZE;

int grid[size][size] = {};

struct Point
{
	Point(const int x, const int y) : x(x), y(y) {};
	bool operator==(const Point& other) const { return x == other.x && y == other.y; }
	int x, y;
};

const Point offsets[] { {1,0}, {-1,0}, {0,1}, {0,-1} };

int basin_size(const std::vector<std::vector<int>>& grid, const int x, const int y)
{
	std::vector<Point> points {{ x, y }};
		
	const int h = grid.size();
	const int w = grid[0].size();

	for (int i = 0; i < points.size(); i++)
	{
		const Point p = points[i];
		const int v = grid[p.y][p.x];

		for (const Point& offset : offsets)
		{
			const Point q(p.x + offset.x, p.y + offset.y);
			if (q.x >= 0 && q.y >= 0 && q.x < w && q.y < h)
			{
				if (std::find(points.begin(), points.end(), q) == points.end())
				{
					const int hq = grid[q.y][q.x];
					if (hq != 9 && hq > v)
						points.push_back(q);
				}
			}
		}
	}

	return static_cast<int>(points.size());
}

int main(int argc, const char *argv[])
{
	std::vector<std::vector<int>> grid;

	int y = 0;
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::vector<int> row(line.size());
		std::transform(line.begin(), line.end(), row.begin(),
			[](const char l) -> int { return l - '0'; });
		grid.push_back(row);
	}

	std::vector<int> basins;

	const int h = grid.size();
	const int w = grid[0].size();
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			const int v = grid[y][x];

			if ((x == 0 || grid[y][x-1] > v) &&
				(y == 0 || grid[y-1][x] > v) && 
				(x == w-1 || grid[y][x+1] > v) &&
				(y == h-1 || grid[y+1][x] > v))
			{
				basins.push_back(basin_size(grid, x, y));
			}

		}
	}

	std::sort(basins.begin(), basins.end(), std::greater<>());
	std::cout << std::accumulate(basins.begin(), basins.begin() + 3, 1, std::multiplies<int>());

	return 0;
}