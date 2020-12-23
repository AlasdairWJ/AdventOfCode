#include <cstdio>
#include <algorithm>

#define N 9
#define MOVES 100

int main(int argc, const char* argv[])
{
	int cups[N];

	for (int& cup : cups)
		scanf_s("%1d", &cup);

	for (int m=0; m<MOVES; m++)
	{
		int dst_cup = cups[0];

		int* destination;

		do {
			if (--dst_cup == 0) dst_cup = N;
			destination = std::find(std::begin(cups) + 4, std::end(cups), dst_cup);
		} while (destination == std::end(cups));

		std::rotate(std::begin(cups) + 1, std::begin(cups) + 4, destination + 1);
		std::rotate(std::begin(cups), std::begin(cups) + 1, std::end(cups));
	}

	int* it = std::find(std::begin(cups), std::end(cups), 1);
	for (int i = 1; i < N; i++)
	{
		if (++it == std::end(cups)) it = std::begin(cups);
		printf("%d", *it);
	}

	return 0;
}