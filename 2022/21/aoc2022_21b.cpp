#include <iostream>
#include <string>
#include <map>
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

// returns required rhs
std::pair<__int64, bool> calculate_right_operand(const __int64 result, const __int64 a, const char op)
{
	switch (op)
	{
	case '+': return { result - a, true }; // a + b == result, b = result - a
	case '-': return { a - result, true }; // a - b == result, b = a - result
	case '*': return (a != 0) ? std::make_pair(result / a, result % a == 0) : std::make_pair(0ll, false); // a * b == result, b = result / a
	case '/': return (result != 0) ? std::make_pair(a / result, a % result == 0) : std::make_pair(0ll, false); // a / b == result, b = a / result
	default: return { 0, false };
	}
}

// returns required lhs
std::pair<__int64, bool> calculate_left_operand(const __int64 result, const char op, const __int64 b)
{
	switch (op)
	{
	case '+': return { result - b, true }; // a + b == result, a = result - b
	case '-': return { result + b, true }; // a - b == result, a = result + b
	case '*': return (b != 0) ? std::make_pair(result / b, result % b == 0) : std::make_pair(0ll, false); // a * b == result, a = result / b
	case '/': return { result * b, true }; // a / b == result, a = result * b
	default: return { 0, false };
	}
}

std::map<std::string, __int64> values;
std::map<std::string, std::tuple<std::string, char, std::string>> operations;

bool set_value(const std::string& id, const __int64 value)
{
	if (const auto it = operations.find(id); it != operations.end())
	{
		const auto& [lhs, op, rhs] = it->second;

		const auto a_it = values.find(lhs), b_it = values.find(rhs);

		if (a_it == values.end() && b_it != values.end())
		{
			auto [a, ok]  = calculate_left_operand(value, op, b_it->second);
			if (ok) ok = set_value(lhs, a);
			return ok;
		}
		
		if (a_it != values.end() && b_it == values.end())
		{
			auto [b, ok] = calculate_right_operand(value, a_it->second, op);
			if (ok) ok = set_value(rhs, b);
			return ok;
		}

		return false;
	}

	values[id] = value;
	return true;
}

int main(const int argc, const char* argv[])
{
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
				operations.emplace(id, std::make_tuple(lhs, op, rhs));
			}
		}
	}

	values.erase("humn");

	// solve everything there is to solve that isn't dependent on the input
	for (bool changes = true; changes;)
	{
		changes = false;
		for (auto it = operations.begin(); it != operations.end(); )
		{
			const auto& id = it->first;
			const auto& [lhs, op, rhs] = it->second;

			const auto lhs_it = values.find(lhs), rhs_it = values.find(rhs);

			if (lhs_it != values.end() && rhs_it != values.end())
			{
				const __int64 a = lhs_it->second, b = rhs_it->second;
				const __int64 result = operate(a, op, b);
				values.emplace(id, result);
				changes = true;

				it = operations.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	{
		const auto it = operations.find("root");
		const auto& [lhs, op, rhs] = it->second;

		const auto a_it = values.find(lhs), b_it = values.find(rhs);

		bool ok = false;

		if (a_it == values.end() && b_it != values.end())
			ok = set_value(lhs, b_it->second);
		else if (a_it != values.end() && b_it == values.end())
			ok = set_value(rhs, a_it->second);

		if (!ok)
			return 1;
	}
	
	const auto it = values.find("humn");
	
	if (it == values.end())
		return 1;
	
	std::cout << it->second;

	return 0;
}