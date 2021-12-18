#include <iostream>
#include <string>
#include <vector>

int tree_count(const int dx, const int dy, const std::vector<std::string>& trees)
{
	int count = 0;

	for (int x = 0, y = 0; y < trees.size(); x += dx, y += dy)
	{
		const auto& row = trees[y];
		if (row[x % (int)row.size()] == '#')
			count++;
	}

	return count;
}

int main(int argc, const char* argv[])
{
	std::vector<std::string> trees;

	std::string line;
	while (std::getline(std::cin, line))
		trees.push_back(line);

	const int slopes[][2] = {{ 1, 1 },
							 { 3, 1 },
							 { 5, 1 },
							 { 7, 1 },
							 { 1, 2 }};

	__int64 product = 1;
	for (const auto& slope : slopes)
		product *= tree_count(slope[0], slope[1], trees);

	std::cout << product;

	return 0;
}