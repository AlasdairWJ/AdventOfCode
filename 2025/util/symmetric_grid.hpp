#ifndef __UTIL_SYMMETRIC_GRID_HPP
#define __UTIL_SYMMETRIC_GRID_HPP

#include <memory>

namespace util
{

template <typename T>
constexpr T tri(const T x) { return (x * (x + 1)) / 2; }

template <typename T, bool Exclusive = false>
struct symmetric_grid
{
	using value_type = T;

	std::size_t size() const noexcept
	{
		return _size;
	}

	std::size_t count() const noexcept
	{
		return _count;
	}

	bool is_exclusive() const noexcept
	{
		return Exclusive;
	}

	symmetric_grid(const std::size_t size)
	{
		_size = size;
		_count = tri(size - Exclusive);
		_data = std::make_unique<T[]>(_count);
	}

	T& operator[](const size_t i, const size_t j)
	{
		return _data[_index(i, j)];
	}

	const T& operator[](const size_t i, const size_t j) const
	{
		return _data[_index(i, j)];
	}

	T* begin() { return _data.get(); }
	T* end() { return _data.get() + _count; }

	const T* begin() const { return _data.get(); }
	const T* end() const { return _data.get() + _count; }

	const T* cbegin() const { return _data.get(); }
	const T* cend() const { return _data.get() + _count; }

	T* data() { return _data.get(); }
	const T* data() const { return _data.get(); }

private:
	static constexpr std::size_t _index(const std::size_t i, const std::size_t j)
	{
		return (i < j) ? (tri(j - Exclusive) + i) : (tri(i - Exclusive) + j);
	}

	std::size_t _size;
	std::size_t _count;
	std::unique_ptr<T[]> _data;
};

}

#endif __UTIL_SYMMETRIC_GRID_HPP
