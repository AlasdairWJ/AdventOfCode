#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <set>

struct rule_t
{
	int m_id;

	bool m_is_letter;
	char m_letter;

	int m_count[2];
	int m_values[2][2];
};

std::map<int, rule_t> rules_map;

bool parse_rule(const char* line, rule_t& rule)
{
	int n;
	sscanf_s(line, "%d: %n", &rule.m_id, &n);

	if (line[n] == '"')
	{
		rule.m_is_letter = true;
		rule.m_letter = line[n+1];
		return true;
	}

	int m = sscanf_s(line+n, "%d %d | %d %d",
					 &rule.m_values[0][0],
					 &rule.m_values[0][1],
					 &rule.m_values[1][0],
					 &rule.m_values[1][1]);

	if (m == 4)
	{
		rule.m_count[0] = 2;
		rule.m_count[1] = 2;
		return true;
	}

	if (m == 2)
	{
		rule.m_count[0] = 2;
		rule.m_count[1] = 0;
		return true;
	}

	m = sscanf_s(line+n, "%d | %d",
				 &rule.m_values[0][0],
				 &rule.m_values[1][0]);

	if (m == 2)
	{
		rule.m_count[0] = 1;
		rule.m_count[1] = 1;
		return true;
	}
	else if (m == 1)
	{
		rule.m_count[0] = 1;
		rule.m_count[1] = 0;
		return true;
	}

	return false;
}

// dear god this was not how i wanted this to go

bool matches_rule(const std::string& line, const int id, const int position, std::set<int>& final_positions)
{
	if (position >= line.size())
		return false;

	const rule_t& rule = rules_map.find(id)->second;

	if (rule.m_is_letter)
	{
		if (rule.m_letter != line[position])
			return false;

		final_positions.insert(position + 1);
		return true;
	}

	if (id == 8)
	{
		std::set<int> current_positions;
		matches_rule(line, 42, position, current_positions);

		while (!current_positions.empty())
		{
			final_positions.insert(current_positions.begin(), current_positions.end());

			std::set<int> next_positions;
			for (const int current_position : current_positions)
				matches_rule(line, 42, current_position, next_positions);
			current_positions.swap(next_positions);
		}

		return !final_positions.empty();
	}

	if (id == 11)
	{
		std::set<int> current_positions;
		matches_rule(line, 42, position, current_positions);

		int count = 1;

		while (!current_positions.empty())
		{
			auto reverse_positions = current_positions;
			for (int i = 0; i < count; i++)
			{
				std::set<int> next_positions;
				for (const int reverse_position : reverse_positions)
					matches_rule(line, 31, reverse_position, next_positions);
				reverse_positions.swap(next_positions);
			}

			final_positions.insert(reverse_positions.begin(), reverse_positions.end());

			std::set<int> next_positions;
			for (const int current_position : current_positions)
				matches_rule(line, 42, current_position, next_positions);
			current_positions.swap(next_positions);

			count++;
		}

		return !final_positions.empty();
	}

	for (int j = 0; j < 2; j++)
	{
		if (rule.m_count[j] == 0)
			continue;

		std::set<int> current_positions = { position };
		for (int i = 0; i < rule.m_count[j]; i++)
		{
			std::set<int> next_positions;
			for (const int current_position : current_positions)
				matches_rule(line, rule.m_values[j][i], current_position, next_positions);
			next_positions.swap(current_positions);
		}

		final_positions.insert(current_positions.begin(), current_positions.end());
	}

	return !final_positions.empty();
}

int main(int argc, const char* argv[])
{
	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		rule_t rule = {};
		parse_rule(line.c_str(), rule);

		rules_map.emplace(rule.m_id, rule);
	}

	int count = 0;
	while (std::getline(std::cin, line))
	{
		std::set<int> final_positions;
		if (matches_rule(line, 0, 0, final_positions))
			if (final_positions.find(line.size()) != final_positions.end())
				count++;
	}

	printf("%d", count);

	return 0;
}