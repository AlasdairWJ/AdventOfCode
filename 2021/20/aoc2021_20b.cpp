#include <iostream>
#include <string>
#include <set>

using Point = std::pair<int, int>;

constexpr char light_pixel = '#', dark_pixel = '.';

int main(int argc, const char* argv[])
{
	std::string alg;
	std::getline(std::cin, alg);

	std::set<Point> pixels;

	{
		std::string line;
		std::getline(std::cin, line); // skip

		int y = 0;
		while (std::getline(std::cin, line) && !line.empty())
		{
			int x = 0;
			for (const char c : line)
			{
				if (c == light_pixel)
					pixels.emplace(x, y);

				x++;
			}
			y++;
		}
	}

	int last_min_x, last_max_x, last_min_y, last_max_y;

	bool is_oob_lit = false;
	for (int step = 0; step < 50; step++)
	{
		auto it = pixels.begin();
		int min_x = it->first, max_x = it->first, min_y = it->second, max_y = it->second;
		for (++it; it != pixels.end(); ++it)
		{
			if (it->first < min_x) min_x = it->first;
			if (it->second < min_y) min_y = it->second;
			if (it->first > max_x) max_x = it->first;
			if (it->second > max_y) max_y = it->second;
		}

		if (step == 0)
		{
			last_min_x = min_x;
			last_max_x = max_x;
			last_min_y = min_y;
			last_max_y = max_y;
		}

		std::set<Point> next;

		for (int y = min_y - 1; y <= max_y + 1; y++)
		{
			for (int x = min_x - 1; x <= max_x + 1; x++)
			{
				unsigned ix = 0;
				unsigned b = 1;
				for (int dy = 1; dy >= -1; --dy)
				{
					for (int dx = 1; dx >= -1; --dx)
					{
						bool is_lit = false;

						if (x + dx < last_min_x - 1 ||
							y + dy < last_min_y - 1 ||
							x + dx > last_max_x + 1 ||
							y + dy > last_max_y + 1)
						{
							is_lit = is_oob_lit;
						}
						else if (pixels.find({x + dx, y + dy}) != pixels.end())
						{
							is_lit = true;
						}

						if (is_lit)
							ix |= b;

						b <<= 1;
					}
				}

				if (alg[ix] == light_pixel)
					next.emplace(x, y);
			}
		}

		is_oob_lit = (is_oob_lit ? alg.back() : alg.front()) == light_pixel;

		last_min_x = min_x;
		last_max_x = max_x;
		last_min_y = min_y;
		last_max_y = max_y;

		pixels.swap(next);
	}

	std::cout << pixels.size();

	return 0;
}