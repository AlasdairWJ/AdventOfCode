#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <charconv>

typedef long long i64;

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

	const std::size_t len = lines[0].size();

	i64 total{};

	for (std::size_t ix = 0; ix < len; )
	{
		std::vector<i64> items;

		for (const std::string& row : lines)
		{
			const std::size_t num_start_ix = row.find_first_not_of(' ', ix);
			std::size_t num_end_ix = row.find(' ', num_start_ix);

			if (num_end_ix == std::string::npos)
				num_end_ix = row.size();

			std::from_chars(row.data() + num_start_ix, row.data() + num_end_ix, items.emplace_back());
		}

		total += accumulate(items, op_row[ix]);;

		ix = op_row.find_first_not_of(' ', ix + 1);
	}

	std::cout << total;
}
//		