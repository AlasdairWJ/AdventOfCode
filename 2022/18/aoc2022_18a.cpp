#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <tuple> // std::tuple
#include <set> // std::set

int main(int argc, const char* argv[])
{
	int surface_area = 0;

	std::set<std::tuple<int, int, int>> cubes;

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		int x, y, z;
		sscanf_s(buffer.c_str(), "%d,%d,%d", &x, &y, &z);

		const int neighbours = cubes.contains({ x - 1, y, z }) +
							   cubes.contains({ x + 1, y, z }) +
							   cubes.contains({ x, y - 1, z }) +
							   cubes.contains({ x, y + 1, z }) +
							   cubes.contains({ x, y, z - 1 }) +
							   cubes.contains({ x, y, z + 1 });

		surface_area += 6 - 2 * neighbours;

		cubes.emplace(x, y, z);
	}

	std::cout << surface_area;

	return 0;
}