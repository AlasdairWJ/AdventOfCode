#include <iostream>
#include <string>
#include <ranges> // std::views::split

int main(int _, const char*[])
{
	std::string line;
	std::getline(std::cin, line);

	const int minutes = std::stoi(line);

	__int64 a = 0, x = -1;

	std::getline(std::cin, line);

	for (int n{}; auto && r : line | std::views::split(','))
	{
		if (const std::string item{ r.begin(), r.end() }; item != "x")
		{
			const int bus_id = std::stoi(item);

			if (x < 0)
			{
				x = bus_id;
			}
			else
			{
				while ((a + n) % bus_id != 0)
					a += x;

				x *= bus_id;
			}
		}

		n++;
	}

	std::cout << a;
}