#include <iostream>
#include <string>
#include <string_view>

#include "../util/charconv.hpp"

int main()
{
	constexpr int D = 100;

	int dial = 50;
	int count = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const char d = line[0];
		const auto x_str = std::string_view{ line }.substr(1);

		const int x = *util::parse<int>(x_str);

		if (d == 'R')
		{
			dial += x;
			count += dial / D;
			dial %= D;
		}
		else
		{
			if (dial == 0)
				dial = D;

			dial -= x;

			if (dial <= 0)
			{
				count += (-dial / D) + 1;
				dial %= D;

				if (dial < 0)
					dial += D;
			}
		}
	}

	std::cout << count;
}