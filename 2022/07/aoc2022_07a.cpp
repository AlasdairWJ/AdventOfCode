#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <map> // std::map
#include <vector> // std::vector
#include <regex> // std::regex, std::smatch, std::regex_match
#include <ranges> // std::views::transform, std::views::filter
#include <numeric> // std::accumulate

int main(int argc, const char* argv[])
{
	std::string current_path = "";

	std::map<std::vector<std::string>, int> folder_sizes;
	std::vector<std::string> current_folder_stack;

	bool needs_next_line = true;
	std::string line;
	while (needs_next_line ? std::getline(std::cin, line) : std::cin)
	{
		needs_next_line = true;

		static const std::regex command_pattern{"^\\$ (\\w+)(?: (.+))?$"};

		std::smatch command_match;
		if (std::regex_match(line, command_match, command_pattern))
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
					static const std::regex file_pattern{ "^(\\d+|dir) (.+)$" };

					std::smatch file_match;
					if (std::regex_match(line, file_match, file_pattern))
					{
						const auto size_param = file_match.str(1);

						if (size_param != "dir")
						{
							const int size = std::stoi(size_param);

							auto folder_stack = current_folder_stack;
							while (!folder_stack.empty())
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

	const auto less_than_100k = [](int x) { return x < 100'000; };

	auto values = folder_sizes | std::views::values | std::views::filter(less_than_100k);

	std::cout<< std::accumulate(values.begin(), values.end(), 0);


	return 0;
}