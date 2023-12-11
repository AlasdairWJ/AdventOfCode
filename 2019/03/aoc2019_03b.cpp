#include <iostream>
#include <vector>
#include <ranges>

struct Point
{
	int x, y;
};

Point delta(const char direction)
{
	switch (direction)
	{
	case 'L': return Point{ -1,  0 };
	case 'R': return Point{  1,  0 };
	case 'U': return Point{  0, -1 };
	case 'D': return Point{  0,  1 };
	default: return Point{};
	};
}

bool in_range(const int x, const int x1, const int x2)
{
	return (x1 < x2) ? (x > x1 && x <= x2) : (x < x1 && x >= x2);
}

bool intersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2, Point& p)
{
	const int adx = a2.x - a1.x, ady = a2.y - a1.y;
	const int bdx = b2.x - b1.x, bdy = b2.y - b1.y;
	
	if (bdy * adx == ady * bdx)
		return false;

	if (adx == 0)
	{
		p = Point{ a1.x, b1.y };
		return in_range(p.y, a1.y, a2.y) && in_range(p.x, b1.x, b2.x);
	}
	else
	{
		p = Point{ b1.x, a1.y };
		return in_range(p.x, a1.x, a2.x) && in_range(p.y, b1.y, b2.y);
	}
}

struct Node
{
	Point position;
	int steps;
};

int main(int argc, const char* argv[])
{
	std::vector<Node> paths[2];

	for (auto& path : paths)
	{
		auto [position, steps] = path.emplace_back();

		do
		{
			char direction;
			std::cin >> direction;

			int distance;
			std::cin >> distance;

			const auto d = delta(direction);

			position.x += distance * d.x;
			position.y += distance * d.y;
			steps += distance;

			path.emplace_back(position, steps);
		}
		while (std::cin.get() == ',');
	}

	int min_steps = -1;

	for (const auto& [a1, a2] : paths[0] | std::views::adjacent<2>)
	{
		for (const auto& [b1, b2] : paths[1] | std::views::adjacent<2>)
		{
			if (Point p; intersect(a1.position, a2.position, b1.position, b2.position, p))
			{
				const int steps{
					a1.steps + std::abs(p.x - a1.position.x) + std::abs(p.y - a1.position.y) +
					b1.steps + std::abs(p.x - b1.position.x) + std::abs(p.y - b1.position.y)
				};
				
				if (min_steps < 0 || steps < min_steps)
					min_steps = steps;
			}
		}
	}

	std::cout << min_steps;
}