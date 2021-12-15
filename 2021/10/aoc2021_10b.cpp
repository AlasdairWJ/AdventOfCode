#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm> // std::sort

bool is_opening(const char paren)
{
	switch(paren)
	{
	case '(':
	case '[':
	case '{':
	case '<':
		return true;
	default:
		return false;
	}
}

char closing(const char paren)
{
	switch(paren)
	{
	case '(': return ')';
	case '[': return ']';
	case '{': return '}';
	case '<': return '>';
	default: return '\0';
	}
}

int score(const char paren)
{
	switch(paren)
	{
	case ')': return 1;
	case ']': return 2;
	case '}': return 3;
	case '>': return 4;
	default: return 0;
	}
}

__int64 autocomplete_score(const std::string& line)
{
	std::stack<char> parens;

	for (const char l : line)
	{
		if (is_opening(l))
		{
			parens.push(closing(l));
		}
		else if (l == parens.top())
		{
			parens.pop();
		}
		else
		{
			return 0;
		}
	}

	__int64 total = 0;
	while (!parens.empty())
	{
		(total *= 5) += score(parens.top());
		parens.pop();
	}

	return total;
}

int main(int argc, const char* argv[])
{
	std::vector<__int64> scores;

	std::string line;
	while (std::getline(std::cin, line))
	{
		const __int64 s = autocomplete_score(line);
		if (s != 0)
			scores.push_back(s);
	}

	std::sort(scores.begin(), scores.end());

	std::cout << scores[scores.size() / 2];

	return 0;
}