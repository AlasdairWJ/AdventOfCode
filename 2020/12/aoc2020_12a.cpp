#include <cstdio>

void rotate_left(int& dx, int& dy)
{
	int temp = dy;
	dy = -dx;
	dx = temp;
}

void rotate_right(int& dx, int& dy)
{
	int temp = dy;
	dy = dx;
	dx = -temp;
}

int abs(const int x)
{
	return x < 0 ? -x : x;
}

int main(int argc, const char* argv[])
{
	int x = 0, y = 0;
	int dx = 1, dy = 0;

	int value;
	char direction;
	while (scanf_s("%c%d\n", &direction, 1, &value) == 2)
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
				rotate_left(dx, dy);
				value -= 90;
			}
			break;
		case 'R':
			while (value > 0)
			{
				rotate_right(dx, dy);
				value -= 90;
			}
			break;
		default:
			puts("invalid direction");
			break;
		}
	}

	printf("%d", abs(x) + abs(y));

	return 0;
}