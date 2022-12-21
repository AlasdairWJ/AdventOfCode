#include <iostream>
#include <numeric>
#include <string>
#include <set>

int main(int argc, const char* argv[])
{
	std::set<int> top;
	int current = 0;

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		if (buffer.empty())
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
			current += std::stoi(buffer);
		}
	}

	std::cout << std::accumulate(top.begin(), top.end(), 0);
	
	return 0;
}