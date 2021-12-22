#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct Range
{
	int lower, upper;

	bool operator()(const int x) const
	{
		return lower <= x && x <= upper;
	}
};

using RangePair = std::pair<Range, Range>;

void read_ticket(const std::string& line, std::vector<int>& ticket)
{
	std::stringstream ss(line);

	for (int& value : ticket)
	{
		ss >> value;
		ss.ignore(1);
	}
}

int main(int argc, const char* argv[])
{
	std::vector<RangePair> valid_ranges;
	
	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		RangePair ranges;
		sscanf_s(line.c_str(),
			"%*[^:]: %d-%d or %d-%d\n",
			&ranges.first.lower, &ranges.first.upper,
			&ranges.second.lower, &ranges.second.upper);

		valid_ranges.push_back(ranges);
	}

	const int num_fields = valid_ranges.size();

	std::getline(std::cin, line); // "your ticket:"
	std::getline(std::cin, line); // my ticket values
	std::getline(std::cin, line); // empty
	std::getline(std::cin, line); // "nearby tickets:"

	int error_rate = 0;

	int k = 0;
	while (std::getline(std::cin, line) && !line.empty())
	{
		std::vector<int> ticket(num_fields);
		read_ticket(line, ticket);

		bool is_ticket_valid = true;

		for (const int& field_value : ticket)
		{
			bool is_field_valid = false;

			for (const auto& ranges : valid_ranges)
				if (ranges.first(field_value) || ranges.second(field_value))
				{
					is_field_valid = true;
					break;
				}

			if (!is_field_valid)
			{
				is_ticket_valid = false;
				error_rate += field_value;
				break;
			}
		}
	}
	
	std::cout << error_rate;

	return 0;
}