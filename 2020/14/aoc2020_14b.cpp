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

	char mask[D + 1];
	int limit;

	char line[128];
	while (gets_s(line))
	{
		if (strncmp(line, "mask", 4) == 0)
		{
			sscanf_s(line, "mask = %s", mask, (unsigned)_countof(mask));

			int count = 0;
			for (char c : mask)
				if (c == 'X')
					count++;
			limit = 1 << count;
			continue;
		}

		uint64_t position, value;

		sscanf_s(line, "mem[%llu] = %llu", &position, &value);

		for (unsigned x = 0; x < limit; x++)
		{
			unsigned bit = 1;
			for (int i = 0; i < D; i++)
			{
				switch (mask[D - i - 1])
				{
				case 'X':
					if ((x & bit) == bit)
						set_bit(position, i);
					else
						clear_bit(position, i);

					bit <<= 1;
					break;

				case '1':
					set_bit(position, i);
					break;

				default:
					break;
				}
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