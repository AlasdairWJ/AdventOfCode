#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>

typedef long long i64;

constexpr int digit(const char c)
{
	return static_cast<int>(c - '0');
}

i64 accumulate(const auto& items, const char op)
{
	switch (op)
	{
	case '+':
		return std::accumulate(items.begin(), items.end(), i64{});
	case '*':
		return std::accumulate(items.begin(), items.end(), i64{ 1 }, std::multiplies<i64>{});
	default:
		return 0;
	}
}

int main()
{
	std::vector<std::string> lines;

	for (std::string line; std::getline(std::cin, line); )
		lines.push_back(line);

	const std::string op_row = lines.back();
	lines.erase(lines.end() - 1);

	const std::size_t len = op_row.size();

	i64 total{};

	for (std::size_t ix = 0, next_ix; ix < len; ix = next_ix)
	{
		const char op = op_row[ix];

		next_ix = std::min(op_row.find_first_not_of(' ', ix + 1), len);

		std::vector<i64> items;

		for (; ix < next_ix; ix++)
		{
			i64 x{};

			for (const auto& row : lines)
			{
				if (row[ix] != ' ')
					x = 10 * x + digit(row[ix]);
			}

			if (x != 0)
				items.push_back(x);
		}

		total += accumulate(items, op);
	}

	std::cout << total;
}
