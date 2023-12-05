#include <iostream>
#include <string>
#include <string_view>
#include <algorithm> // std::ranges::min
#include <ranges> // std::views::split
#include <vector>
#include <cstdint>

#include "../../util/charconv.hpp" // util::from_chars 
#include "../../util/separate.hpp" // util::separate 

struct Range
{
	int64_t destination;
	int64_t source;
	int64_t length;

	bool contains(const int64_t value) const
	{
		return value >= source && value < source + length;
	}

	int64_t map(const int64_t value) const
	{
		return destination + (value - source);
	}
};

int main(int _, const char*[])
{
	std::string line;
	
	std::vector<int64_t> values;

	{
		std::getline(std::cin, line);

		const std::string_view initial_values_str = std::string_view{ line }.substr(7);

		for (auto && r : initial_values_str | std::views::split(' '))
			if (int64_t number; util::from_chars(r, number))
				values.push_back(number);
	}
	
	std::getline(std::cin, line); // skip

	for (std::string line; std::getline(std::cin, line); ) // "a-to-b map:"
	{
		std::vector<Range> ranges;

		while (std::getline(std::cin, line) && !line.empty())
		{
			const auto [dest_str, source_str, length_str] = util::separate<3>(line);

			int64_t dest, source, length;
			util::from_chars(dest_str, dest);
			util::from_chars(source_str, source);
			util::from_chars(length_str, length);

			ranges.emplace_back(dest, source, length);
		}

		for (int64_t& value : values)
		{
			for (const auto& range: ranges)
			{
				if (range.contains(value))
				{
					value = range.map(value);
					break;
				}
			}
		}
	}

	std::cout << std::ranges::min(values);
}