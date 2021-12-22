#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <variant>

enum TokenType { LEFT_PAREN, RIGHT_PAREN, NUMBER, OPERATOR };

using TokenValue = std::variant<char, __int64>;
using Token = std::pair<TokenType, TokenValue>;
using TokenList = std::vector<Token>;

bool tokenise(const std::string& line, TokenList& output)
{
	std::stringstream ss(line);

	bool expecting_value = true;
	while (ss.peek() != EOF)
	{
		if (expecting_value)
		{
			if (ss.peek() == '(')
			{
				ss.ignore(1);
				output.emplace_back(LEFT_PAREN, '(');
			}
			else
			{
				__int64 value;
				ss >> value;
				output.emplace_back(NUMBER, value);

				expecting_value = false;
			}

		}
		else
		{
			if (ss.peek() == ')')
			{
				ss.ignore(1);
				output.emplace_back(RIGHT_PAREN, ')');
			}
			else
			{
				ss.ignore(1);
				output.emplace_back(OPERATOR, static_cast<char>(ss.get()));
				ss.ignore(1);

				expecting_value = true;
			}
		}
	}

	return true;
}

bool shunting_yard(const TokenList& infix_tokens,
						  TokenList& postfix_tokens)
{
	std::stack<Token> stack;

	for (const auto& token : infix_tokens)
	{
		switch (token.first)
		{
		case NUMBER:
			postfix_tokens.push_back(token);
			break;

		case OPERATOR:
			while (!stack.empty() && stack.top().first == OPERATOR)
			{
				postfix_tokens.push_back(stack.top());
				stack.pop();
			}
			stack.push(token);
			break;

		case LEFT_PAREN:
			stack.push(token);
			break;

		case RIGHT_PAREN:
			while (!stack.empty() && stack.top().first == OPERATOR)
			{
				postfix_tokens.push_back(stack.top());
				stack.pop();
			}

			if (!stack.empty() && stack.top().first == LEFT_PAREN)
			{
				stack.pop();
			}
			break;
		}
	}

	while (!stack.empty())
	{
		postfix_tokens.push_back(stack.top());
		stack.pop();
	}

	return true;
}

void print_tokens(const TokenList& tokens)
{
	for (const auto& [op, value] : tokens)
	{
		switch (op)
		{
		case OPERATOR:
		case LEFT_PAREN:
		case RIGHT_PAREN:
			std::cout << std::get<char>(value);
			break;
		case NUMBER:
			std::cout << std::get<__int64>(value);
			break;
		default:
			break;
		}
		std::cout << ' ';
	}
	std::cout << '.' << std::endl;
}

__int64 operate(const char op_symbol, const __int64 a, const __int64 b)
{
	switch (op_symbol)
	{
	case '+': return a + b;
	case '*': return a * b;
	default: return 0;
	}
}

__int64 evaluate(TokenList postfix_tokens)
{
	for (auto it = postfix_tokens.begin(); it != postfix_tokens.end(); ++it)
	{
		if (it->first == OPERATOR)
		{
			const char op = std::get<char>(it->second);
			it--;
			const __int64 b = std::get<__int64>(it->second);
			it--;
			const __int64 a = std::get<__int64>(it->second);

			it = postfix_tokens.erase(it, it + 2);

			it->first = NUMBER;
			it->second = operate(op, a, b);
		}
	}

	return std::get<__int64>(postfix_tokens.front().second);
}

int main(int argc, const char* argv[])
{
	__int64 sum = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		TokenList infix_tokens;
		tokenise(line, infix_tokens);

		TokenList postfix_tokens;
		shunting_yard(infix_tokens, postfix_tokens);

		const __int64 result = evaluate(postfix_tokens);

		sum += result;
	}

	std::cout << sum;

	return 0;
}