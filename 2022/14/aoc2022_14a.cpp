#include <iostream>
#include <string>
#include <vector>

struct point { int x, y; };

int compare(const int a, const int b)
{
	return (a > b) - (a < b);
}

template<typename T>
struct grid_t
{
	grid_t(const int left, const int right, const int top, const int bottom) :
		m_left(left),
		m_width(right - left + 1),
		m_top(top),
		m_height(bottom - top + 1),
		m_data(std::make_unique<T[]>(m_width * m_height))
	{
	}

	T& at(const int x, const int y)
	{
		return m_data[(y - m_top) * m_width + (x - m_left)];
	}

private:
	const int m_left, m_width, m_top, m_height;
	const std::unique_ptr<T[]> m_data;
};

int main(int argc, const char* argv[])
{
	int left = 500, right = 500, bottom = 0;

	std::vector<std::vector<point>> all_lines; 

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		std::vector<point> lines;

		const char* s = buffer.c_str();
		do
		{
			char* end;
			const int x = std::strtol(s, &end, 10);
			s = end;

			if (x < left)
				left = x;
			if (x > right)
				right = x;

			s++;
			const int y = std::strtol(s, &end, 10);
			s = end;

			if (y > bottom)
				bottom = y;

			if (*s != '\0')
				s += 4;

			lines.push_back({x, y});
		}
		while (*s != '\0');

		all_lines.push_back(lines);
	}
	
	grid_t<bool> grid(left, right, 0, bottom);

	for (const auto& lines : all_lines)
	{
		auto it = lines.begin();
		point p = *it;
		for (it++; it != lines.end(); it++)
		{
			const int dx = compare(it->x, p.x), dy = compare(it->y, p.y);
			for (; p.x != it->x || p.y != it->y; p.x += dx, p.y += dy)
				grid.at(p.x, p.y) = true;
			grid.at(p.x, p.y) = true;
		}
	}

	int units_at_rest = 0;
	bool entered_void = false;
	while (!entered_void)
	{
		point p { 500, 0 };

		bool at_rest = false;
		while (!at_rest && !entered_void)
		{
			if (p.y == bottom)
			{
				entered_void = true;
			}
			else if (!grid.at(p.x, p.y + 1))
			{
				p.y++;
			}
			else if (p.x == left)
			{
				entered_void = true;
			}
			else if (!grid.at(p.x - 1, p.y + 1))
			{
				p.x--;
				p.y++;
			}
			else if (p.x == right)
			{
				entered_void = true;
			}
			else if (!grid.at(p.x + 1, p.y + 1))
			{
				p.x++;
				p.y++;
			}
			else
			{
				at_rest = true;
			}
		}

		if (at_rest)
		{
			grid.at(p.x, p.y) = true;
			units_at_rest++;
		}
	}

	std::cout << units_at_rest;

	return 0;
}
