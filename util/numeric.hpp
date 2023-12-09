#ifndef __UTIL_NUMERIC_HPP
#define __UTIL_NUMERIC_HPP

#include "concepts.hpp"
#include <numeric>

namespace util
{

template <Number T>
int sign(const T& val) { return (T{} < val) - (val < T{}); }

template <Number T>
bool solve_quadratic(const T a, const T b, const T c, T& x1, T& x2)
{
	const T discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return false;

	const T sqrt_discriminant = std::sqrt(discriminant);
	x1 = (-b - sqrt_discriminant) / (2 * a);
	x2 = (-b + sqrt_discriminant) / (2 * a);
	return true;
}

template <std::integral T>
constexpr T lcm(const T a, const T b)
{
	return a * b / std::gcd(a, b);
}


} // util

#endif // __UTIL_NUMERIC_HPP