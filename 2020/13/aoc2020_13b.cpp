#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	int minutes;
	std::cin >> minutes;

	__int64 a = 0, x = -1;
	
	int n = 0;
	
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
	while (std::cin.get() == ',');

	std::cout << a;

	return 0;
}