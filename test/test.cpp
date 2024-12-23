#include <iostream>
#include <array>

#include "../util/ranges.hpp"

int main(int argc, char const *argv[])
{
	std::array values = { 4, 5, 6 };

	auto it = util::concat_iterator(
		values.begin(),
		values.end(),
		values.begin()
	);

	auto end = util::concat_iterator(
		values.end(),
		values.end(),
		std::next(values.begin())
	);

//	std::cout << std::input_or_output_iterator<decltype(it)>;

	for (const int x : std::ranges::subrange(it, end))
		std::cout << x << '\n';

//	util::Range r{ it, end };
//
//	for (const auto [a, b] : std::views::adjacent<2>(r))
//		std::cout << a << " - " << b << '\n';
}