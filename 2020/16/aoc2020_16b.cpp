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
	
	gets_s(line);
	int my_ticket[N];
	read_ticket(line, my_ticket);

	gets_s(line); // skip empty line

	gets_s(line); // "nearby tickets:"

	bool all_options[N][N];
	for (auto& options : all_options)
		for (bool& b : options)
			b = true;

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
				break;
			}
		}

		if (!is_ticket_valid)
			continue;

		for (int field_pos = 0; field_pos < N; field_pos++)
		{
			const int& value = ticket[field_pos];
			for (int field_id = 0; field_id < N; field_id++)
			{
				const auto& ranges = valid_ranges[field_id];
				if (!ranges[0](value) && !ranges[1](value))
					all_options[field_id][field_pos] = false;
			}
		}
	}

	int option_count[N] = {};

	for (int field_pos = 0; field_pos < N; field_pos++)
		for (int field_id = 0; field_id < N; field_id++)
			if (all_options[field_id][field_pos])
				option_count[field_pos]++;

	int id_to_pos_map[N];

	for (int i = 0; i < N; i++)
	{
		int solved_pos = -1;
		for (int pos = 0; pos < N; pos++)
			if (option_count[pos] == 1)
			{
				solved_pos = pos;
				break;
			}

		int solved_id = -1;
		for (int id = 0; id < N; id++)
			if (all_options[id][solved_pos])
			{
				solved_id = id;
				break;
			}

		id_to_pos_map[solved_id] = solved_pos;

		for (int pos = 0; pos < N; pos++)
			if (all_options[solved_id][pos])
			{
				all_options[solved_id][pos] = false;
				option_count[pos]--;
			}
		
	}

	__int64 product = 1;
	for (int i = 0; i < 6; i++)
		product *= my_ticket[id_to_pos_map[i]];

	printf("%lld", product);

	return 0;

}