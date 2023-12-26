#ifndef __UTIL_NUMERIC_HPP
#define __UTIL_NUMERIC_HPP

#include "concepts.hpp"
#include <numeric> // std::gcd, std::accumulate
#include <cmath> // std::sqrt

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

template <typename T>
concept IntegerRange = std::ranges::range<T> && std::integral<std::ranges::range_value_t<T>>;

template <IntegerRange T>
auto gcd(const T& r)
{
	using U = std::ranges::range_value_t<T>;
	return std::accumulate(std::next(r.begin()), r.end(), *r.begin(), std::gcd<U, U>);
}

template <IntegerRange T>
auto lcm(const T& r)
{
	using U = std::ranges::range_value_t<T>;
	return std::accumulate(std::next(r.begin()), r.end(), *r.begin(), std::lcm<U, U>);
}


} // util

#endif // __UTIL_NUMERIC_HPP