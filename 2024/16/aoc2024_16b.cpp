#include <iostream>
#include <set>
#include <map>

#include "../../util/Point.hpp"
#include "../../util/Grid.hpp"

using util::Point;

constexpr char Empty = '.';
constexpr char Wall = '#';

Point turn_right(const Point& p) { return Point { -p.y, p.x }; }
Point turn_left(const Point& p) { return Point { p.y, -p.x }; }

constexpr int TurnCost = 1'000;

struct Node
{
	int score;
	Point position;
	Point direction;

	auto operator<=>(const Node& p) const = default;
};

int find_route_tile_count(const auto& grid, const Point start, const Point end)
{
	std::map<Point, int> history;
	history[start] = 0;

	std::set<Node> nodes;
	nodes.emplace(Node{ 0, start, Point{ 1, 0 } });

	while (!nodes.empty())
	{
		const auto [score, pos, dir] = *nodes.begin();

		if (pos == end)
			break;

		nodes.erase(nodes.begin());

		if (const auto q = pos + turn_left(dir); grid[q.x, q.y] == Empty)
		{
			const int newScore = score + TurnCost + 1;
			const auto it = history.find(q);

			if (it == history.end() || it->second > newScore)
			{
				nodes.emplace(Node{ newScore, q, turn_left(dir) });
				history[q] = newScore;
			}
		}

		if (const auto q = pos + dir; grid[q.x, q.y] == Empty)
		{
			const int newScore = score + 1;
			const auto it = history.find(q);

			if (it == history.end() || it->second > newScore)
			{
				nodes.emplace(Node{ newScore, q, dir });
				history[q] = newScore;
			}
		}

		if (const auto q = pos + turn_right(dir); grid[q.x, q.y] == Empty)
		{
			const int newScore = score + TurnCost + 1;
			const auto it = history.find(q);

			if (it == history.end() || it->second > newScore)
			{
				nodes.emplace(Node{ newScore, q, turn_right(dir) });
				history[q] = newScore;
			}
		}
	}

	auto final_node = *nodes.begin();
	final_node.direction *= -1;

	nodes.clear();

	nodes.insert(final_node);

	std::set<Point> route;
	route.insert(end);

	while (!nodes.empty())
	{
		const auto [score, pos, dir] = *nodes.begin();

		nodes.erase(nodes.begin());

		if (const auto q = pos + dir; grid[q.x, q.y] == Empty)
		{
			if (const auto it = history.find(q); it != history.end())
			{
				if (it->second == score - 1)
				{
					nodes.emplace(Node{ it->second, q, dir });
					route.insert(q);
				}
				else if (it->second == score - TurnCost - 1)
				{
					nodes.emplace(Node{ score - 1, q, dir });
					nodes.emplace(Node{ it->second, q, turn_left(dir) });
					nodes.emplace(Node{ it->second, q, turn_right(dir) });
					route.insert(q);
				}
			}
		}
	}

	return route.size();
}

int main(int argc, char const *argv[])
{
	util::Grid grid;
	std::cin >> grid;

	const auto [start_x, start_y] = grid.find('S');
	const auto [end_x, end_y] = grid.find('E');

	grid[start_x, start_y] = Empty;
	grid[end_x, end_y] = Empty;
	
	std::cout << find_route_tile_count(grid, Point{ start_x, start_y}, Point{ end_x, end_y });
}