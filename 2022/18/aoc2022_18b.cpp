#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <tuple> // std::tuple
#include <set> // std::set
#include <ranges> // std::views::elements
#include <algorithm> // std::ranges::minmax_element

using point = std::tuple<int, int, int>;

int surface_area(const std::set<point>& cubes)
{
	int surface_area = 0;

	for (const auto& [x, y, z] : cubes)
	{
		const int neighbours = cubes.contains({ x - 1, y, z }) +
							   cubes.contains({ x + 1, y, z }) +
							   cubes.contains({ x, y - 1, z }) +
							   cubes.contains({ x, y + 1, z }) +
							   cubes.contains({ x, y, z - 1 }) +
							   cubes.contains({ x, y, z + 1 });

		surface_area += 6 - neighbours;
	}

	return surface_area;
}

int main(int argc, const char* argv[])
{
	std::set<point> cubes;

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		int x, y, z;
		sscanf_s(buffer.c_str(), "%d,%d,%d", &x, &y, &z);
		cubes.emplace(x, y, z);
	}

	const int total_surface_area = surface_area(cubes);

	auto all_x = std::views::elements<0>(cubes);
	auto all_y = std::views::elements<1>(cubes);
	auto all_z = std::views::elements<2>(cubes);

	const auto [left_it, right_it] = std::ranges::minmax_element(all_x);
	const auto [top_it, bottom_it] = std::ranges::minmax_element(all_y);
	const auto [front_it, back_it] = std::ranges::minmax_element(all_z);

	const int left = *left_it, right = *right_it;
	const int top = *top_it, bottom = *bottom_it;
	const int front = *front_it, back = *back_it;

	int internal_surface_area = 0;

	point p;
	auto& [x, y, z] = p;

	for (x = left; x != right; x++)
	{
		for (y = top; y != bottom; y++)
		{
			for (z = front; z != back; z++)
			{
				if (cubes.contains(p))
					continue;

				std::set<point> shape;
				std::set<point> current{ p };

				bool is_on_edge = false;

				while (!current.empty())
				{
					shape.insert(current.begin(), current.end());

					std::set<point> next;

					for (const auto& [x, y, z] : current)
					{
						if (x > left)
						{
							if (point q{ x - 1,  y, z }; !cubes.contains(q) && !shape.contains(q))
								next.insert(q);
						}
						else is_on_edge = true;

						if (x < right)
						{
							if (point q{ x + 1, y, z }; !cubes.contains(q) && !shape.contains(q))
								next.insert(q);
						}
						else is_on_edge = true;

						if (y > top)
						{
							if (point q{ x, y - 1, z }; !cubes.contains(q) && !shape.contains(q))
								next.insert(q);
						}
						else is_on_edge = true;

						if (y < bottom)
						{
							if (point q{ x, y + 1, z }; !cubes.contains(q) && !shape.contains(q))
								next.insert(q);
						}
						else is_on_edge = true;

						if (z > front)
						{
							if (point q{ x, y, z - 1 }; !cubes.contains(q) && !shape.contains(q))
								next.insert(q);
						}
						else is_on_edge = true;

						if (z < back)
						{
							if (point q{ x, y, z + 1 }; !cubes.contains(q) && !shape.contains(q))
								next.insert(q);
						}
						else is_on_edge = true;
					}

					current.swap(next);
				}

				if (!is_on_edge)
					internal_surface_area += surface_area(shape);

				cubes.insert(shape.begin(), shape.end());
			}
		}
	}

	std::cout << total_surface_area - internal_surface_area;

	return 0;
}