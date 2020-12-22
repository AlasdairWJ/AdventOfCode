#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, const char* argv[])
{
	scanf_s("%*d\n");

	__int64 a = 0, x;
	
	int n = 0;
	char bus[32];
	while (scanf_s("%[^,],", bus, (unsigned)_countof(bus)) == 1)
	{
		if (strcmp(bus, "x") != 0)
		{
			int bus_id;
			sscanf_s(bus, "%d", &bus_id);

			if (n == 0)
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

	printf("%lld", a);

	return 0;
}