#include <iostream> // std::cout
#include <string> // std::string, std::getline, std::stoi
#include <numeric> // std::accumulate
#include <set> // std::set

int main(int argc, const char* argv[])
{
	std::set<int> top;
	int current = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
		{
			if (top.size() < 3)
			{
				top.emplace(current);
			}
			else if (auto it = top.begin(); current > *it)
			{
				top.erase(it);
				top.emplace(current);
			}

			current = 0;
		}
		else
		{
			current += std::stoi(line);
		}
	}

	std::cout << std::accumulate(top.begin(), top.end(), 0);

	return 0;
}