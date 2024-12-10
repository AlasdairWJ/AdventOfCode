#include <iostream>
#include <string>
#include <vector>
#include <ranges>

struct Block
{
	int id;
	int count;
};

int tri(const int n)
{
	return n * (n + 1) / 2;
}

int main(int argc, char const *argv[])
{
	std::string line;
	std::getline(std::cin, line);
	
	std::vector<Block> blocks;
	std::vector<int> counts;

	int id = 0;
	bool gap = false;

	for (const char c : line)
	{
		const int count = int{ c - '0' };

		if (gap)
		{
			blocks.push_back(Block{ -1, count });
		}
		else
		{
			blocks.push_back(Block{ id, count });
			counts.push_back(count);
			id++;
		}

		gap ^= true;
	}

	for (--id; id > 0; --id)
	{
		const int space_required = counts[id];

		bool moved = false;

		auto it = blocks.begin();

		for (; it->id != id; ++it)
		{
			if (!moved && it->id < 0 && it->count >= space_required)
			{
				if (it->count == space_required)
				{
					it->id = id;
				}
				else
				{
					it->count -= space_required; // reduce available space of free block
					it = blocks.insert(it, Block{ id, space_required }); // insert new block before this one
				}

				moved = true;
			}
		}

		if (moved)
			it->id = -1; // clear the original block
	}

	long long checksum = 0;
	long long position = 0;

	for (const auto [id, count] : blocks)
	{
		if (id >= 0)
			checksum += (count * position + tri(count - 1)) * id;

		position += count;
	}

	std::cout << checksum;
}
