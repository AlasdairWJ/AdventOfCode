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

	std::string line;
	while (std::getline(std::cin, line))
	{
		int x = 0, y = 0;

		int position = 0;
		int dx, dy;
		while (position < (int)line.size() && read_direction(line, position, dx, dy))
			x += dx, y += dy;

		floor_tiles[{x,y}] ^= 1;
	}

	for (int day = 0; day < 100; day++)
	{

		std::map<std::pair<int, int>,int> neighbour_counts;

		for (const auto& pair : floor_tiles)
		{
			if (!pair.second)
				continue;

			const auto& pos = pair.first;

			neighbour_counts[pos]; // lol
			neighbour_counts[{pos.first+1, pos.second  }]++; // e
			neighbour_counts[{pos.first-1, pos.second  }]++; // w
			neighbour_counts[{pos.first+1, pos.second-1}]++; // ne
			neighbour_counts[{pos.first  , pos.second-1}]++; // nw
			neighbour_counts[{pos.first  , pos.second+1}]++; // se
			neighbour_counts[{pos.first-1, pos.second+1}]++; // sw
		}

		for (const auto& pair : neighbour_counts)
		{
			bool& tile = floor_tiles[pair.first];
			
			if (tile)
			{
				if (pair.second == 0 || pair.second > 2)
					tile = false;
			}
			else
			{
				if (pair.second == 2)
					tile = true;
			}
		}
	}

	int count = 0;
	for (const auto& pair : floor_tiles)
		if (pair.second)
			count++;

	printf("%d", count);

	return 0;
}