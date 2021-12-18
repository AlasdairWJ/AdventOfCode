#include <iostream>
#include <string>
#include <vector>

int main(int argc, const char* argv[])
{
	std::vector<std::string> trees;

	std::string line;
	while (std::getline(std::cin, line))
		trees.push_back(line);

	int x = 0;
	int count = 0;

	for (const auto& row : trees)
	{
		if (row[x % (int)row.size()] == '#')
			count++;

		x += 3;
	}

	std::cout << count;

	return 0;
}