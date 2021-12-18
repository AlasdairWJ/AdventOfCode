#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	int valid_count = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		int lower, upper, n;
		char letter;
		sscanf_s(line.c_str(),
				 "%d-%d %c: %n",
				 &lower,
				 &upper,
				 &letter, 1u,
				 &n);

		const std::string password = line.substr(n);

		if ((password[lower-1] == letter) != (password[upper-1] == letter))
			valid_count++;
	}

	std::cout << valid_count;

	return 0;
}