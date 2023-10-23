#include <iostream>
#include <string>

int main(int _, const char*[])
{
	int count = 0;

	std::string line;
	for (int x = 0; std::getline(std::cin, line); x += 3)
	{
		if (line[x % static_cast<int>(line.size())] == '#')
			count++;
	}

	std::cout << count;
}