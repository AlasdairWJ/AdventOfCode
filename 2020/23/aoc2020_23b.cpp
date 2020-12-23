#include <cstdio>
#include <cstdlib>

// had to steal logic here because i suck

#define INPUT_SIZE 9
#define N 1'000'000
#define MOVES 10'000'000

int next_cup[N];

int main(int argc, const char* argv[])
{
	int first;
	scanf_s("%1d", &first);

	int current = first;
	for (int n=1, next; n<INPUT_SIZE; n++)
	{
		scanf_s("%1d", &next);
		current = (next_cup[current] = next);
	}

	for (int n=INPUT_SIZE; n<N; n++)
		current = (next_cup[current] = n+1);

	current = (next_cup[current] = first);

	for (int m=0; m<MOVES; m++)
	{
		int picked_up[3];
		picked_up[0] = next_cup[current];
		picked_up[1] = next_cup[picked_up[0]];
		picked_up[2] = next_cup[picked_up[1]];

		int destination = current;
		do
		{	
			if (--destination == 0)
				destination = N;
		}
		while (picked_up[0] == destination ||
			   picked_up[1] == destination ||
			   picked_up[2] == destination);

		const int next = next_cup[picked_up[2]];
		next_cup[picked_up[2]] = next_cup[destination];
		next_cup[destination] = picked_up[0];
		current = (next_cup[current] = next);
	}

	printf("%lld", (__int64)next_cup[1] * next_cup[next_cup[1]]);
	
	return 0;
}	