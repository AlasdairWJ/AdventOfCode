#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::string start_row;
	std::getline(std::cin, start_row);

	std::vector<bool> positions(start_row.size());
	positions[start_row.find('S')] = true;

	int split_count{};

	for (std::string line; std::getline(std::cin, line); )
	{
		for (std::size_t ix{}; (ix = line.find('^', ix)) != std::string::npos; ix++)
		{
			if (positions[ix])
			{
				positions[ix - 1] = true;
				positions[ix] = false;
				positions[ix + 1] = true;
				split_count++;
			}
		}
	}

	std::cout << split_count;
}
