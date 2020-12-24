#include <cstdio>
#include <map>
#include <set>
#include "d4.hpp"
#include "coord.hpp"

// this was hell

#define N 10

#define TILE_SIZE 10
#define TILES_COUNT 12
#define IMAGE_SIZE (TILES_COUNT*(TILE_SIZE-2))

#define MONSTER_WIDTH 20
#define MONSTER_HEIGHT 3

// -----------------------------------------------------------------------------

template <int SIZE>
void rotate(int &x, int &y)
{
	int temp = y;
	y = SIZE - x - 1;
	x = temp;
}

template <int SIZE>
struct image_t
{
	char m_data[SIZE][SIZE];
	d4_t m_orientation;

	const char &get(int x, int y, const d4_t& d4 = d4_t::zero) const
	{
		const d4_t orientation = m_orientation * d4;

		for (int i = 0; i < orientation.r; i++)
			rotate<SIZE>(x, y);

		if (orientation.s == 1)
			x = SIZE - x - 1;

		return m_data[y][x];
	}

	char &get(int x, int y, const d4_t& d4 = d4_t::zero)
	{
		const d4_t orientation = m_orientation * d4;

		for (int i = 0; i < orientation.r; i++)
			rotate<SIZE>(x, y);

		if (orientation.s == 1)
			x = SIZE - x - 1;

		return m_data[y][x];
	}

	void print(const d4_t& d4 = d4_t::zero) const
	{
		for (int row = 0; row < SIZE; row++)
		{
			for (int col = 0; col < SIZE; col++)
			{
				putchar(get(col, row, d4));
			}
			putchar('\n');
		}
		putchar('\n');
	}
};


struct tile_t : image_t<TILE_SIZE>
{
	int m_id;
};

// -----------------------------------------------------------------------------

bool matches_side(const tile_t &a, const d4_t& a_orientation, const tile_t &b, const d4_t& b_orientation)
{
	for (int x = 0; x < N; x++)
		if (a.get(x, 0, a_orientation) != b.get(x, 0, b_orientation))
			return false;
	return true;
}


// -----------------------------------------------------------------------------

std::map<int, tile_t> all_tiles;
std::set<int> remaining_tile_ids;
std::map<coord_t, tile_t> spacial_map;

bool find_next_tile_location(int& id, coord_t& position)
{
	for (const auto& spacial_map_pair : spacial_map)
	{
		const auto& coord = spacial_map_pair.first;
		const auto& tile = spacial_map_pair.second;

		for (const int other_tile_id : remaining_tile_ids)
		{
			tile_t& other_tile = all_tiles[other_tile_id];

			for (const auto& orientation : d4_t::all_orientations)
			{
				if (matches_side(tile, d4_t(0), other_tile, orientation))
				{
					// printf("Tile #%d goes above #%d\n", other_tile.m_id, tile.m_id);
					other_tile.m_orientation = orientation * d4_t(2, 1);
					id = other_tile_id;
					position = coord + coord_t(0,-1);
					return true;
				}
				if (matches_side(tile, d4_t(1), other_tile, orientation))
				{
					// printf("Tile #%d goes to the left of #%d\n", other_tile.m_id, tile.m_id);
					other_tile.m_orientation = orientation * d4_t(1, 1);
					id = other_tile_id;
					position = coord + coord_t(-1,0);
					return true;
				}
				if (matches_side(tile, d4_t(2), other_tile, orientation))
				{
					// printf("Tile #%d goes below #%d\n", other_tile.m_id, tile.m_id);
					other_tile.m_orientation = orientation * d4_t(0, 1);
					id = other_tile_id;
					position = coord + coord_t(0,1);
					return true;
				}
				if (matches_side(tile, d4_t(3), other_tile, orientation))
				{
					// printf("Tile #%d goes to the right of #%d\n", other_tile.m_id, tile.m_id);
					other_tile.m_orientation = orientation * d4_t(3, 1);
					id = other_tile_id;
					position = coord + coord_t(1,0);
					return true;
				}
			}
		}
	}

	return false;
}

template <int SIZE>
bool mark_sea_monster(image_t<SIZE>& image, const int x0, const int y0)
{
	static const char sea_monster[3][21] = {
		"                  O ",
		"O    OO    OO    OOO",
		" O  O  O  O  O  O   "
	};

	for (int x=0; x<MONSTER_WIDTH; x++)
		for (int y=0; y<MONSTER_HEIGHT; y++)
			if (sea_monster[y][x] != ' ' && image.get(x0+x, y0+y) == '.')
				return false;

	for (int x=0; x<MONSTER_WIDTH; x++)
		for (int y=0; y<MONSTER_HEIGHT; y++)
			if (sea_monster[y][x] != ' ')
				image.get(x0+x, y0+y) = 'O';

	return true;
}

int main(int argc, const char *argv[])
{
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
		remaining_tile_ids.insert(id);
	}

	const int origin_tile_id = *remaining_tile_ids.begin();
	remaining_tile_ids.erase(origin_tile_id);

	spacial_map[{0,0}] = all_tiles[origin_tile_id];

	while (!remaining_tile_ids.empty())
	{
		int placed_tile_id;
		coord_t tile_position;
		if (!find_next_tile_location(placed_tile_id, tile_position))
		{
			puts(":(");
			return 1;
		}

		spacial_map[tile_position] = all_tiles[placed_tile_id];
		remaining_tile_ids.erase(placed_tile_id);
	}

	int min_x = spacial_map.begin()->first.x;
	int min_y = spacial_map.begin()->first.y;
	for (const auto& spacial_map_pair : spacial_map)
	{
		if (spacial_map_pair.first.x < min_x) min_x = spacial_map_pair.first.x;
		if (spacial_map_pair.first.y < min_y) min_y = spacial_map_pair.first.y;
	}
	
	image_t<IMAGE_SIZE> image = {};

	for (int tile_y = 0; tile_y < TILES_COUNT; tile_y++)
	{
		const int offset_y = tile_y * (TILE_SIZE-2);

		for (int tile_x = 0; tile_x < TILES_COUNT; tile_x++)
		{
			const tile_t& tile = spacial_map[{min_x + tile_x, min_y + tile_y}];
			const int offset_x = tile_x * (TILE_SIZE-2);

			for (int y = 1; y < (TILE_SIZE-1); y++)
			{
				for (int x = 1; x < (TILE_SIZE-1); x++)
				{
					image.get(offset_x + x - 1, offset_y + y - 1) = tile.get(x, y);
				}
			}
		}
	}

	for (const auto& orientation : d4_t::all_orientations)
	{
		image.m_orientation = orientation;

		bool any = false;
		for (int x = 0; x < IMAGE_SIZE - MONSTER_WIDTH; x++)
		{
			for (int y = 0; y < IMAGE_SIZE - MONSTER_HEIGHT; y++)
			{
				if (mark_sea_monster(image, x, y))
					any = true;
			}
		}

		if (any)
			break;
	}

	int count = 0;
	for (int x = 0; x < IMAGE_SIZE; x++)
	{
		for (int y = 0; y < IMAGE_SIZE; y++)
		{
			if (image.get(x, y) == '#')
				count++;
		}
	}

	printf("%d", count);

	return 0;
}