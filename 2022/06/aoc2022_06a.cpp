#include <iostream>
#include <string>
#include <set>

int main(int argc, const char* argv[])
{
	std::string buffer;
	std::getline(std::cin, buffer);

	int i = 0;
	while (std::set<char>(&buffer[i], &buffer[i] + 4).size() < 4)
		i++;

	std::cout << i + 4;

	return 0;
}