#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	int position = 0;
	int depth = 0;
	int aim = 0;

	std::string direction;
	int amount;
	while (std::cin >> direction, std::cin >> amount)
	{
		if (direction == "up")
		{
			aim -= amount;
		}
		else if (direction == "down")
		{
			aim += amount;
		}
		else if (direction == "forward")
		{
			position += amount;
			depth += aim * amount;
		}
	}

	std::cout << position * depth;

	return 0;
}