#include <iostream>
#include <string>
#include <map>

int main(int argc, const char* argv[])
{
	std::string current_path = "";

	std::map<std::string, int> folder_sizes;
	int total_disk_size = 0;

	bool needs_next_line = true;
	std::string buffer;
	while (needs_next_line ? std::getline(std::cin, buffer) : std::cin)
	{
		needs_next_line = true;
		if (buffer.substr(2, 2) == "cd")
		{
			const auto next = buffer.substr(5);
			if (next == "..")
			{
				current_path.resize(current_path.find_last_of('/'));
			}
			else if (next == "/")
			{
				current_path = "";
			}
			else
			{
				current_path.append("/").append(next);
			}
		}
		else if (buffer.substr(2, 2) == "ls")
		{
			while (std::getline(std::cin, buffer) && buffer[0] != '$')
			{
				const auto pos = buffer.find_first_of(' ');
				const auto size_str = buffer.substr(0, pos);
				const auto name = buffer.substr(pos + 1);

				if (size_str != "dir")
				{
					const int size = std::stoi(size_str);

					std::string folder = current_path;
					while (!folder.empty())
					{
						folder_sizes[folder] += size;
						folder = folder.substr(0, folder.find_last_of('/'));
					}
					
					total_disk_size += size;
				}
			}

			needs_next_line = false;
		}
	}

	const int minimum_to_delete = total_disk_size - (70000000 - 30000000);

	int smallest_size = 0;
	for (const auto& [_, size] : folder_sizes)
	{
		if (size > minimum_to_delete)
		{
			if (smallest_size == 0 || size < smallest_size)
				smallest_size = size;
		}
	}

	std::cout << smallest_size;

	return 0;
}