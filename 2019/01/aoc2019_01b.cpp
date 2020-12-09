#include <cstdio>

int main(int argc, const char* argv[])
{
	int total_fuel = 0;

	int mass;
	while (scanf_s("%d", &mass) == 1)
	{
		int fuel =  (mass / 3) - 2;

		do
		{
			total_fuel += fuel;
			fuel = (fuel / 3) - 2;
		}
		while  (fuel > 0);
	}

	printf("%d", total_fuel);

	return 0;
}