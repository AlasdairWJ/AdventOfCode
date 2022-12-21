#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	int current = 0, best_so_far = 0;

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		if (buffer.empty())
		{
			if (best_so_far == 0 || current > best_so_far)
			{
				best_so_far = current;
			}

			current = 0;
		}
		else
		{
			current += std::stoi(buffer);
		}
	}

	std::cout << best_so_far;

	return 0;
}