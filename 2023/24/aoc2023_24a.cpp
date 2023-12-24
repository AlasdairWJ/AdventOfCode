#include <iostream>
#include <string> // std::getline
#include <vector>
#include <cstdint>

#include "../../util/separate.hpp" // util::separate
#include "../../util/charconv.hpp" // util::from_chars

constexpr int64_t Minimum = 200'000'000'000'000;
constexpr int64_t Maximum = 400'000'000'000'000;

// Test data (cba to make it an argv)
//constexpr int64_t Minimum = 7;
//constexpr int64_t Maximum = 27;

struct Stone
{
	int64_t x, y, z;
	int64_t dx, dy, dz;
};

bool intersect(const Stone& a, const Stone& b)
{
	const int64_t det = a.dy * b.dx - a.dx * b.dy;

	if (det == 0)
		return false;
		
	const double t = static_cast<double>(b.dy * (a.x - b.x) + b.dx * (b.y - a.y)) / det;
	const double u = static_cast<double>(a.dy * (a.x - b.x) + a.dx * (b.y - a.y)) / det;

	if (t < 0 || u < 0)
		return false;

	const double x = a.x + t * a.dx;
	const double y = a.y + t * a.dy;

	return Minimum <= x && x <= Maximum && Minimum <= y && y <= Maximum;
}

int main(int _, const char*[])
{
	std::vector<Stone> stones;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto [positions, velocities] = util::separate(line, " @ ");
		
		auto& stone = stones.emplace_back();

		const auto [x1_str, y1_str, z1_str] = util::separate<3>(positions, ", ");
		util::from_chars(x1_str, stone.x);
		util::from_chars(y1_str, stone.y);
		util::from_chars(z1_str, stone.z);

		const auto [x2_str, y2_str, z2_str] = util::separate<3>(velocities, ", ");
		util::from_chars(x2_str, stone.dx);
		util::from_chars(y2_str, stone.dy);
		util::from_chars(z2_str, stone.dz);
	}

	int total = 0;

	for (std::size_t i = 0; i < stones.size(); i++)
	{
		for (std::size_t j = i + 1; j < stones.size(); j++)
		{
			if (intersect(stones[i], stones[j]))
				total++;
		}
	}

	std::cout << total;
}