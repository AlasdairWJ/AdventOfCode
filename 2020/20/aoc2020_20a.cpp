#include <cstdio>
#include <map>

#define N 10

void rotate(int &x, int &y)
{
	int temp = x;
	x = N - y - 1;
	y = temp;
}

struct tile_t
{
	int m_id;
	char m_data[N][N];

	const char &get(int x, int y, const int r = 0, const int s = 0) const
	{
		if (s == 1)
			x = N - x - 1;

		for (int i = 0; i < r; i++)
			rotate(x, y);

		return m_data[y][x];
	}
};

bool matches_side(const tile_t &a, const int ra, const int sa, const tile_t &b, const int rb, const int sb)
{
	for (int x = 0; x < N; x++)
		if (a.get(x, 0, ra, sa) != b.get(x, 0, rb, sb))
			return false;
	return true;
}

int main(int argc, const char *argv[])
{
 	//std::map<std::pair<int, int>, int> full_map;
	std::map<int, tile_t> all_tiles;

	int count = 0;
	while (!feof(stdin))
	{
		int id;
		if (scanf_s("Tile %d:\n", &id) != 1)
			break;

		tile_t tile;
		tile.m_id = id;

		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				tile.m_data[row][col] = getchar();
			}
			getchar(); // nl
		}
		getchar(); // nl

		all_tiles.emplace(id, tile);

		count++;
	}

	__int64 corner_product = 1;

	for (const auto& a : all_tiles)
	{
		int side_matches = 0;

		for (const auto &b : all_tiles)
		{
			if (a.first == b.first)
				continue;

			for (int ra = 0; ra < 4; ra++)
				for (int rb = 0; rb < 4; rb++)
					for (int sb = 0; sb < 2; sb++)
						if (matches_side(a.second, ra, 0, b.second, rb, sb))
							side_matches++;
		}

		if (side_matches == 2)
			corner_product *= a.first;
	}

	printf("%lld", corner_product);

	return 0;
}