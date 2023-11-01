#include <iostream>
#include <string> // std::getline
#include <set>

constexpr int N = 14;

int main(int _, const char*[])
{
	std::string line;
	std::getline(std::cin, line);

	int i = 0;
	while (std::set<char>(&line[i], &line[i] + N).size() < N)
		i++;

	std::cout << i + N;
}