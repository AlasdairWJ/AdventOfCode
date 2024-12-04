#include <iostream>
#include <string>
#include <vector>

constexpr int Size = 3;

bool is_match(const auto& lines, const int x, const int y)
{
	return
		(lines[y + 1][x + 1] == 'A')
		&&
		(
			(lines[y][x] == 'M' && lines[y + 2][x + 2] == 'S')
			||
			(lines[y][x] == 'S' && lines[y + 2][x + 2] == 'M')
		)
		&&
		(
			(lines[y][x + 2] == 'M' && lines[y + 2][x] == 'S')
			||
			(lines[y][x + 2] == 'S' && lines[y + 2][x] == 'M')
		);
}

int main(int _, const char*[])
{
	std::vector<std::string> lines;

	for (std::string line; std::getline(std::cin, line); )
		lines.push_back(line);

	const int width = static_cast<int>(lines.front().size());
	const int height = static_cast<int>(lines.size());
	
	int count = 0;

	for (int x = 0; x <= width - Size; x++)
	{
		for (int y = 0; y <= height - Size; y++)
		{
			if (is_match(lines, x, y))
				count++;
		}
	}

	std::cout << count;
}