#include <iostream>
#include <string> // std::getline
#include <vector>
#include <ranges> // std::views::reverse
#include <regex> // std::regex_match

#include "../../util/charconv.hpp" // util::from_chars

const std::regex move_re{ "^move (\\d+) from (\\d+) to (\\d+)$" };

int main(int _, const char*[])
{
	std::vector<std::string> stack_buffer;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
		stack_buffer.push_back(line);

	const int column_count = (stack_buffer.back().size() + 1) / 4;
	stack_buffer.pop_back();

	std::vector<std::vector<char>> columns(column_count);

	for (const std::string& line : stack_buffer | std::views::reverse)
	{
		for (int i = 0; i < column_count; i++)
			if (const char l = line[4 * i + 1]; l != ' ')
				columns[i].push_back(l);
	}

	for (std::string line; std::getline(std::cin, line); )
	{
		if (std::smatch match; std::regex_match(line, match, move_re))
		{
			int n, from, to;
			util::from_chars(match[1], n);
			util::from_chars(match[2], from);
			util::from_chars(match[3], to);

			auto& from_column = columns[from - 1];
			auto& to_column = columns[to - 1];	
			
			const auto it = from_column.end() - n;
			to_column.insert(to_column.end(), it, from_column.end());
			from_column.erase(it, from_column.end());
		}
	}

	for (const auto& column : columns)
		std::cout << column.back();
}