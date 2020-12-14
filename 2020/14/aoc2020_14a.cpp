#include <cstdio>
#include <cstdint>
#include <map>

void clear_bit(uint64_t& mask, const int bit)
{
	mask &= ~(1llu << bit);
}

void set_bit(uint64_t& mask, const int bit)
{
	mask |= 1llu << bit;
}

int main(int argc, const char* argv[])
{
	std::map<int, uint64_t> memory;

	char line[128];
	char mask[37];
	while (gets_s(line))
	{
		if (strncmp(line, "mask", 4) == 0)
		{
			sscanf_s(line, "mask = %s", mask, (unsigned)_countof(mask));
		}
		else
		{
			int position;
			uint64_t value;

			if (sscanf_s(line, "mem[%d] = %llu", &position, &value) != 2)
				continue;

			for (int i = 0; i < 36; i++)
			{
				if (mask[35 - i] == '0') clear_bit(value, i);
				if (mask[35 - i] == '1') set_bit(value, i);
			}

			memory[position] = value;
		}
	}

	uint64_t sum = 0;
	for (const auto& pos_value_pair : memory)
		sum += pos_value_pair.second;
	printf("%llu", sum);

	return 0;
}