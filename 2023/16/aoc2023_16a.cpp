#include <iostream>
#include <string> // std::getline
#include <vector>
#include <algorithm> // std::ranges::count

struct Point
{
	int x, y;

	auto operator<=>(const Point&) const = default;

	Point operator+(const Point& other)
	{
		return Point{
			x + other.x,
			y + other.y
		};
	}

	Point& operator+=(const Point& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
};

struct Projector
{
	Projector(const std::vector<std::string>& grid)
		: _grid(grid)
		, _energized(grid.size(), std::string(grid.front().size(), '.'))
		, _width(grid.front().size())
		, _height(grid.size())
	{
	}

	void operator()(Point position = Point{}, Point direction = Point{ 1, 0 })
	{
		while (position.x >= 0 && position.x < _width && position.y >= 0 && position.y < _height)
		{
			_energized[position.y][position.x] = '#';

			switch (_grid[position.y][position.x])
			{
			case '\\':
				if (direction.x == 0)
				{
					// vertical
					direction.x = direction.y;
					direction.y = 0;
				}
				else
				{
					// horizontal
					direction.y = direction.x;
					direction.x = 0;
				}
				break;

			case '/':
				if (direction.x == 0)
				{
					// horizontal
					direction.x = -direction.y;
					direction.y = 0;
				}
				else
				{
					// vertical
					direction.y = -direction.x;
					direction.x = 0;
				}
				break;

			case '|':
				if (direction.y == 0)
				{
					_grid[position.y][position.x] = 'X';

					direction.y = direction.x;
					direction.x = 0;
					operator()(position + direction, direction);
					
					direction.y = -direction.y;
				}
				break;

			case '-':
				if (direction.x == 0)
				{
					_grid[position.y][position.x] = 'X';

					direction.x = direction.y;
					direction.y = 0;
					operator()(position + direction, direction);
					
					direction.x = -direction.x;
				}
				break;

			case '.': break;
			default: return;
			}

			position += direction;
		}
	}

	int energizedCount() const
	{
		int total = 0;

		for (const auto& row : _energized)
			total += std::ranges::count(row, '#');

		return total;
	}

private:
	const std::size_t _width, _height;
	std::vector<std::string> _grid;
	std::vector<std::string> _energized;
};

int main(int _, const char*[])
{
	std::vector<std::string> grid;

	for (std::string line; std::getline(std::cin, line); )
		grid.push_back(line);

	Projector proj{ grid };
	proj();
	std::cout << proj.energizedCount();
}