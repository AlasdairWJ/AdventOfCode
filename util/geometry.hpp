#ifndef __UTIL_GEOMETRY_HPP
#define __UTIL_GEOMETRY_HPP

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

	auto operator<=>(const Point&) const = default;
};

Point operator+(Point a, const Point& b) { return a += b; }
Point operator-(Point a, const Point& b) { return a -= b; }
Point operator*(Point a, const int value) { return a *= value; }
Point operator*(const int value, Point b) { return b *= value; }
Point operator/(Point a, const int value) { return a /= value; }

} // util

#endif