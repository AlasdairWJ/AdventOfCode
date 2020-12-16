#include <cstdio>

#define N 20

struct range_t
{
	int m_lower, m_upper;

	bool operator()(const int x) const
	{
		return m_lower <= x && x <= m_upper;
	}
};

void read_ticket(const char* line, int (&ticket)[N])
{
	int offset = 0, n;
	for (int i = 0; i < N; i++)
	{
		sscanf_s(line + offset, "%d%n", &ticket[i], &n);
		offset += n + 1;
	}
}

int main(int argc, const char* argv[])
{
	range_t valid_ranges[N][2];
	for (int i = 0; i < N; i++)
	{
		scanf_s("%*[^:]: %d-%d or %d-%d\n",
			&valid_ranges[i][0].m_lower, &valid_ranges[i][0].m_upper,
			&valid_ranges[i][1].m_lower, &valid_ranges[i][1].m_upper);
	}

	char line[128];
	gets_s(line); // "your ticket:"
	gets_s(line); // my ticket values
	gets_s(line); // empty
	gets_s(line); // "nearby tickets:"

	int error_rate = 0;

	while (gets_s(line) && line[0] != '\0')
	{
		int ticket[N];
		read_ticket(line, ticket);

		bool is_ticket_valid = true;

		for (const int& field_value : ticket)
		{
			bool is_field_valid = false;

			for (const auto& ranges : valid_ranges)
				if (ranges[0](field_value) || ranges[1](field_value))
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
	
	printf("%d", error_rate);

	return 0;
}