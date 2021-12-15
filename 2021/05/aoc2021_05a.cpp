#include <iostream>
#include <vector>
#include <cmath> // abs
#include <climits> // INT_MAX, INT_MIN
#include <algorithm> // std::count_if

int sgn(const int val) { return (0 < val) - (val < 0); }
int max(const int a, const int b) { return a > b ? a : b; }

struct Line { int x1, y1, x2, y2; };

int main(int argc, const char* argv[])
{
	std::vector<Line> lines;
	int min_x = INT_MAX, min_y = INT_MAX;
	int max_x = INT_MIN, max_y = INT_MIN; 

	Line l;
	while (scanf_s("%d,%d -> %d,%d", &l.x1, &l.y1, &l.x2, &l.y2) == 4)
	{
		if (l.x1 != l.x2 && l.y1 != l.y2)
			continue;

		if (l.x1 < min_x) min_x = l.x1;
		if (l.y1 < min_y) min_y = l.y1;
		if (l.x1 > max_x) max_x = l.x1;
		if (l.y1 > max_y) max_y = l.y1;

		if (l.x2 < min_x) min_x = l.x2;
		if (l.y2 < min_y) min_y = l.y2;
		if (l.x2 > max_x) max_x = l.x2;
		if (l.y2 > max_y) max_y = l.y2;

		lines.push_back(l);
	}

	const int range_x = max_x - min_x + 1;
	const int range_y = max_y - min_y + 1;

	std::vector<int> data(range_x * range_y);

	for (const Line& l : lines)
	{
		const int dx = sgn(l.x2 - l.x1), dy = sgn(l.y2 - l.y1);
		const int _n = max(abs(l.x2 - l.x1), abs(l.y2 - l.y1));
		for (int x = l.x1, y = l.y1, n = 0; n <= _n; x += dx, y += dy, n++)
			data[(x - min_x) + range_x * (y - min_y)]++;
	}

	std::cout << std::count_if(data.begin(), data.end(), [](const int v) { return v >= 2; });

	return 0;
}