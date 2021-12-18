#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm> // std::transform

constexpr int N = 5;

struct Point
{
	int x, y;

	Point() = default;
	Point(const int x, const int y) : x(x), y(y) {};
	bool operator<(const Point& other) const { return x < other.x || (x == other.x && y < other.y); }
};

const int deltas[][2] = {{ 1, 0},
						 { 0, 1},
						 {-1, 0},
						 { 0,-1}};

int main(int argc, const char* argv[])
{
	std::vector<std::vector<int>> original_risk_grid;

	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		std::vector<int> row(line.size());
		std::transform(line.begin(), line.end(), row.begin(), [](char x) { return x - '0'; });

		original_risk_grid.push_back(row);
	}

	const int original_size_y = original_risk_grid.size();
	const int original_size_x = original_risk_grid[0].size();
	const int size_y = N * original_size_x;
	const int size_x = N * original_size_x;

	std::vector<int> buffer(size_x * size_y);

	const auto at = [&](const Point& p) -> int& { return buffer[p.x + size_x * p.y]; };

	const auto get_original = [&](Point p)
	{
		int i = 0;
		while (p.x >= original_size_x) p.x -= original_size_x, i++;
		while (p.y >= original_size_y) p.y -= original_size_y, i++;
		return (original_risk_grid[p.y][p.x] + i - 1) % 9 + 1;
	};

	std::set<Point> to_check;
	to_check.emplace();

	while (true)
	{
		std::set<Point> to_check_next;

		for (const auto& p : to_check)
		{
			const int& p_value = at(p);

			for (const auto& delta : deltas)
			{
				const Point q(p.x + delta[0], p.y + delta[1]);
				if (q.x >= 0 && q.y >= 0 && q.x < size_x && q.y < size_y)
				{
					int& q_value = at(q);

					const int next_q_value = p_value + get_original(q);
					if (q_value == 0 || next_q_value < q_value)
					{
						q_value = next_q_value;
						to_check_next.emplace(q);
					}
				}
			}
		}

		if (to_check_next.empty())
			break;

		to_check = std::move(to_check_next);
	}

	std::cout << buffer.back();

	return 0;
}