#include <cstdio>

int main(int argc, const char* argv[])
{
	int total_fuel = 0;

	int mass;
	while (scanf_s("%d", &mass) == 1)
	{
		const int fuel = (mass / 3) - 2;
		total_fuel += fuel;
	}

	printf("%d", total_fuel);

	return 0;
}