#include <cstdio>

int transform(const int subject, int loop_size)
{
	__int64 result = 1;
	while (loop_size--)
		(result *= subject) %= 20201227;
	return (int)result;
}

int main(int argc, const char* argv[])
{
	int keys[2];
	int loop_sizes[2];

	scanf("%d\n%d", &keys[0], &keys[1]);

	unsigned mask = 0;

	int l = 1;
	__int64 value = 1;
	while (mask != 3u)
	{
		(value *= 7) %= 20201227;

		if (value == keys[0])
		{
			printf("key 1 has loop size %d\n", l);
			loop_sizes[0] = l;
			mask |= 1u;
		}

		if (value == keys[1])
		{
			printf("key 2 has loop size %d\n", l);
			loop_sizes[1] = l;
			mask |= 2u;
		}

		l++;
	}

	printf("%d\n%d", transform(keys[0], loop_sizes[1]), transform(keys[1], loop_sizes[0]));

	return 0;
}