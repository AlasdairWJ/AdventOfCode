#include <iostream>
#include <string>
#include <string_view>
#include <algorithm> // std::ranges::min
#include <ranges> // std::views::split
#include <vector>
#include <cstdint>

#include "../../util/charconv.hpp" // util::from_chars 
#include "../../util/separate.hpp" // util::separate 

auto split(const auto& str)
{
	std::vector<int64_t> values;

	for (auto && r : str | std::views::split(' '))
		if (int64_t number; util::from_chars(r, number))
			values.push_back(number);

	return values;
}

struct ValueRange
{
	int64_t start;
	int64_t length;
	int64_t end() const { return start + length; }
};

struct Range
{
	int64_t destination;
	int64_t source;
	int64_t length;
	int64_t end() const { return source + length; }

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
	
	std::vector<ValueRange> value_ranges;

	{
		std::getline(std::cin, line);

		const auto values = split(std::string_view{ line }.substr(7));

		for (int ix = 0; ix < values.size(); ix += 2)
			value_ranges.emplace_back(values[ix], values[ix + 1]);
	}
	
	std::getline(std::cin, line); // skip

	while (std::getline(std::cin, line) && !line.empty()) // "a-to-b map:"
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

		std::vector<ValueRange> next_value_ranges;

		auto add_value_range = [&next_value_ranges, &ranges](auto self, const ValueRange& value_range)
		{
			for (const auto& range : ranges)
			{
				if (value_range.start >= range.source && value_range.end() <= range.end())
				{
					// values are entirely contained within range

					next_value_ranges.emplace_back(range.map(value_range.start), value_range.length);
					return;
				}
				else if (value_range.start < range.source && value_range.end() > range.end())
				{
					// range is entirely within values

					next_value_ranges.emplace_back(range.destination, range.length);
					self(self, ValueRange{ value_range.start, range.source - value_range.start });
					self(self, ValueRange{ range.end(), value_range.end() - range.end() });
					return;
				}
				else if (value_range.start < range.source && value_range.end() > range.source && value_range.end() <= range.end())
				{
					// overlaps start

					next_value_ranges.emplace_back(range.destination, value_range.end() - range.source);
					self(self, ValueRange{ value_range.start, range.source - value_range.start });
					return;
				}
				else if (value_range.start >= range.source && value_range.start < range.end() && value_range.end() > range.end())
				{
					// overlaps end

					next_value_ranges.emplace_back(range.map(value_range.start), range.end() - value_range.start);
					self(self, ValueRange{ range.end(), value_range.end() - range.end() });
					return;
				}
			}

			next_value_ranges.push_back(value_range);
		};

		for (const auto& value_range : value_ranges)
			add_value_range(add_value_range, value_range);

		value_ranges.swap(next_value_ranges);
	}

	std::cout << std::ranges::min(value_ranges | std::views::transform([](auto r) { return r.start; }));
}