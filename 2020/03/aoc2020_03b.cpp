#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int tree_count(const int dx, const int dy, const std::vector<std::string>& trees)
{
	const int max_y = (int)trees.size();

	int x = 0;
	int y = 0;

	int count = 0;

	do
	{
		const std::string& line = trees[y];
		if (line[x % (int)line.size()] == '#')
			count++;

		x += dx;
		y += dy;
	}
	while (y < max_y);

	return count;
}

int main(int argc, const char* argv[])
{
	std::vector<std::string> trees;

	std::string line;
	while (std::getline(std::cin, line))
		trees.push_back(line);

	const int slopes[][2] = {
		{ 1, 1 },
		{ 3, 1 },
		{ 5, 1 },
		{ 7, 1 },
		{ 1, 2 },
	};

	__int64 product = 1;
	for (const auto& slope : slopes)
		product *= tree_count(slope[0], slope[1], trees);

	printf("%lld", product);
	return 0;
}