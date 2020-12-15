#include <cstdio>

#define COLUMNS 25
#define ROWS 6

enum pixel_t { BLACK = 0, WHITE = 1, TRANSPARENT = 2 };
using image_t = pixel_t[ROWS][COLUMNS];

bool read_image(image_t& image)
{
	for (int row = 0; row < ROWS; row++)
		for (int col = 0; col < COLUMNS; col++)
		{
			const int digit = getchar();
			if (digit == EOF)
				return false;

			image[row][col] = static_cast<pixel_t>(digit - '0');
		}

	return true;
}


int main(int argc, const char* argv[])
{
	image_t image, layer;

	for (auto& row : image)
		for (auto& x : row)
			x = TRANSPARENT;

	while (!feof(stdin))
	{
		if (!read_image(layer))
			break;

		for (int row = 0; row < ROWS; row++)
			for (int col = 0; col < COLUMNS; col++)
				if (image[row][col] == TRANSPARENT)
					image[row][col] = layer[row][col];
	}

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLUMNS; col++)
			putchar(image[row][col] == WHITE ? '#' : ' ');
		putchar('\n');
	}

	return 0;
}