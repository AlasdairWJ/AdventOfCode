#include <iostream>
#include <string>
#include <charconv>
#include <ranges>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <cstdint>

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

int main(int _, const char*[])
{
	int64_t time{}, distance{};

	for (int64_t* pValue : { &time, &distance })
	{
		std::string line;
		std::getline(std::cin, line);

		std::string value_str;

		std::ranges::copy(
			// god knows why i can't construct a string directly from this
			line | std::views::split(' ') | std::views::drop(1) | std::views::join,
			std::back_inserter(value_str)
		);

		if (int64_t value; from_chars(value_str, value))
			*pValue = value;
	}

	double largest_time, smallest_time;
	if (solve(-1, time, -distance, largest_time, smallest_time))
		std::cout << static_cast<int>(std::ceil(largest_time) - std::floor(smallest_time)) - 1;
}