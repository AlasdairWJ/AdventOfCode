#include <iostream>
#include <string>
#include <map>

template <typename T> T& clrb(T& mask, const int bit) { return mask &= ~(T(1) << bit); }
template <typename T> T& setb(T& mask, const int bit) { return mask |= T(1) << bit; }

int main(int argc, const char* argv[])
{
	std::map<int, uint64_t> memory;

	std::string mask;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (strncmp(line.c_str(), "mask", 4) == 0)
		{
			mask = line.substr(7);
		}
		else if (strncmp(line.c_str(), "mem", 3) == 0)
		{
			int position;
			uint64_t value;
			sscanf_s(line.c_str(), "mem[%d] = %llu", &position, &value);

			for (int i = 0; i < mask.size(); i++)
			{
				switch (mask[mask.size() - i - 1])
				{
				case '0':
					clrb(value, i);
					break;

				case '1':
					setb(value, i);
					break;

				default:
					break;
				}
			}
			memory[position] = value;
		}
	}

	uint64_t sum = 0;

	for (const auto& [_, value] : memory)
		sum += value;
	
	std::cout << sum;

	return 0;
}