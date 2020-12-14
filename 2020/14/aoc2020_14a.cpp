#include <cstdio>
#include <cstdint>
#include <map>

#define D 36

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
	std::map<uint64_t, uint64_t> memory;

	char line[128];
	char mask[D + 1];
	while (gets_s(line))
	{
		if (strncmp(line, "mask", 4) == 0)
		{
			sscanf_s(line, "mask = %s", mask, (unsigned)_countof(mask));
			continue;
		}

		uint64_t position, value;
		sscanf_s(line, "mem[%llu] = %llu", &position, &value);

		for (int i = 0; i < D; i++)
		{
			switch (mask[D - i - 1])
			{
			case '0':
				clear_bit(value, i);
				break;

			case '1':
				set_bit(value, i);
				break;

			default:
				break;
			}
		}

		memory[position] = value;

	}

	uint64_t sum = 0;

	for (const auto& pos_value_pair : memory)
		sum += pos_value_pair.second;
	
	printf("%llu", sum);

	return 0;
}