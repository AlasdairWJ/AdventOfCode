#include <iostream>
#include <string> // std::getline
#include <vector>
#include <map>
#include <set>
#include <charconv>
#include <algorithm>
#include <ranges>

#include "../../util/separate.hpp" // util::separate
#include "../../util/charconv.hpp" // util::from_chars

struct Cuboid
{
	int x1, y1, z1;
	int x2, y2, z2;
};

struct Point
{
	int x, y;

	auto operator<=>(const Point&) const = default;
};

int main(const int argc, const char* argv[])
{
	std::vector<Cuboid> cuboids;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto [start_indices, end_indices] = util::separate(line, "~");

		auto& cuboid = cuboids.emplace_back();

		const auto [x1_str, y1_str, z1_str] = util::separate<3>(start_indices, ",");
		util::from_chars(x1_str, cuboid.x1);
		util::from_chars(y1_str, cuboid.y1);
		util::from_chars(z1_str, cuboid.z1);

		const auto [x2_str, y2_str, z2_str] = util::separate<3>(end_indices, ",");
		util::from_chars(x2_str, cuboid.x2);
		util::from_chars(y2_str, cuboid.y2);
		util::from_chars(z2_str, cuboid.z2);
	}

	std::ranges::sort(cuboids, [](auto && c1, auto && c2) { return c1.z1 < c2.z1; });
	
	std::map<Point, std::pair<int, int>> heightMap;
	std::vector<bool> isRemovable(cuboids.size(), true);

	for (auto && [blockID, cuboid] : cuboids | std::views::enumerate)
	{
		int maxHeight = 0;
		std::set<int> restingOn;

		for (Point p{ cuboid.x1, cuboid.y1 }; p.x <= cuboid.x2; p.x++)
		{
			for (p.y = cuboid.y1; p.y <= cuboid.y2; p.y++)
			{
				if (auto it = heightMap.find(p); it != heightMap.end())
				{
					const auto [id, height] = it->second;

					if (height > maxHeight)
					{
						restingOn.clear();
						maxHeight = height;
					}

					if (height == maxHeight)
					{
						restingOn.insert(id);
					}
				}
			}
		}

		for (Point p{ cuboid.x1, cuboid.y1 }; p.x <= cuboid.x2; p.x++)
		{
			for (p.y = cuboid.y1; p.y <= cuboid.y2; p.y++)
			{
				heightMap[p] = std::make_pair(blockID, maxHeight + (cuboid.z2 - cuboid.z1 + 1));
			}
		}
		
		if (restingOn.size() == 1)
		{
			isRemovable[*restingOn.begin()] = false;
		}
	}

	std::cout << std::ranges::count(isRemovable, true);
}