#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include <regex>

__int64 operate(const __int64 a, const char op, const __int64 b)
{
	switch (op)
	{
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	default: return 0;
	}
}

int main(const int argc, const char* argv[])
{
	std::map<std::string, __int64> values;
	std::vector<std::tuple<std::string, std::string, char, std::string>> operations;

	std::string line;
	while (std::getline(std::cin, line))
	{
		static const std::regex roles_pattern{ "^(\\w+)\\: (?:(\\d+)|(\\w+) (.) (\\w+))" };

		std::smatch match;
		if (std::regex_match(line, match, roles_pattern))
		{
			const auto id = match.str(1);

			if (match.length(2) != 0)
			{
				const __int64 value = std::stoll(match.str(2));
				values.emplace(id, value);
			}
			else
			{
				const auto lhs = match.str(3);
				const char op = match.str(4).front();
				const auto rhs = match.str(5);
				operations.emplace_back(id, lhs, op, rhs);
			}
		}
	}

	while (!operations.empty())
	{
		for (auto it = operations.begin(); it != operations.end(); )
		{
			const auto [id, lhs, op, rhs] = *it;

			const auto lhs_it = values.find(lhs), rhs_it = values.find(rhs);

			if (lhs_it != values.end() && rhs_it != values.end())
			{
				const __int64 a = lhs_it->second, b = rhs_it->second;
				const __int64 result = operate(a, op, b);
				values.emplace(id, result);

				it = operations.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	
	const auto it = values.find("root");
	
	if (it == values.end())
		return 1;
	
	std::cout << it->second;

	return 0;
}