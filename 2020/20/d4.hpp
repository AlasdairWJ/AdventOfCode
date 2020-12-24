#pragma once

struct d4_t
{
	int r;
	int s;

	d4_t(int r = 0, int s = 0)
		: r(r % 4), s(s % 2)
	{
	}

	d4_t(const d4_t&) = default;

	d4_t &operator*=(const d4_t &other)
	{
		if (other.s == 0)
		{
			(r += other.r) %= 4;
			(s += other.s) %= 2;
		}
		else
		{
			(r = 4 - r + other.r) %= 4;
			(s += other.s) %= 2;
		}
		return *this;
	}

	d4_t operator*(const d4_t &other) const
	{
		return d4_t(*this) *= other;
	}

	d4_t inverse() const
	{
		return d4_t(s == 0 ? 4 - r : r, s);
	}

	d4_t &operator/=(const d4_t &other)
	{
		return *this *= other.inverse();
	}

	d4_t operator/(const d4_t &other) const
	{
		return d4_t(*this) /= other;
	}

	d4_t rotate(int _r = 1) const
	{
		return *this * d4_t(_r, 0);
	}

	d4_t reflect(int _s = 1) const
	{
		return *this * d4_t(0, _s);
	}

	static const d4_t zero;

	static const d4_t all_orientations[8];
	static const d4_t all_rotations[4];
	static const d4_t all_reflections[2];
};

const d4_t d4_t::zero(0, 0);

const d4_t d4_t::all_orientations[] = {
	d4_t(0, 0), d4_t(1, 0), d4_t(2, 0), d4_t(3, 0),
	d4_t(0, 1), d4_t(1, 1), d4_t(2, 1), d4_t(3, 1)
};

const d4_t d4_t::all_rotations[] = {
	d4_t(0, 0), d4_t(1, 0), d4_t(2, 0), d4_t(3, 0),
};

const d4_t d4_t::all_reflections[] = {
	d4_t(0, 0),
	d4_t(0, 1),
};