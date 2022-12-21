#include <iostream>
#include <string>
#include <set>

int main(int argc, const char* argv[])
{
	std::string buffer;
	std::getline(std::cin, buffer);

	int i = 0;
	while (std::set<char>(&buffer[i], &buffer[int] + 14).size() < 14)
		i++;

	std::cout << i + 14;

	return 0;
}