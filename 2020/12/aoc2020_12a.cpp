#include <iostream>

void rotate_ccw(int& dx, int& dy) { std::swap(dx = -dx, dy); }
void rotate_cw(int& dx, int& dy) { std::swap(dx, dy = -dy); }

int main(int _, const char*[])
{
	int x = 0, y = 0;
	int dx = 1, dy = 0;

	char direction;
	int value;
	while (std::cin >> direction, std::cin >> value)
	{
		switch (direction)
		{
		case 'F':
			x += dx * value;
			y += dy * value;
			break;
		case 'N':
			y -= value;
			break;
		case 'E':
			x += value;
			break;
		case 'S':
			y += value;
			break;
		case 'W':
			x -= value;
			break;
		case 'L':
			while (value > 0)
			{
				rotate_ccw(dx, dy);
				value -= 90;
			}
			break;
		case 'R':
			while (value > 0)
			{
				rotate_cw(dx, dy);
				value -= 90;
			}
			break;
		default:
			break;
		}
	}

	std::cout << std::abs(x) + std::abs(y);
}