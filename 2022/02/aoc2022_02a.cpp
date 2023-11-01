#include <iostream>
#include <string> // std::getline

int main(int _, const char*[])
{
	int score = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const int move = int{ line[0] - 'A' };
		const int response = int { line[2] - 'X' };
		const int result = (response + 4 - move) % 3;

		score += response + 1;

		if (result == 1)
			score += 3;
		else if (result == 2)
			score += 6;
	}

	std::cout << score;
}