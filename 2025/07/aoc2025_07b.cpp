#include <iostream>
#include <string>
#include <vector>
#include <numeric>

typedef long long i64;

int main()
{
	std::string start_row;
	std::getline(std::cin, start_row);

	std::vector<i64> positions(start_row.size());
	positions[start_row.find('S')] = 1;

	for (std::string line; std::getline(std::cin, line); )
	{
		for (std::size_t ix{}; (ix = line.find('^', ix)) != std::string::npos; ix++)
		{
			if (i64& count = positions[ix]; count != 0)
			{
				positions[ix - 1] += count;
				positions[ix + 1] += count;
				count = 0;
			}
		}
	}

	std::cout << std::accumulate(positions.begin(), positions.end(), i64{});
}
