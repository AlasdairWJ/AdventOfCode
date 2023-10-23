#include <iostream>

void rotate_ccw(int& dx, int& dy) { std::swap(dx = -dx, dy); }
void rotate_cw(int& dx, int& dy) { std::swap(dx, dy = -dy); }

int main(int _, const char*[])
{
	int x = 0, y = 0;
	int waypoint_x = 10, waypoint_y = -1;

	char direction;
	int value;
	while (std::cin >> direction, std::cin >> value)
	{
		switch (direction)
		{
		case 'F':
			x += waypoint_x * value;
			y += waypoint_y * value;
			break;
		case 'N':
			waypoint_y -= value;
			break;
		case 'E':
			waypoint_x += value;
			break;
		case 'S':
			waypoint_y += value;
			break;
		case 'W':
			waypoint_x -= value;
			break;
		case 'L':
			while (value > 0)
			{
				rotate_ccw(waypoint_x, waypoint_y);
				value -= 90;
			}
			break;
		case 'R':
			while (value > 0)
			{
				rotate_cw(waypoint_x, waypoint_y);
				value -= 90;
			}
			break;
		default:
			break;
		}
	}

	std::cout << std::abs(x) + std::abs(y);
}