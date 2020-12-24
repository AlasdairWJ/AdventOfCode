#pragma once

struct coord_t
{
	int x, y;

	coord_t() = default;
	coord_t(const int x, const int y) : x(x), y(y) {}

	coord_t& operator+=(const coord_t& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	coord_t& operator-=(const coord_t& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	coord_t operator-() const
	{
		return coord_t(-x, -y);
	}
};

coord_t operator+(const coord_t& a, const coord_t& b)
{
	return coord_t(a) += b;
}

coord_t operator-(const coord_t& a, const coord_t& b)
{
	return coord_t(a) -= b;
}

bool operator==(const coord_t& a, const coord_t& b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator!=(const coord_t& a, const coord_t& b)
{
	return !(a == b);
}

// for maps
bool operator<(const coord_t& a, const coord_t& b)
{
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}