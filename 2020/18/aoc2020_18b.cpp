#include <cstdio>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <list>

struct token_t
{
	enum { LEFT_PAREN, RIGHT_PAREN, NUMBER, OPERATOR } m_type;
	union { char m_symbol; __int64 m_value; };
};

bool tokenise(const std::string& line, std::list<token_t>& output)
{
	for (int i = 0; i < line.size();)
	{
		if (isspace(line[i]))
		{
			i++;
			continue;
		}

		token_t token;

		int numeric_value, n;
		if (sscanf_s(&line[i], "%d%n", &numeric_value, &n) == 1)
		{
			token.m_type = token_t::NUMBER;
			token.m_value = numeric_value;

			i += n;
		}
		else
		{
			switch (line[i])
			{
			case '+':
			case '*':
				token.m_type = token_t::OPERATOR;
				token.m_symbol = line[i++];
				break;

			case '(':
				token.m_type = token_t::LEFT_PAREN;
				token.m_symbol = line[i++];
				break;

			case ')':
				token.m_type = token_t::RIGHT_PAREN;
				token.m_symbol = line[i++];
				break;

			default:
				return false;
			}
		}

		output.push_back(token);
	}

	return true;
}

int precedence(const char op)
{
	switch (op)
	{
	case '+': return 2;
	case '*': return 1;
	default: return 0;
	}
}

bool shunting_yard(std::list<token_t>& tokens, std::list<token_t>& output)
{
	std::stack<token_t> stack;

	for (const auto& token : tokens)
	{
		switch (token.m_type)
		{
		case token_t::NUMBER:
			output.push_back(token);
			break;

		case token_t::OPERATOR:
			while (!stack.empty() && stack.top().m_type == token_t::OPERATOR && precedence(stack.top().m_symbol) >= precedence(token.m_symbol))
			{
				output.push_back(stack.top());
				stack.pop();
			}
			stack.push(token);
			break;

		case token_t::LEFT_PAREN:
			stack.push(token);
			break;

		case token_t::RIGHT_PAREN:
			while (!stack.empty() && stack.top().m_type == token_t::OPERATOR)
			{
				output.push_back(stack.top());
				stack.pop();
			}

			if (!stack.empty() && stack.top().m_type == token_t::LEFT_PAREN)
			{
				stack.pop();
			}
			break;
		}
	}

	while (!stack.empty())
	{
		output.push_back(stack.top());
		stack.pop();
	}

	return true;
}

void print_tokens(const std::list<token_t>& tokens)
{
	for (const auto& token : tokens)
	{
		switch (token.m_type)
		{
		case token_t::OPERATOR:
		case token_t::LEFT_PAREN:
		case token_t::RIGHT_PAREN:
			printf("%c ", token.m_symbol);
			break;
		case token_t::NUMBER:
			printf("%lld ", token.m_value);
			break;
		}
	}
	putchar('\n');
}

__int64 operate(const char op, const __int64 a, const __int64 b)
{
	switch (op)
	{
	case '+': return a + b;
	case '*': return a * b;
	}
	return 0;
}

__int64 evaluate(std::list<token_t> postfix_tokens)
{
	auto it = postfix_tokens.begin();
	while (it != postfix_tokens.end())
	{
		if (it->m_type == token_t::OPERATOR)
		{
			const char op = it->m_symbol;
			it--;
			const __int64 b = it->m_value;
			it--;
			const __int64 a = it->m_value;

			it = postfix_tokens.erase(it);
			it = postfix_tokens.erase(it);

			it->m_type = token_t::NUMBER;
			it->m_value = operate(op, a, b);
		}
		it++;
	}

	return postfix_tokens.front().m_value;
}

int main(int argc, const char* argv[])
{
	__int64 sum = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::list<token_t> tokens;
		tokenise(line, tokens);

		std::list<token_t> postfix_tokens;
		shunting_yard(tokens, postfix_tokens);

		const __int64 result = evaluate(postfix_tokens);

		sum += result;
	}

	printf("%lld", sum);

	return 0;
}