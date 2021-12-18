#include <iostream>
#include <string>
#include <algorithm> // std::count

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
		
		const int letter_count = std::count(password.begin(),
											password.end(),
											letter);

		if (lower <= letter_count && letter_count <= upper)
			valid_count++;
	}

	std::cout << valid_count;

	return 0;
}