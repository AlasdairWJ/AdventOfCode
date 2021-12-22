#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

struct RuleList
{
	int count() const { return m_count; }

	const auto* begin() const { return m_rules; }
	const auto* end() const { return m_rules + m_count; }

	void add(int rule_id)
	{
		m_rules[m_count++] = rule_id;
	}

private:
	int m_count;
	int m_rules[2];
};

struct Options
{
	Options() = default;

	const auto* begin() const { return m_options; }
	const auto* end() const { return m_options + m_count; }

	RuleList& add() { return m_options[m_count++]; }

private:
	int m_count;
	RuleList m_options[2];
};

struct Rule
{
	Rule() = default;

	bool is_letter() const { return m_is_letter; }

	bool is_letter_match(const char letter) const { return m_letter == letter; }

	void set_letter(const char letter)
	{
		m_letter = letter;
		m_is_letter = true;
	}

	Options& options() { return m_options; }
	const Options& options() const { return m_options; }

private:
	Options m_options;
	bool m_is_letter;
	char m_letter;
};

using iterator = std::string::iterator;
using Result = std::pair<bool, iterator>;

std::map<int, Rule> all_rules;

Result matches(const iterator& begin, const iterator& end, std::vector<int>& rules, int offset = 0)
{
	if (const bool a = offset == rules.size(); a || begin == end)
		return { a, begin };

	const int rule_id = rules[offset++];
	auto& rule = all_rules[rule_id];

	if (rule.is_letter())
	{
		return rule.is_letter_match(*begin) ?
			   matches(begin + 1, end, rules, offset) : 
			   std::make_pair(false, begin);
	}

	if (rule_id == 8)
	{
		Result result = { false, begin };
		while (result = matches(result.second, end, std::vector<int>{ 42 }), result.first)
		{
			const auto full_result = matches(result.second, end, rules, offset);
			if (full_result.first)
				return full_result;
		}

		return { false, begin };
	}

	if (rule_id == 11)
	{
		std::vector<int> new_rules_31;
		Result result = { false, begin };
		while (result = matches(result.second, end, std::vector<int>{ 42 }), result.first)
		{
			new_rules_31.push_back(31);
			Result full_result = matches(result.second, end, new_rules_31);
			if (full_result.first)
			{
				full_result = matches(full_result.second, end, rules, offset);
				if (full_result.first)
					return full_result;
			}
		}

		return { false, begin };
	}

	for (const auto& rule_list : rule.options())
	{
		rules.insert(rules.begin() + offset, rule_list.begin(), rule_list.end());

		const auto result = matches(begin, end, rules, offset);
		if (result.first)
			return result;

		const auto it = rules.begin() + offset;
		rules.erase(it, it + rule_list.count());
	}

	return { false, begin };
}

int main(int argc, const char* argv[])
{
	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		std::stringstream ss(line);

		int rule_id;
		ss >> rule_id;

		ss.ignore(2); // ": "

		Rule& rule = all_rules[rule_id]; // let this do the construction for us

		if (ss.peek() == '"')
		{
			ss.ignore(1); // '"'

			char letter;
			ss >> letter;
			rule.set_letter(letter);

			ss.ignore(1); // '"'
		}
		else
		{
			auto& options = rule.options();

			do
			{
				auto& sub_rules = options.add();

				int sub_rule_id;
				while (!ss.eof() && ss.peek() != '|')
				{
					ss >> sub_rule_id;
					sub_rules.add(sub_rule_id);

					ss.ignore(1); // ' '
				}
			}
			while (!ss.eof() && ss.ignore(1));
		}
	}

	int count = 0;
	while (std::getline(std::cin, line))
	{
		const auto [success, end] = matches(line.begin(), line.end(), std::vector<int>{ 0 });
		if (success && end == line.end())
			count++;
	}

	std::cout << count;

	return 0;
}