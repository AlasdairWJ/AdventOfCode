#include <iostream>
#include <string>
#include <map>

//   nw ne
//    |/
// w--O--e
//   /|
// sw se

bool read_direction(const std::string& line, int& position, int& dx, int& dy)
{
	switch (line[position++])
	{
	case 'e': dx =  1, dy = 0; break;
	case 'w': dx = -1, dy = 0; break;
	case 'n':
		dy = -1;
		switch (line[position++])
		{
		case 'e': dx = 1; break;
		case 'w': dx = 0; break;
		default: return false;
		}
		break;
	case 's':
		dy = 1;
		switch (line[position++])
		{
		case 'e': dx = 0; break;
		case 'w': dx = -1; break;
		default: return false;
		}
		break;
	default: return false;
	}
	return true;
}

int main(int argc, const  char* argv[])
{
	std::map<std::pair<int, int>, bool> floor_tiles;

	int min_x = 0, max_x = 0;
	int min_y = 0, max_y = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		int x = 0, y = 0;

		int position = 0;
		int dx, dy;
		while (position < (int)line.size() && read_direction(line, position, dx, dy))
			x += dx, y += dy;

		floor_tiles[{x,y}] ^= 1;

		if (x < min_x) min_x = x;
		if (y < min_y) min_y = y;
		if (x > max_x) max_x = x;
		if (y > max_y) max_y = y;
	}

	printf("x: %d-%d\n", min_x, max_x);
	printf("y: %d-%d\n", min_y, max_y);

	int count = 0;
	for (const auto& pair : floor_tiles)
		if (pair.second)
			count++;

	printf("%d", count);

	return 0;
}