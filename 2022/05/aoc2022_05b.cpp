#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, const char* argv[])
{
	std::string buffer;
	std::getline(std::cin, buffer);

	const int column_count = (buffer.size() + 1) / 4;
	
	std::vector<std::vector<char>> columns(column_count);

	do
	{
		for (int i = 0; i < column_count; i++)
		{
			const char l = buffer[4 * i + 1];
			if (l != ' ' && !isdigit(l))
				columns[i].push_back(l);
		}
	}
	while (std::getline(std::cin, buffer), !buffer.empty());

	for (auto& column : columns)
		std::reverse(column.begin(), column.end());

	while (std::getline(std::cin, buffer))
	{
		int n, from, to;
		sscanf_s(buffer.c_str(), "move %d from %d to %d", &n, &from, &to);

		auto &from_column = columns[from - 1],
			 &to_column = columns[to - 1];

		const auto it = from_column.end() - n;
		to_column.insert(to_column.end(), it, from_column.end());
		from_column.erase(it, from_column.end());
	}

	for (const auto& column : columns)
		std::cout << column.back();

	return 0;
}