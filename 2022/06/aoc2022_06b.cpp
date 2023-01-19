#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <set> // std::set

int main(int argc, const char* argv[])
{
	std::string line;
	std::getline(std::cin, line);

	int i = 0;
	while (std::set<char>(&line[i], &line[i] + 14).size() < 14)
		i++;

	std::cout << i + 14;

	return 0;
}