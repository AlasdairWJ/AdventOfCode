#include <iostream>
#include <string> // std::getline
#include <map>
#include <vector>
#include <regex> // std::regex_match
#include <ranges> // std::views::views, std::views::filter
#include <algorithm> // std::ranges::min_element

const std::regex command_re{ "^\\$ (\\w+)(?: (.+))?$" };
const std::regex file_re{ "^(\\d+|dir) (.+)$" };

int main(int _, const char*[])
{
	std::map<std::vector<std::string>, int> folder_sizes;
	std::vector<std::string> current_folder_stack;

	int total_disk_size = 0;

	bool needs_next_line = true;
	for (std::string line; needs_next_line ? std::getline(std::cin, line) : std::cin; )
	{
		needs_next_line = true;

		if (std::smatch command_match; std::regex_match(line, command_match, command_re))
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
					std::smatch file_match;
					if (std::regex_match(line, file_match, file_re))
					{
						const auto size_param = file_match.str(1);

						if (size_param != "dir")
						{
							const int size = std::stoi(size_param);
							for (auto folder_stack = current_folder_stack; !folder_stack.empty(); )
							{
								folder_sizes[folder_stack] += size;
								folder_stack.pop_back();
							}

							total_disk_size += size;
						}
					}
				}

				needs_next_line = false;
			}
		}
	}


	const int minimum_to_delete = total_disk_size - (70'000'000 - 30'000'000);

	sauto could_free_enough_space = [&minimum_to_delete](int x) { return x > minimum_to_delete; };

	auto values = folder_sizes | std::views::values | std::views::filter(could_free_enough_space);

	std::cout << *std::ranges::min_element(values);
}