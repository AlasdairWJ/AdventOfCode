#include <cstdio>
#include <cstdlib>
#include <cstring>

#define N 9
#define SIZE 9
#define MOVES 100
//#define SIZE 1'000'000
//#define MOVES 10'000'000

int cups[N];

int main(int argc, const char* argv[])
{
	for (int n=0, cup; n<N; n++)
		scanf_s("%1d", &cups[n]);

	for (int n=N; n<SIZE; n++)
		cups[n] = n;

	//for (int n=0; n<N; n++)
	//	printf("%d ", cups[n]);
	//printf("\n");

	for (int m=0; m<MOVES; m++)
	{
		const int front = cups[0];

		std::memmove(&cups[0], &cups[1], (N-1) * sizeof(int));
		cups[N-1] = front;

		int pickup[3];
		memcpy(pickup, cups, sizeof(pickup));

		int destination_cup_value = front;
		do
		{
			if (--destination_cup_value == 0)
				destination_cup_value = N;
		}
		while (pickup[0] == destination_cup_value ||
			   pickup[1] == destination_cup_value ||
			   pickup[2] == destination_cup_value);

		int n = 3;
		for (; n < N-1; n++)
		{
			if (cups[n] == destination_cup_value)
				break;
		}

		memcpy(cups, cups + 3, (n - 3 + 1) * sizeof(int));
		memcpy(cups + (n - 3 + 1), pickup, sizeof(pickup));

		//for (int n=0; n<N; n++)
		//	printf("%d ", cups[n]);
		//printf("\n");
	}

	int n0=0;
	while (cups[n0] != 1)
		n0++;

	for (int n=1; n<N; n++)
		printf("%d", cups[(n0 + n) % N]);

	return 0;
}	