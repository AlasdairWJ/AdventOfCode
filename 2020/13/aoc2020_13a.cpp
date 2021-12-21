#include <iostream>

int main(int argc, const char* argv[])
{
	int minutes;
	std::cin >> minutes;

	int best_wait_time = minutes;
	int best_product = 1;

	do
	{
		if (std::cin.peek() == 'x')
		{
			std::cin.ignore(1);
		}
		else
		{
			int bus_id;
			std::cin >> bus_id;

			const int wait_time = bus_id - minutes % bus_id;
			if (wait_time < best_wait_time)
			{
				best_wait_time = wait_time;
				best_product = wait_time * bus_id;
			}
		}

	}
	while (std::cin.get() == ',');

	std::cout << best_product;

	return 0;
}