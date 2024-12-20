#include <iostream>
#include <set>
#include <map>

#include "../../util/Grid.hpp"

using util::Point;

constexpr char Empty = '.';
constexpr char Wall = '.';

constexpr int TurnCost = 1'000;

struct Node
{
	int score;
	Point position;
	Point direction;

	auto operator<=>(const Node& p) const = default;
};

int find_minimal_path(const auto& grid, const Point start, const Point end)
{
	std::map<Point, int> history;
	history[start] = 0;

	std::set<Node> nodes;
	nodes.emplace(Node{ 0, start, Point{ 1, 0 } });

	while (!nodes.empty())
	{
		const auto [score, pos, dir] = *nodes.begin();

		if (pos == end)
			return score;

		nodes.erase(nodes.begin());

		if (const auto q = pos + dir.turn_left(); grid[q] == Empty)
		{
			const int newScore = score + TurnCost + 1;
			const auto it = history.find(q);

			if (it == history.end() || it->second > newScore)
			{
				nodes.emplace(Node{ newScore, q, dir.turn_left() });
				history[q] = newScore;
			}
		}

		if (const auto q = pos + dir; grid[q] == Empty)
		{
			const int newScore = score + 1;
			const auto it = history.find(q);

			if (it == history.end() || it->second > newScore)
			{
				nodes.emplace(Node{ newScore, q, dir });
				history[q] = newScore;
			}
		}

		if (const auto q = pos + dir.turn_right(); grid[q] == Empty)
		{
			const int newScore = score + TurnCost + 1;
			const auto it = history.find(q);

			if (it == history.end() || it->second > newScore)
			{
				nodes.emplace(Node{ newScore, q, dir.turn_right() });
				history[q] = newScore;
			}
		}
	}

	return -1;
}

int main(int argc, char const *argv[])
{
	util::Grid grid;
	std::cin >> grid;

	const Point start = grid.find('S');
	const Point end = grid.find('E');

	grid[start] = Empty;
	grid[end] = Empty;

	std::cout << find_minimal_path(grid, start, end);
}