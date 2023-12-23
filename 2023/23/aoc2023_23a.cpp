#include <iostream>
#include <string> // std::getline
#include <vector>
#include <map>
#include <set>

#include "../../util/geometry.hpp" // util::Point

using Point = util::Point;

constexpr Point Directions[]{
	Point{ 1, 0 },
	Point{ 0, 1 },
	Point{ -1, 0 },
	Point{ 0, -1 }
};

struct Node
{
	std::map<Point, int> connections;
};

struct State
{
	Point pos;
	std::set<Point> visited;
	int distance;
};

int main(int _, const char*[])
{
	std::vector<std::string> grid;

	for (std::string line; std::getline(std::cin, line); )
		grid.push_back(line);

	const int size = static_cast<int>(grid.size());

	std::map<Point, Node> nodes;

	const Point startingNode{ static_cast<int>(grid.front().find('.')), 0 };
	const Point finishingNode{ static_cast<int>(grid.back().find('.')), size - 1 };

	nodes[startingNode];
	nodes[finishingNode];

	for (int y = 1; y < size - 1; y++)
	{
		for (int x = 1; x < size - 1; x++)
		{
			if (grid[y][x] == '#')
				continue;

			int directions = 0;

			for (const auto [dx, dy] : Directions)
			{
				if (grid[y + dy][x + dx] != '#')
					directions++;
			}

			if (directions > 2)
				nodes[Point{ x, y }];				
		}
	}

	for (const auto& [start, node] : nodes)
	{
		std::map<Point, std::pair<char, int>> current{ std::make_pair(start, std::make_pair(' ', 0)) };

		while (!current.empty())
		{
			decltype(current) next;

			for (const auto& [p, chr_dist_pair] : current)
			{
				const auto& [c, dist] = chr_dist_pair;

				if (c != ' ' && nodes.contains(p))
				{
					if (int& d = nodes[start].connections[p]; d < dist)
						d = dist;

					continue;
				}

				// up
				if (p.y > 0 && c != 'v' && (grid[p.y - 1][p.x] == '.' || grid[p.y - 1][p.x] == '^'))
					next.emplace(Point{ p.x, p.y - 1 }, std::make_pair('^', dist + 1));

				// down
				if (p.y < (size - 1) && c != '^' && (grid[p.y + 1][p.x] == '.' || grid[p.y + 1][p.x] == 'v'))
					next.emplace(Point{ p.x, p.y + 1 }, std::make_pair('v', dist + 1));

				// left
				if (p.x > 0 && c != '>' && (grid[p.y][p.x - 1] == '.' || grid[p.y][p.x - 1] == '<'))
					next.emplace(Point{ p.x - 1, p.y }, std::make_pair('<', dist + 1));

				// right
				if (p.x < (size - 1) && c != '<' && (grid[p.y][p.x + 1] == '.' || grid[p.y][p.x + 1] == '>'))
					next.emplace(Point{ p.x + 1, p.y }, std::make_pair('>', dist + 1));
			}

			next.swap(current);
		}
	}

	std::vector<State> current{ State{ startingNode } };

	int longestDistance = 0;

	while (!current.empty())
	{
		decltype(current) next;

		for (auto& state : current)
		{
			if (state.pos == finishingNode)
			{
				if (state.distance > longestDistance)
					longestDistance = state.distance;

				continue;
			}

			state.visited.insert(state.pos);

			const auto& connections = nodes.find(state.pos)->second.connections;

			for (const auto& [nextNode, distanceTo] : connections)
			{
				if (!state.visited.contains(nextNode))
				{
					next.emplace_back(
						nextNode,
						state.visited, 
						state.distance + distanceTo
					);
				}
			}
		}

		current.swap(next);
	}

	std::cout << longestDistance;
}