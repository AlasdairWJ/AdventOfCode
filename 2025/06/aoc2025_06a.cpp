#include <iostream>
#include <string>
#include <string_view>
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

	const std::size_t len = op_row.size();

	i64 total{};

	for (std::size_t ix = 0, next_ix; ix < len; ix = next_ix)
	{
		next_ix = std::min(op_row.find_first_not_of(' ', ix + 1), len);

		std::vector<i64> items;

		for (const std::string& row : lines)
		{
			const auto str = std::string_view{ row }.substr(ix, next_ix - 1); 
			const std::size_t num_start_ix = str.find_first_not_of(' ');
			const std::size_t num_end_ix = std::min(str.find(' ', num_start_ix), str.size());

			std::from_chars(
				str.data() + num_start_ix, 
				str.data() + num_end_ix, 
				items.emplace_back()
			);
		}

		total += accumulate(items, op_row[ix]);
	}

	std::cout << total;
}
