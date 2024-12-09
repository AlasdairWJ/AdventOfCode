#include <iostream>
#include <string>
#include <vector>
#include <ranges>

int main(int argc, char const *argv[])
{
	std::string line;
	std::getline(std::cin, line);
	
	std::vector<int> blocks;

	int id = 0;
	bool gap = false;
	for (const char c : line)
	{
		const int count = int{ c - '0' };

		blocks.push_back(Block{
			gap ? -1 : id,
			count
		});

		if (gap)
			id++;

		gap ^= true;
	}

	int index = 0;
	int last = blocks.size() - 1;

	while (blocks[index] >= 0)
		index++;

	while (index < last)
	{
		blocks[index] = blocks[last];
		blocks[last] = -1;

		while (blocks[index] >= 0)
			index++;

		do last--;
		while (blocks[last] < 0);
	}

	long long checksum = 0;

	for (const auto [index, value] : blocks | std::views::enumerate)
	{
		if (value > 0)
			checksum += value * index;
	}

	std::cout << checksum;
}