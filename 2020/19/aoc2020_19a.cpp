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

bool matches_rule(const std::string& line, const int rule_id, const int position, int& final_positions)
{
	if (position >= line.size())
		return false;

	const rule_t& rule = rules_map.find(rule_id)->second;

	if (rule.m_is_letter)
	{
		if (rule.m_letter != line[position])
			return false;

		final_positions = position + 1;
		return true;
	}

	for (int j = 0; j < 2; j++)
	{
		if (rule.m_count[j] == 0)
			continue;

		bool is_match = true;

		int current_position = position;
		for (int i = 0; i < rule.m_count[j]; i++)
			if (!matches_rule(line, rule.m_values[j][i], current_position, current_position))
			{
				is_match = false;
				break;
			}

		if (is_match)
		{
			final_positions = current_position;
			return true;
		}
	}

	return false;
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
		int final_position;
		if (matches_rule(line, 0, 0, final_position))
			if (final_position == line.size())
				count++;
	}

	printf("%d", count);

	return 0;
}