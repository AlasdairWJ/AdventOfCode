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

	char current_op = op_row[0];
	const int rows = static_cast<int>(lines.size());
	const int len = static_cast<int>(lines.front().size());

	i64 total{};
	std::vector<i64> items;

	for (int ix = 0; ix < len; ix++)
	{
		if (op_row[ix] != ' ')
			current_op = op_row[ix];

		i64 x{};
		for (const auto& row : lines)
		{
			if (row[ix] != ' ')
				x = 10 * x + digit(row[ix]);
		}

		if (x != 0)
		{
			items.push_back(x);
		}
		else
		{
			total += accumulate(items, current_op);
			items.clear();
		}
	}

	if (!items.empty())
		total += accumulate(items, current_op);

	std::cout << total;
}
