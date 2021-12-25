#include <iostream>
#include <string>
#include <map>
#include <algorithm> // std::count_if

//   nw ne
//    |/
// w--O--e
//   /|
// sw se

int main(int argc, const char* argv[])
{
	std::map<std::pair<int, int>, bool> floor_tiles;

	std::string line;
	while (std::getline(std::cin, line))
	{
		int x = 0, y = 0;

		auto it = line.begin();
		while (it != line.end())
		{
			switch(*(it++))
			{
			case 'e': x++; break;
			case 'w': x--; break;
			case 'n': y--;
				switch (*(it++))
				{
				case 'e': x++; break;
				case 'w': 
				default: break;
				}
				break;
			case 's': y++;
				switch (*(it++))
				{
				case 'w': x--; break;
				case 'e':
				default: break;
				}
				break;
			default:
				break;
			}
		}

		floor_tiles[{x,y}] ^= 1;
	}

	std::cout << std::count_if(floor_tiles.begin(), floor_tiles.end(),
							   [](const auto pair) { return pair.second; });

	return 0;
}