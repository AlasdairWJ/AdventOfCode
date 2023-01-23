#include <iostream> // std::cout
#include <string> // std::string, std::getline, std::stoi

int main(int argc, const char* argv[])
{
	int current = 0, best_so_far = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
		{
			if (best_so_far == 0 || current > best_so_far)
			{
				best_so_far = current;
			}

			current = 0;
		}
		else
		{
			current += std::stoi(line);
		}
	}

	std::cout << best_so_far;

	return 0;
}