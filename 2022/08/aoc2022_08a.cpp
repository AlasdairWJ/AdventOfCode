#include <iostream>
#include <string> // std::getline
#include <vector>
#include <algorithm> // std::ranges::count

int main(int _, const char*[])
{
	std::vector<std::string> heights;

	for (std::string line; std::getline(std::cin, line); )
		heights.push_back(line);

	// assume square
	const int size = static_cast<int>(heights.size());
	const int tree_count = size * size;

	std::vector<bool> visible(tree_count);

	auto check = [&](int x, int y, const int dx, const int dy)
	{
		char max = 0;
		for (int i = 0; i < size; i++, x += dx, y += dy)
		{
			if (const char height = heights[y][x]; height > max)
			{
				max = height;
				visible[y * size + x] = true;
			}
		}
	};

	for (int i = 0; i < size; i++)
	{
		check(i,		0,			0,	1);
		check(i,		size - 1,	0,	-1);
		check(0,		i,			1,	0);
		check(size - 1, i,			-1,	0);
	}

	std::cout << std::ranges::count(visible, true);
}