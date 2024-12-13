#include <iostream>
#include <string>
#include <regex>

#include "../util/charconv.hpp"
#include "../../util/linear_algebra.hpp"

constexpr long long Offset = 10'000'000'000'000ll;

int main(int _, const char*[])
{
	const std::regex button_pattern{ "^Button [AB]: X\\+(\\d+), Y\\+(\\d+)$" };
	const std::regex prize_pattern{ "^Prize: X=(\\d+), Y=(\\d+)$" };

	long long total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::smatch match;
		std::regex_match(line, match, button_pattern);

		long long A[2][2]{};

		A[0][0] = util::from_chars<long long>(match[1]);
		A[1][0] = util::from_chars<long long>(match[2]);

		std::getline(std::cin, line);
		std::regex_match(line, match, button_pattern);

		A[0][1] = util::from_chars<long long>(match[1]);
		A[1][1] = util::from_chars<long long>(match[2]);

		long long x[2]{};

		std::getline(std::cin, line);
		std::regex_match(line, match, prize_pattern);

		x[0] = util::from_chars<long long>(match[1]);
		x[1] = util::from_chars<long long>(match[2]);

		x[0] += Offset;
		x[1] += Offset;

		long long y[2]{};

		if (util::solve(A, x, y))
			total += 3 * y[0] + y[1];

		std::getline(std::cin, line); // skip empty line
	}

	std::cout << total;
}