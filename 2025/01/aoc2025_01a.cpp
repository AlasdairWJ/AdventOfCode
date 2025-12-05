#include <iostream>
#include <string>
#include <string_view>

#include "../util/charconv.hpp"

int main()
{
	constexpr int D = 100;
	constexpr int S[]{ -1, 1 };

	int dial = 50;
	int count = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const char d = line[0];
		const auto x_str = std::string_view{ line }.substr(1);
		
		const int x = *util::parse<int>(x_str) * S[d == 'R'];

		dial %= x;

		if (x < 0)
			dial += x;

		if (dial == 0)
			count++;
	}

	std::cout << count;
}