#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

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

bool matches_rule(const char* line, const int id, int& length)
{
	const rule_t& rule = rules_map.find(id)->second;

	if (rule.m_is_letter)
	{
		if (rule.m_letter != *line)
			return false;

		length = 1;
		return true;
	}

	bool matches_first_set = true;

	int new_length = 0;
	for (int i = 0; i < rule.m_count[0]; i++)
	{
		int match_length;
		if (!matches_rule(line + new_length, rule.m_values[0][i], match_length))
		{
			matches_first_set = false;
			break;
		}
		new_length += match_length;
	}

	if (matches_first_set)
	{
		length = new_length;
		return true;
	}

	if (!matches_first_set && rule.m_count[1] == 0)
		return false;

	new_length = 0;
	for (int i = 0; i < rule.m_count[1]; i++)
	{
		int match_length;
		if (!matches_rule(line + new_length, rule.m_values[1][i], match_length))
			return false;

		new_length += match_length;
	}

	length = new_length;
	return true;
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
		int length;
		if (matches_rule(line.c_str(), 0, length) && length == line.size())
			count++;
	}

	printf("%d", count);

	return 0;
}