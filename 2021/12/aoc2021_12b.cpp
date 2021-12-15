#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

using Connections = std::map<std::string, std::vector<std::string>>;
using SmallCaves = std::map<std::string, int>;

const std::string start("start");
const std::string end("end");

int find_paths(const Connections& cx, SmallCaves& smallCaves, std::string location = start, bool hasSpare = true)
{
	int total = 0;

	for (const auto& nextCave : cx.find(location)->second)
	{
		if (nextCave == end)
		{
			total++;
			continue;
		}

		if (nextCave == start)
			continue;
		
		if (islower(nextCave[0]))
		{
			int& timesVisited = smallCaves[nextCave];

			bool canTravel = true;
			bool usingSpare = false;
			if (timesVisited != 0)
			{
				if (hasSpare) usingSpare = true;
				else canTravel = false;
			}

			if (canTravel)
			{
				timesVisited++;
				total += find_paths(cx, smallCaves, nextCave, hasSpare && !usingSpare);
				timesVisited--;
			}
		}
		else
		{
			total += find_paths(cx, smallCaves, nextCave, hasSpare);
		}
	}

	return total;
}

int main(int argc, const char* argv[])
{
	Connections cx;

	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		const auto ix = line.find('-');

		const std::string a = line.substr(0, ix);
		const std::string b = line.substr(ix + 1);

		cx[a].push_back(b);	
		cx[b].push_back(a);	
	}

	std::cout << find_paths(cx, SmallCaves());

	return 0;
}