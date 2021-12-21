#include <iostream>
#include <string>
#include <map>
#include <algorithm> // std::count

template <typename T> T& clrb(T& mask, const int bit) { return mask &= ~(T(1) << bit); }
template <typename T> T& setb(T& mask, const int bit) { return mask |= T(1) << bit; }

int main(int argc, const char* argv[])
{
	std::map<uint64_t, uint64_t> memory;

	unsigned limit;
	std::string mask;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (strncmp(line.c_str(), "mask", 4) == 0)
		{
			mask = line.substr(7);
			limit = 1u << std::count(mask.begin(), mask.end(), 'X');
		}
		else if (strncmp(line.c_str(), "mem", 3) == 0)
		{
			uint64_t position, value;
			sscanf_s(line.c_str(), "mem[%llu] = %llu", &position, &value);

			for (unsigned x = 0; x < limit; x++)
			{
				unsigned bit = 1;
				for (int i = 0; i < mask.size(); i++)
				{
					switch (mask[mask.size() - i - 1])
					{
					case 'X':
						if ((x & bit) == bit)
							setb(position, i);
						else
							clrb(position, i);

						bit <<= 1;
						break;

					case '1':
						setb(position, i);
						break;

					default:
						break;
					}
				}
				memory[position] = value;
			}
		}
	}

	uint64_t sum = 0;

	for (const auto& [_, value] : memory)
		sum += value;
	
	std::cout << sum;

	return 0;
}