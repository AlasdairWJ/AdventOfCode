#include <iostream>
#include <string>
#include <vector>

int main(int _, const char*[])
{
	std::vector<std::string> rows;

	for (std::string line; std::getline(std::cin, line); )
		rows.push_back(line);

	const int row_size = static_cast<int>(rows[0].size());

	const int slopes[][2]{
		{ 1, 1 },
		{ 3, 1 },
		{ 5, 1 },
		{ 7, 1 },
		{ 1, 2 }
	};

	long long product = 1;
	for (const auto& [dx, dy] : slopes)
	{
		int count = 0;

		for (int x = 0, y = 0; y < rows.size(); x += dx, y += dy)
		{
			if (rows[y][x % row_size] == '#')
				count++;
		}

		product *= count;
	}

	std::cout << product;
}