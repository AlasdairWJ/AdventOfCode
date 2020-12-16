#include <cstdio>
#include <vector>
#include <utility>

struct range_t
{
	int m_lower, m_upper;

	bool operator()(const int x) const
	{
		return m_lower <= x && x <= m_upper;
	}
};

int main(int argc, const char* argv[])
{
	std::vector<std::pair<range_t, range_t>> valid_ranges;
	int num_fields = 0;

	char line[128];
	while (gets_s(line) && line[0] != '\0')
	{
		range_t ranges[2];
		sscanf_s(line, "%*[^:]: %d-%d or %d-%d",
			&ranges[0].m_lower, &ranges[0].m_upper,
			&ranges[1].m_lower, &ranges[1].m_upper);

		valid_ranges.emplace_back(ranges[0], ranges[1]);

		//printf("% 3d - % 3d,  ", ranges[0].m_lower, ranges[0].m_upper);
		//printf("% 3d - % 3d\n", ranges[1].m_lower, ranges[1].m_upper);

		num_fields++;
	}

	gets_s(line); // your ticket
	gets_s(line); // values
	gets_s(line); // space

	gets_s(line); // nearby tickets

	int error_sum = 0;
	bool first = true;

	while (gets_s(line) && line[0] != '\0')
	{
		int offset = 0, n;


		for (int i = 0; i < num_fields; i++)
		{
			bool is_valid = false;

			int value;
			sscanf_s(&line[offset], "%d%n", &value, &n);
			offset += n + 1;

			if (first)
				printf("%d, ", value);

			for (const auto& ranges : valid_ranges)
				if (ranges.first(value) || ranges.second(value))
				{
					is_valid = true;
					break;
				}

			if (!is_valid)
			{
				printf("%d is invalid\n", value);
				error_sum += value;
			}
		}

		first = false;
	}
	
	printf("\n\n%d", error_sum);

	return 0;
}