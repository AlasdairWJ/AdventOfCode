#ifndef __UTIL_GEOMETRY_HPP
#define __UTIL_GEOMETRY_HPP

#include <cmath>

namespace util
{
struct Point
{
	int x, y;

	Point& operator+=(const Point& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Point& operator-=(const Point& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Point& operator*=(const int value)
	{
		x *= value;
		y *= value;
		return *this;
	}

	Point& operator/=(const int value)
	{
		x /= value;
		y /= value;
		return *this;
	}

	Point turn_left() const
	{
		return Point{ y, -x };
	}

	Point turn_right() const
	{
		return Point{ -y, x };
	}

	auto operator<=>(const Point&) const = default;

	static bool CompareX(const Point& lhs, const Point& rhs) { return lhs.x < rhs.x; }
	static bool CompareY(const Point& lhs, const Point& rhs) { return lhs.y < rhs.y; }
};

Point operator+(const Point& p) { return p; }
Point operator-(const Point& p) { return Point{ -p.x, -p.y }; }
Point operator+(Point a, const Point& b) { return a += b; }
Point operator-(Point a, const Point& b) { return a -= b; }
Point operator*(Point a, const int value) { return a *= value; }
Point operator*(const int value, Point b) { return b *= value; }
Point operator/(Point a, const int value) { return a /= value; }
	
constexpr Point Up{ 0, -1 };
constexpr Point Down{ 0, 1 };
constexpr Point Left{ -1, 0 };
constexpr Point Right{ 1, 0 };

constexpr Point UnitDirections[]{
	Up,
	Down,
	Left,
	Right
};

} // util

#endif