#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, const char* argv[])
{
	int minutes;
	scanf_s("%d\n", &minutes);

	int best_wait_time = minutes;
	int best_product = 1;

	char bus[32];
	while (!feof(stdin) && scanf_s("%[^,],", bus, (unsigned)_countof(bus)) != 0)
	{
		if (strcmp(bus, "x") == 0)
			continue;

		int bus_minutes;
		sscanf_s(bus, "%d", &bus_minutes);

		const int wait_time = bus_minutes - minutes % bus_minutes;
		if (wait_time < best_wait_time)
		{
			best_wait_time = wait_time;
			best_product = wait_time * bus_minutes;
		}
	}

	printf("%d", best_product);

	return 0;
}