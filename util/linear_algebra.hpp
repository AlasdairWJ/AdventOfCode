#ifndef __UTIL_LINEAR_ALGEBRA_HPP
#define __UTIL_LINEAR_ALGEBRA_HPP

#include <type_traits>

namespace util
{

template <typename T>
bool solve(const T (&A)[2][2], const T (&x)[2], T (&y)[2])
{
	const T det = A[0][0] * A[1][1] - A[0][1] * A[1][0];

	if (det == T{})
		return false;

	y[0] = A[1][1] * x[0] - A[0][1] * x[1];
	y[1] = A[0][0] * x[1] - A[1][0] * x[0];

	if constexpr (std::is_integral_v<T>)
	{
		if (y[0] % det != 0 || y[1] % det != 0)
			return false;
	}

	y[0] /= det;
	y[1] /= det;

	return true;
}

} // util

#endif // __UTIL_LINEAR_ALGEBRA_HPP