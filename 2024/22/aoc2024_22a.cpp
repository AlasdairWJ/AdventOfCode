#include <iostream>
#include <array>

typedef long long int64;

constexpr int64 Limit = (1ll << 24) - 1;

constexpr void mix(int64& value, const int64 with)
{
	value ^= with;
}
constexpr void prune(int64& value)
{
	value &= Limit;
}

constexpr void next(int64& value)
{
	mix(value, value << 6);
	prune(value);
	mix(value, value >> 5);
	prune(value);
	mix(value, value << 11);
	prune(value);
}

int main(int _, const char*[])
{
	int64 total = 0;

	for (int64 value; std::cin >> value; )
	{
		for (int n = 0; n < 2000; n++)
			next(value);

		total += value;
	}
		
	std::cout << total << '\n';
}