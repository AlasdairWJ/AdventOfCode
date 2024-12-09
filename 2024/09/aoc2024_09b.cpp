#include <iostream>
#include <string>
#include <vector>
#include <ranges>

struct Block
{
	int id;
	int count;

	bool has_room_for(const int amount) const
	{
		return id < 0 && count >= amount;
	}
};

int main(int argc, char const *argv[])
{
	std::string line;
	std::getline(std::cin, line);
	
	std::vector<Block> blocks;

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

	for (; id > 0; --id)
	{
		auto last = std::ranges::find_if(blocks, [&id](auto& block) { return block.id == id; });

		if (last == blocks.end())
			continue;

		const int amount = last->count;

		auto it = std::find_if(blocks.begin(), last, [&amount](auto& block) { return block.has_room_for(amount); });

		if (it != last)
		{
			if (it->count == last->count)
			{
				it->id = last->id;

				last->id = -1;
			}
			else
			{
				const int leftOver = it->count - last->count;
				*it = *last;
				last->id = -1;
				blocks.insert(it + 1, Block{ -1, leftOver });
			}
		}
	}

	long long checksum = 0;
	int position = 0;

	for (const auto [id, count] : blocks)
	{
		if (id >= 0)
		{
			for (int n = 0; n < count; n++)
				checksum += (position + n) * id;
		}

		position += count;
	}

	std::cout << checksum;
}
