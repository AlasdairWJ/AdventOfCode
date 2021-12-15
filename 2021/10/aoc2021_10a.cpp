#include <iostream>
#include <string>
#include <stack>

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
	case ')': return 3;
	case ']': return 57;
	case '}': return 1197;
	case '>': return 25137;
	default: return 0;
	}
}

int syntax_error_score(const std::string& line)
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
			return score(l);
		}
	}

	return 0;
}

int main(int argc, const char* argv[])
{
	int total = 0;

	std::string line;
	while (std::getline(std::cin, line))
		total += syntax_error_score(line);

	std::cout << total;

	return 0;
}