#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	int score = 0;

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		const int move = static_cast<int>(buffer[0] - 'A');
		const int response = static_cast<int>(buffer[2] - 'X');
		const int result = (response + 4 - move) % 3;
		
		score += response + 1;

		if (result == 1)
			score += 3;
		else if (result == 2)
			score += 6;
	}

	std::cout << score;

	return 0;
}