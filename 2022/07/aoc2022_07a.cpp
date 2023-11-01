#include <iostream>
#include <string> // std::getline
#include <map>
#include <vector>
#include <regex> // std::regex_match
#include <ranges> // std::views::views, std::views::filter
#include <numeric> // std::accumulate

const std::regex command_re{ "^\\$ (\\w+)(?: (.+))?$" };
const std::regex file_re{ "^(\\d+|dir) (.+)$" };

int main(int _, const char*[])
{
	std::string current_path{};

	std::map<std::vector<std::string>, int> folder_sizes;
	std::vector<std::string> current_folder_stack;

	bool needs_next_line = true;
	for (std::string line; needs_next_line ? std::getline(std::cin, line) : std::cin; )
	{
		needs_next_line = true;

		if (std::smatch command_match; std::regex_match(line, command_match, command_pattern))
		{
			const auto command = command_match.str(1);
			if (command == "cd")
			{
				const auto next_folder = command_match.str(2);
				if (next_folder == "..")
				{
					current_folder_stack.pop_back();
				}
				else if (next_folder == "/")
				{
					current_folder_stack.clear();
				}
				else
				{
					current_folder_stack.push_back(next_folder);
				}
			}
			else if (command == "ls")
			{
				while (std::getline(std::cin, line) && line.front() != '$')
				{
					if (std::smatch file_match; std::regex_match(line, file_match, file_re))
					{
						const auto size_or_dir = file_match.str(1);
						if (size_or_dir != "dir")
						{
							const int size = std::stoi(size_or_dir);
							for (auto folder_stack = current_folder_stack; !folder_stack.empty(); )
							{
								folder_sizes[folder_stack] += size;
								folder_stack.pop_back();
							}
						}
					}
				}

				needs_next_line = false;
			}
		}
	}

	auto less_than_100k = [](int x) { return x < 100'000; };

	auto values = folder_sizes | std::views::values | std::views::filter(less_than_100k);

	std::cout << std::accumulate(values.begin(), values.end(), 0);
}