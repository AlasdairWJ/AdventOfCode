#include <iostream> // std::cout
#include <string> // std::string, std::getline

int main(int argc, const char* argv[])
{
	int score = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		const int move = static_cast<int>(line[0] - 'A');
		const int result = static_cast<int>(line[2] - 'X');
		const int response = (move + result + 2) % 3;

		score += response + 1;

		if (result == 1)
			score += 3;
		else if (result == 2)
			score += 6;
	}

	std::cout << score;

	return 0;
}