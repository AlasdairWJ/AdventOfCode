#include <cstdio>
#include <utility>

constexpr int POW(int base, int exponent)
{
	return exponent == 0 ? 1 : base * POW(base, exponent - 1);
}

const int N = 20; // board size + 2*number of iterations
const int D = 3;
const int ND = POW(N, D);

const int I = 8;
const int MAX_ITERATIONS = 6;

using board_type = char[ND];

char& get(board_type& board, int (&pos)[D])
{
	int x = 0;
	for (int d = 0, p = 1; d < D; d++, p *= N)
		x += p * pos[d];
	return board[x];
} 

void update(board_type& current, board_type& next)
{
	int pos[D], npos[D];
	for (int i = 0; i < ND; i++)
	{
		const char& current_cell = current[i];
		char& next_cell = next[i];

		for (int d = 0, x = i; d < D; d++, x /= N)
			pos[d] = x % N;

		int neighbour_count = 0;

		for (int j = 0; j < POW(3, D); j++)
		{
			if (j == (POW(3, D) - 1) / 2)
				continue; // middle

			bool on_board = true;
			for (int d = 0, x = j; d < D; d++, x /= 3)
			{
				int& p = (npos[d] = pos[d] + (x % 3) - 1);
				if (p < 0 || p >= N)
				{
					on_board = false;
					break;
				}
			}

			if (!on_board)
				continue;

			if (get(current, npos) == '#')
				neighbour_count++;
		}

		if (current_cell == '#')
		{
			next_cell = neighbour_count == 2 || neighbour_count == 3 ? '#' : ' ';
		}
		else
		{
			next_cell = neighbour_count == 3 ? '#' : ' ';
		}
	}
}

board_type buf1 = {}, buf2;

int main(int argc, const char* argv[])
{
	board_type *current = &buf1, *next = &buf2;

	int pos[D] = { 0, 0, N/2 };
	for (int i = 0; i < I; i++)
	{
		pos[1] = N/2 - I/2 + i;
		for (int j = 0; j < I; j++)
		{
			pos[0] = N/2 - I/2 + j;
			get(*current, pos) = getchar();
		}
		getchar(); // nl
	}

	for (int it = 0; it < MAX_ITERATIONS; it++)
	{
		update(*current, *next);
		std::swap(current, next);
	}

	int count = 0;

	for (int i = 0; i < ND; i++)
		if ((*current)[i] == '#')
			count++;

	printf("%d", count);

	return 0;
}