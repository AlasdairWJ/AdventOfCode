#ifndef __UTIL_GRID_HPP
#define __UTIL_GRID_HPP

#include <vector>
#include <string>
#include <iostream>

#include "Point.hpp"

namespace util
{

struct Grid
{
	Grid() = default;

	Grid(const int w, const int h)
		: _lines(
			static_cast<std::size_t>(h),
			std::string(
				static_cast<std::size_t>(w),
				' '
			)
		)
		, _width{ w }
		, _height{ h }
	{
	}

	int width() const { return _width; }
	int height() const { return _height; }

	char& operator[](const int x, const int y) { return _lines[y][x]; }
	char& operator[](const util::Point& p) { return _lines[p.y][p.x]; }

	char operator[](const int x, const int y) const { return _lines[y][x]; }
	char operator[](const util::Point& p) const { return _lines[p.y][p.x]; }

	void strip_edges()
	{
		_lines.erase(_lines.begin());
		_lines.erase(_lines.end() - 1);

		for (auto& line : _lines)
		{
			line.erase(line.begin());
			line.erase(line.end() - 1);
		}

		_width -= 2;
		_height -= 2;
	}

	bool in_bounds(const util::Point& p) const
	{
		return
			p.x >= 0 &&
			p.y >= 0 &&
			p.x < _width && 
			p.y < _height;
	}

	std::string& operator[](int y) { return _lines[y]; }
	const std::string& operator[](int y) const { return _lines[y]; }

	auto begin() { return _lines.begin(); }
	auto end() { return _lines.end(); }

	auto cbegin() const { return _lines.cbegin(); }
	auto cend() const { return _lines.cend(); }

	auto begin() const { return _lines.begin(); }
	auto end() const { return _lines.end(); }

	util::Point find(const char c)
	{
		for (int y = 0; y < _height; y++)
		{
			if (const auto pos = _lines[y].find(c); pos != std::string::npos)
				return { static_cast<int>(pos), y };
		}
		
		return { -1, -1 };
	}

private:
	int _width;
	int _height;
	std::vector<std::string> _lines;

	friend std::istream& operator>>(std::istream&, Grid& grid);
	friend std::ostream& operator<<(std::ostream&, const Grid& grid);
};

inline std::istream& operator>>(std::istream& is, Grid& grid)
{
	grid._lines.clear();

	for (std::string line; std::getline(is, line) && !line.empty(); )
		grid._lines.push_back(line);

	grid._width = static_cast<int>(grid._lines.front().size());
	grid._height = static_cast<int>(grid._lines.size());

	return is;
}

inline std::ostream& operator<<(std::ostream& os, const Grid& grid)
{
	for (const auto& line : grid._lines)
		os << line << '\n';	

	return os;
}

}

#endif // __UTIL_GRID_HPP