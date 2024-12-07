#include <iostream>
#include <string>
#include <vector>
#include <ranges>

#include "../../util/separate.hpp"
#include "../util/charconv.hpp"

int main(int _, const char*[])
{
	long long total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto [result_str, equation_str] = util::separate(line, ": ");

		const long long result = util::from_chars<long long>(result_str);

		const auto equation = equation_str 
			| std::views::split(' ')
			| std::views::transform(util::from_chars_t{})
			| std::ranges::to<std::vector>();

		const auto equation_count = equation.size();

		const unsigned combinations = 1u << (equation_count - 1);

		bool solvable = false;

		for (unsigned c = 0u; c < combinations; c++)
		{
			long long r = equation[0];

			for (int n = 1; n < equation_count; n++)
			{
				if ((c & (1u << (n - 1))) == 0u)
				{
					r += equation[n];
				}
				else
				{
					r *= equation[n];
				}
			}

			if (r == result)
			{
				solvable = true;
				break;
			}
		}

		if (solvable)
			total += result;
	}

	std::cout << total;
}