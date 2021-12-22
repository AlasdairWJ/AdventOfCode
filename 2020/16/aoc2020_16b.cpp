#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template <typename T> T& clrb(T& mask, const int bit) { return mask &= ~(T(1) << bit); }
template <typename T> T& setb(T& mask, const int bit) { return mask |= T(1) << bit; }
template <typename T> bool hasb(T& mask, const int bit) { return (mask & (T(1) << bit)) != 0; }

int fsb(const unsigned x)
{
	int c = 0;
	unsigned b = 1;
	while ((x & b) == 0)
	{
		c++;
		b <<= 1;
	}
	return c;
}

bool is_power_of_2(const unsigned x) { return (x != 0) && (x & (x - 1)) == 0; }

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

	std::vector<int> my_ticket(num_fields);
	read_ticket(line, my_ticket);

	std::getline(std::cin, line); // skip empty line
	std::getline(std::cin, line); // "nearby tickets:"

	std::vector<unsigned> options(num_fields, (1u << num_fields) - 1);

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
				break;
			}
		}

		if (!is_ticket_valid)
			continue;

		for (int field_pos = 0; field_pos < num_fields; field_pos++)
		{
			const int& value = ticket[field_pos];
			for (int field_id = 0; field_id < num_fields; field_id++)
			{
				const auto& ranges = valid_ranges[field_id];
				if (!ranges.first(value) && !ranges.second(value))
					clrb(options[field_pos], field_id);
			}
		}
	}

	std::vector<int> id_to_pos_map(num_fields);
	for (int i = 0; i < num_fields; i++)
	{
		int solved_pos;
		for (int field_pos = 0; field_pos < num_fields; field_pos++)
			if (is_power_of_2(options[field_pos]))
			{
				solved_pos = field_pos;
				break;
			}

		const int solved_id = fsb(options[solved_pos]);

		id_to_pos_map[solved_id] = solved_pos;

		for (int pos = 0; pos < num_fields; pos++)
			clrb(options[pos], solved_id);
	}

	__int64 product = 1;
	for (int i = 0; i < 6; i++)
		product *= my_ticket[id_to_pos_map[i]];

	std::cout << product;

	return 0;
}