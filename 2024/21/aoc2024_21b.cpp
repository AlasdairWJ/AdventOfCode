#include <iostream>
#include <string>
#include <map>

#include "../../util/Point.hpp"

using util::Point;

typedef long long i64;

constexpr int Layers = 25;

constexpr char NumericalPad[][3]{
	{ '7', '8', '9' },
	{ '4', '5', '6' },
	{ '1', '2', '3' },
	{ ' ', '0', 'A' },
};

constexpr char DirectionalPad[][3]{
	{ ' ', '^', 'A' },
	{ '<', 'v', '>' },
};

constexpr char NumericalButtons[]{ 'A', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

constexpr char DirectionalButtons[]{ 'A', '^', '<', 'v', '>' };

struct Route
{
	bool is_unique() const { return _count == 1; }

	void add(const std::string& p)
	{
		_paths[_count++].assign(p).push_back('A');
	}

	void add(const int n, const char c)
	{
		_paths[_count++].assign(n, c).push_back('A');
	}

	const std::string& path(const int id = 0) const { return _paths[id]; }

private:
	int _count;
	std::string _paths[2];
};

std::map<char, Point> make_button_map(const auto& grid)
{
	std::map<char, Point> buttons;	

	Point p{};
	for (const auto& row : grid)
	{
		p.x = 0;

		for (const auto& c : row)
		{
			const auto it = buttons.emplace(c, p);

			p.x++;
		}

		p.y++;
	}

	return buttons;
}

Route calculate_route_between(const char a, const char b, const auto& map)
{
	const auto& src = map.find(a)->second;
	const auto& dst = map.find(b)->second;

	const auto d = dst - src;

	Route route{};

	if (d.x == 0 || d.y == 0)
	{
		if (d.x == 0)
		{
			route.add(std::abs(d.y), d.y < 0 ? '^' : 'v');
		}
		else
		{
			route.add(std::abs(d.x), d.x < 0 ? '<' : '>');
		}
	}
	else
	{
		const auto blankPos = map.find(' ')->second;

		const bool is_blocked_hori = (Point { dst.x, src.y } == blankPos);

		if (!is_blocked_hori)
		{
			std::string path;
			path.append(std::abs(d.x), d.x < 0 ? '<' : '>');
			path.append(std::abs(d.y), d.y < 0 ? '^' : 'v');
			route.add(path);
		}

		const bool is_blocked_vert = (Point { src.x, dst.y } == blankPos);

		if (!is_blocked_vert)
		{
			std::string path;
			path.append(std::abs(d.y), d.y < 0 ? '^' : 'v');
			path.append(std::abs(d.x), d.x < 0 ? '<' : '>');
			route.add(path);
		}
	}

	return route;
}

std::map<std::pair<char, char>, Route> routes;
std::map<std::tuple<char, char, int>, i64> cost_cache;

i64 cost(const std::string& sequence, const int layer);

i64 cost(const char a, const char b, const int layer)
{
	if (a == b)
		return 1; // just A

	const auto& route = routes.find(std::make_pair(a, b))->second;

	if (layer == 0)
	{
		return route.path().size(); // always the same either way (plus A)
	}

	const auto it = cost_cache.find(std::make_tuple(a, b, layer));

	if (it != cost_cache.end())
		return it->second;

	i64 c;

	if (route.is_unique())
	{
		c = cost(route.path(), layer - 1);
	}
	else
	{
		c = std::min(
			cost(route.path(0), layer - 1),
			cost(route.path(1), layer - 1)
		);
	}

	cost_cache.emplace(std::make_tuple(a, b, layer), c);

	return c;
}

i64 cost(const std::string& sequence, const int layer)
{
	char prev = 'A';

	i64 c = 0;
	for (const char next : sequence)
	{
		c += cost(prev, next, layer);
		prev = next;
	}

	return c;
}

int main(int _, const char*[])
{
	const auto numericalMap = make_button_map(NumericalPad);
	const auto directionalMap = make_button_map(DirectionalPad);

	for (const char a : NumericalButtons)
	{
		for (const char b : NumericalButtons)
		{
			if (a == b)
				continue;

			routes.emplace(std::make_pair(a, b), calculate_route_between(a, b, numericalMap));
		}
	}

	for (const char a : DirectionalButtons)
	{
		for (const char b : DirectionalButtons)
		{
			if (a == b)
				continue;

			routes.emplace(std::make_pair(a, b), calculate_route_between(a, b, directionalMap));
		}
	}

	i64 total = 0;

	for (std::string sequence; std::getline(std::cin, sequence); )
	{
		total += cost(sequence, Layers) * std::stoi(sequence.substr(0, 3));
	}

	std::cout << total;
}