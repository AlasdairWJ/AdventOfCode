#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> //std::vector
#include <utility> //std::pair
#include <set> // std::set
#include <ranges> // std::views::elements
#include <algorithm> // std::ranges::min_element, std::ranges::max_element

int main(int argc, const char* argv[])
{
	const int width = 7;

	using point = std::pair<int, int>;
	const std::set<point> pieces[]
	{
		{
			{0,0}, {0,1}, {0,2}, {0,3}
		},
		{
				   {2,1},
			{1,0}, {1,1}, {1,2},
				   {0,1}
		},
		{
						  {2,2},
						  {1,2},
			{0,0}, {0,1}, {0,2}
		},
		{
			{3,0},
			{2,0},
			{1,0},
			{0,0}
		},
		{
			{1,0}, {1,1},
			{0,0}, {0,1},
		}
	};

	std::string gas;
	std::getline(std::cin, gas);

	int gas_index = 0;

	std::set<point> fallen_rocks;

	int current_piece_index = 0;

	for (int n = 0; n < 2022; n++)
	{
		const int spawn_height = (fallen_rocks.empty() ? 3 : fallen_rocks.rbegin()->first + 4);

		std::vector<point> falling_rocks;
		for (const auto& [y, x] : pieces[current_piece_index])
			falling_rocks.push_back({ y + spawn_height, x + 2 });

		bool blocked = false;

		do
		{
			auto falling_rocks_xs = std::views::elements<1>(falling_rocks);

			if (const char direction = gas[gas_index]; direction == '<')
			{
				const int min_x = *std::ranges::min_element(falling_rocks_xs);

				if (min_x > 0)
				{
					blocked = false;

					for (const auto& [y, x] : falling_rocks)
					{
						if (fallen_rocks.contains({ y, x - 1 }))
						{
							blocked = true;
							break;
						}
					}

					if (!blocked)
					{
						for (auto& [_, x] : falling_rocks)
							x--;
					}
				}
			}
			else
			{
				const int max_x = *std::ranges::max_element(falling_rocks_xs);

				if (max_x < width - 1)
				{
					blocked = false;

					for (const auto& [y, x] : falling_rocks)
					{
						if (fallen_rocks.find({ y, x + 1 }) != fallen_rocks.end())
						{
							blocked = true;
							break;
						}
					}

					if (!blocked)
					{
						for (auto& [_, x] : falling_rocks)
							x++;
					}
				}
			}

			blocked = false;

			for (const auto& [y, x] : falling_rocks)
			{
				if (y == 0 || fallen_rocks.find({ y - 1 , x }) != fallen_rocks.end())
				{
					blocked = true;
					break;
				}
			}

			if (!blocked)
			{
				for (auto& [y, _] : falling_rocks)
					y--;
			}

			++gas_index %= gas.size();
		}
		while (!blocked);

		fallen_rocks.insert(falling_rocks.begin(), falling_rocks.end());

		++current_piece_index %= _countof(pieces);
	}

	std::cout << fallen_rocks.rbegin()->first + 1 << '\n';

	return 0;
}