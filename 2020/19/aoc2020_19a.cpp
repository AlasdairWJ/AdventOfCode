#include <cstdio>
#include <iostream>
#include <string>
#include <map>

struct rule_t
{
	int m_rule_id;

	bool m_is_letter;
	char m_letter;

	struct {
		int m_subrule_count;
		int m_subrules[2];
	} m_options[2];
};

std::map<int, rule_t> rules_map;

bool matches_rule(const std::string& line, const int rule_id, const int position, int& final_position)
{
	if (position >= line.size())
		return false;

	const rule_t& rule = rules_map.find(rule_id)->second;

	if (rule.m_is_letter)
	{
		if (rule.m_letter != line[position])
			return false;

		final_position = position + 1;
		return true;
	}

	for (int j = 0; j < 2; j++)
	{
		if (rule.m_options[j].m_subrule_count == 0)
			continue;

		bool is_match = true;

		int current_position = position;
		for (int i = 0; i < rule.m_options[j].m_subrule_count; i++)
			if (!matches_rule(line, rule.m_options[j].m_subrules[i], current_position, current_position))
			{
				is_match = false;
				break;
			}

		if (is_match)
		{
			final_position = current_position;
			return true;
		}
	}

	return false;
}

int read_list(const std::string& line, int& position, int* values)
{
	int i = 0, n;
	while (position < line.size() && sscanf_s(&line[position], "%d%n", &values[i], &n) == 1)
	{
		position += n + 1;
		i++;
	}
	return i;
}

int main(int argc, const char* argv[])
{
	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		int rule_id;

		int offset;
		sscanf_s(line.c_str(), "%d: %n", &rule_id, &offset);

		rule_t& rule = rules_map[rule_id]; // let this do the construction for us
		rule.m_rule_id = rule_id;

		if (line[offset] == '"')
		{
			rule.m_is_letter = true;
			rule.m_letter = line[offset+1];
		}
		else
		{
			rule.m_options[0].m_subrule_count = read_list(line, offset, rule.m_options[0].m_subrules);
			if (offset < line.size() && line[offset] == '|')
				rule.m_options[1].m_subrule_count = read_list(line, ++offset, rule.m_options[1].m_subrules);
		}
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