#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <set>

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

// this was not how i wanted this to go

bool matches_rule(const std::string& line, const int rule_id, const int position, std::set<int>& final_positions)
{
	if (position >= line.size())
		return false;

	const rule_t& rule = rules_map.find(rule_id)->second;

	if (rule.m_is_letter)
	{
		if (rule.m_letter != line[position])
			return false;

		final_positions.insert(position + 1);
		return true;
	}

	if (rule_id == 8)
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

	if (rule_id == 11)
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
		if (rule.m_options[j].m_subrule_count == 0)
			continue;

		std::set<int> current_positions = { position };
		for (int i = 0; i < rule.m_options[j].m_subrule_count; i++)
		{
			std::set<int> next_positions;
			for (const int current_position : current_positions)
				matches_rule(line, rule.m_options[j].m_subrules[i], current_position, next_positions);
			next_positions.swap(current_positions);
		}

		final_positions.insert(current_positions.begin(), current_positions.end());
	}

	return !final_positions.empty();
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
		std::set<int> final_positions;
		if (matches_rule(line, 0, 0, final_positions))
			if (final_positions.find(line.size()) != final_positions.end())
				count++;
	}

	printf("%d", count);

	return 0;
}