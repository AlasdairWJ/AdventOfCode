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
		int space_required = counts[id];

		auto it = blocks.begin();

		for (; it->id != id; ++it)
		{
			if (space_required > 0 && it->id < 0)
			{
				if (it->count <= space_required)
				{
					it->id = id;
					space_required -= it->count;
				}
				else
				{
					it->id = -1;
					it->count -= space_required;
					it = blocks.insert(it, Block{ id, space_required }); // insert new block before this one
					space_required = 0;
				}
			}
		}

		if (space_required == 0)
			it->id = -1; // it's all been moved, so clear the original block
		
		it->count = space_required;
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
