#include <cstdio>
#include <utility>

#define COLUMNS 90
#define ROWS 91

using buffer_type = char[ROWS][COLUMNS + 1];

int neighbours(const buffer_type& board, const int target_row, const int target_column)
{
	const int row_min = target_row > 0 ? target_row - 1 : target_row;
	const int row_max = target_row < ROWS-1 ? target_row + 1 : target_row;
	const int column_min = target_column > 0 ? target_column - 1 : target_column;
	const int column_max = target_column < COLUMNS-1 ? target_column + 1 : target_column;

	int n = 0;
	for (int row = row_min; row <= row_max; row++)
		for (int column = column_min; column <= column_max; column++)
			if (row != target_row || column != target_column)
				if (board[row][column] == '#')
					n++;

	return n;
}

bool update(const buffer_type& current, buffer_type& next)
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
			else if (seat == '#' && n >= 4)
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

buffer_type buf1, buf2;

int main(int argc, const char* argv[])
{
	board_type *current = &buf1, *next = &buf2;

	int input_row = 0;
	while (input_row < ROWS && scanf_s("%s\n", (*current)[input_row], COLUMNS + 1) == 1)
		input_row++;

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