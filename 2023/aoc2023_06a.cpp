#include <iostream>
#include <string>
#include <charconv>
#include <ranges>
#include <cmath>

bool from_chars(auto && r, auto& value)
{
	const char* data = std::ranges::data(r);
	return std::from_chars(data, data + std::ranges::size(r), value).ec == std::errc{};
}

bool solve(const double a, const double b, const double c, double& x1, double& x2)
{
	const double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return false;

	const double sqrt_discriminant = std::sqrt(discriminant);
	x1 = (- b - sqrt_discriminant) / (2 * a);
	x2 = (- b + sqrt_discriminant) / (2 * a);
	return true;
}

const auto non_empty = [](auto && r) { return !r.empty(); };

struct Race
{
	int time, distance;
};

int main(int _, const char*[])
{
	std::vector<Race> races;

	for (const auto member : { &Race::time, &Race::distance })
	{
		std::string line;
		std::getline(std::cin, line);

		std::size_t i = 0;
		for (auto && r : line | std::views::split(' ') | std::views::drop(1) | std::views::filter(non_empty))
		{
			if (int value; from_chars(r, value))
			{
				if (i == races.size())
					races.emplace_back();

				races[i++].*member = value;
			}
		}
	}

	int total = 1;

	for (const auto [time, best_distance] : races)
	{
		double largest_time, smallest_time;
		if (solve(-1, time, -best_distance, largest_time, smallest_time))
			total *= static_cast<int>(std::ceil(largest_time) - std::floor(smallest_time)) - 1;
	}

	std::cout << total;
}