#include <cstdio>
#include <utility>

#define COLUMNS 90
#define ROWS 91

using board_type = char[ROWS][COLUMNS + 1];

int is_in_range(const int x, const int limit)
{
	return x >= 0 && x < limit;
}

int neighbours(const board_type& board, const int target_row, const int target_column)
{
	static const int delta[8][2] = {
		{ -1,  0 },
		{ -1,  1 },
		{  0,  1 },
		{  1,  1 },
		{  1,  0 },
		{  1, -1 },
		{  0, -1 },
		{ -1, -1 },
	};

	int n = 0;
	for (int d = 0; d < 8; d++)
	{
		int row = target_row + delta[d][0];
		int column = target_column + delta[d][1];

		while (is_in_range(row, ROWS) && is_in_range(column, COLUMNS))
		{
			const char& seat = board[row][column];
			if (seat != '.')
			{
				if (seat == '#')
					n++;

				break;
			}

			row += delta[d][0];
			column += delta[d][1];
		}
	}

	return n;
}

bool update(const board_type& current, board_type& next)
{
	bool updates = false;
	for (int row = 0; row < ROWS; row++)
		for (int column = 0; column < COLUMNS; column++)
		{
			const char seat = current[row][column];
			const int n = neighbours(current, row, column);

			if (seat == 'L' && n == 0)
			{
				next[row][column] = '#';
				updates = true;
			}
			else if (seat == '#' && n >= 5)
			{
				next[row][column] = 'L';
				updates = true;
			}
			else
			{
				next[row][column] = seat;
			}
		}

	return updates;
}

board_type buf1, buf2;

int main(int argc, const char* argv[])
{
	board_type *current = &buf1, *next = &buf2;

	{
		int row = 0;
		while (row < ROWS && scanf_s("%s\n", (*current)[row], COLUMNS + 1) == 1)
			row++;
	}

	while (update(*current, *next))
		std::swap(current, next);

	int seated_count = 0;
	for (int row = 0; row < ROWS; row++)
		for (int column = 0; column < COLUMNS; column++)
			if ((*next)[row][column] == '#')
				seated_count++;

	printf("%d", seated_count);

	return 0;
}