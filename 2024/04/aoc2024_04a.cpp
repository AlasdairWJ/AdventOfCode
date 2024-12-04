#include <iostream>
#include <string>
#include <vector>

constexpr char XMAS[]{ 'X', 'M', 'A', 'S' };
constexpr int Size = std::size(XMAS);

constexpr int directions[][2]{
	{  1,  0 },
	{  1, -1 },
	{  0, -1 },
	{ -1, -1 },
	{ -1,  0 },
	{ -1,  1 },
	{  0,  1 },
	{  1,  1 }
};

bool is_match(const auto& lines int x, int y, const int dx, const int dy)
{
	for (int n = 0; n < Size; n++, x += dx, y += dy)
	{
		if (lines[y][x] != XMAS[n])
			return false;
	}

	return true;
}

int main(int _, const char*[])
{
	std::vector<std::string> lines;

	for (std::string line; std::getline(std::cin, line); )
		lines.push_back(line);

	const int width = static_cast<int>(lines.front().size());
	const int height = static_cast<int>(lines.size());
	
	int count = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			for (const auto [dx, dy] : directions)
			{
				if (dx < 0 && x < Size - 1)
					continue;

				if (dx > 0 && x > width - Size)
					continue;

				if (dy < 0 && y < Size - 1)
					continue;

				if (dy > 0 && y > height - Size)
					continue;

				if (is_match(line, x, y, dx, dy))
					count++;
			}
		}
	}

	std::cout << count;
}