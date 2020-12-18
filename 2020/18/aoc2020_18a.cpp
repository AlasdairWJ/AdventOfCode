#include <cstdio>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <list>

struct token_t
{
	enum { PARENTHESES, NUMBER, OPERATOR } m_type;
	union { char m_symbol; __int64 m_value; };
};

bool tokenise(const std::string& line, std::list<token_t>& output)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (isspace(line[i]))
			continue;

		token_t token;	

		switch (line[i])
		{
		case '+':
		case '*':
			token.m_type = token_t::OPERATOR;
			token.m_symbol = line[i];
			break;

		case '(':
		case ')':
			token.m_type = token_t::PARENTHESES;
			token.m_symbol = line[i];
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			token.m_type = token_t::NUMBER;
			token.m_value = line[i] - '0';
			break;

		default:
			return false;
		}

		output.push_back(token);
	}

	return true;
}

bool simple_shunting_yard(std::list<token_t>& tokens, std::list<token_t>& output)
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
			while (!stack.empty() && stack.top().m_type == token_t::OPERATOR)
			{
				output.push_back(stack.top());
				stack.pop();
			}
			stack.push(token);
			break;

		case token_t::PARENTHESES:
			if (token.m_symbol == '(')
			{
				stack.push(token);
			}
			else // ')'
			{
				while (!stack.empty() && stack.top().m_type == token_t::OPERATOR)
				{
					output.push_back(stack.top());
					stack.pop();
				}

				if (!stack.empty() && stack.top().m_type == token_t::PARENTHESES && stack.top().m_symbol == '(')
				{
					stack.pop();
				}
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
		case token_t::PARENTHESES:
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
		simple_shunting_yard(tokens, postfix_tokens);

		const __int64 result = evaluate(postfix_tokens);

		sum += result;
	}

	printf("%lld", sum);

	return 0;
}