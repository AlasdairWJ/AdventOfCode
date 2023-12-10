#include <iostream>
#include <string>
#include <vector>

struct Position
{
	int x, y;

	auto operator<=>(const Position&) const = default;
};

enum class Direction
{
	Any, Up, Down, Left, Right
};

int main(int _, const char*[])
{
	Position start{ -1, -1 };
	std::vector<std::string> grid;

	for (std::string line; std::getline(std::cin, line); )
	{
		if (start.x < 0)
		{
			const std::size_t ix = line.find('S');
			if (ix != std::string::npos)
			{
				start.x = static_cast<int>(ix);
				start.y = static_cast<int>(grid.size());
			}
		}

		grid.push_back(line);
	}

	const int max_x = static_cast<int>(grid.front().size() - 1);
	const int max_y = static_cast<int>(grid.size() - 1);

	// recalculate S
	{
		bool up = false, left = false, right = false, down = false;

		if (start.y != 0)
		{
			const char above = grid[start.y - 1][start.x];
			up = (above == '|' || above == 'F' || above == '7');
		}

		if (start.x != 0)
		{
			const char beside = grid[start.y][start.x - 1];
			left = (beside == '-' || beside == 'F' || beside == 'L');
		}

		if (start.y < max_y)
		{
			const char below = grid[start.y + 1][start.x];
			down = (below == '|' || below == 'J' || below == 'L');
		}

		if (start.x < max_x)
		{
			const char beside = grid[start.y][start.x + 1];
			right = (beside == '-' || beside == 'J' || beside == '7');
		}

		char& c = grid[start.y][start.x];
		if (up && left) c = 'J';
		else if (left && down) c = '7';
		else if (down && right) c = 'F';
		else if (right && up) c = 'L';
	}

	Position position = start;
	std::vector<Position> path;
	Direction last_direction = Direction::Any;

	do
	{
		path.push_back(position);

		bool up = false, left = false, right = false, down = false;

		switch (grid[position.y][position.x])
		{
		case '|': up = true; down = true; break;
		case 'L': up = true; right = true; break;
		case '-': right = true; left = true; break;
		case 'F': right = true; down = true; break;
		case '7': down = true; left = true; break;
		case 'J': left = true; up = true; break;
		default: break;
		}

		if (up && last_direction != Direction::Down)
		{
			position.y--;
			last_direction = Direction::Up;
		}
		else if (right && last_direction != Direction::Left)
		{
			position.x++;
			last_direction = Direction::Right;
		}
		else if (down && last_direction != Direction::Up)
		{
			position.y++;
			last_direction = Direction::Down;
		}
		else if (left && last_direction != Direction::Right)
		{
			position.x--;
			last_direction = Direction::Left;
		}
	}
	while (position != start);

	std::cout << path.size() / 2;
}