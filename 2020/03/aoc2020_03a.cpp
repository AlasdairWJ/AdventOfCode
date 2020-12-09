#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, const char* argv[])
{
	std::vector<std::string> trees;

	{
		std::string line;
		while (std::getline(std::cin, line))
			trees.push_back(line);
	}

	const int max_y = (int)trees.size();

	int x = 0;
	int y = 0;

	int count = 0;

	do
	{
		const std::string& line = trees[y];
		if (line[x % (int)line.size()] == '#')
			count++;

		x += 3;
		y += 1;
	}
	while (y < max_y);

	printf("%d", count);

	return 0;
}