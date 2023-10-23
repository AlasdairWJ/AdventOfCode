#include <iostream>
#include <string>
#include <ranges> // std::views::split

int main(int _, const char*[])
{
	std::string line;
	std::getline(std::cin, line);

	const int minutes = std::stoi(line);

	int best_wait_time = minutes;
	int best_product = 1;

	std::getline(std::cin, line);

	for (auto && r : line | std::views::split(','))
	{
		if (const std::string item{ r.begin(), r.end() }; item != "x")
		{
			const int bus_id = std::stoi(item);

			const int wait_time = bus_id - minutes % bus_id;
			if (wait_time < best_wait_time)
			{
				best_wait_time = wait_time;
				best_product = wait_time * bus_id;
			}
		}
	}

	std::cout << best_product;
}