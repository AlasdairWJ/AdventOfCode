#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

enum TokenType { LEFT_PAREN, RIGHT_PAREN, VALUE };
using Token = std::pair<TokenType, int>;
using TokenList = std::vector<Token>;

bool is_value(const Token& token) { return token.first == VALUE; }

bool explode(TokenList& tokens)
{
	int depth = 0;
	auto prev_number_it = tokens.end();
	for (auto it = tokens.begin(); it != tokens.end(); ++it)
	{
		switch (it->first)
		{
		case LEFT_PAREN:
			depth++;
			break;

		case RIGHT_PAREN:
			depth--;
			break;

		case VALUE:
			if (depth > 4)
			{
				const auto left_paren_it = it - 1;

				if (prev_number_it != tokens.end())
					prev_number_it->second += it->second;

				const auto other_number_it = it + 1;
				
				const auto right_paren_it = other_number_it + 1;

				const auto next_number_it = std::find_if(right_paren_it + 1, tokens.end(), is_value);

				if (next_number_it != tokens.end())
					next_number_it->second += other_number_it->second;

				it = tokens.erase(left_paren_it, right_paren_it + 1);

				it = tokens.emplace(it, VALUE, 0);

				return true;
			}

			prev_number_it = it;
			break;

		default:
			break;
		}
	}

	return false;
}

bool split(TokenList& tokens)
{
	for (auto it = tokens.begin(); it != tokens.end(); ++it)
	{
		if (it->first == VALUE)
		{
			const int value = it->second;
			if (value >= 10)
			{
				const int a = value / 2;
				const int b = value - a;

				it = tokens.erase(it);

				const Token new_tokens[] 
				{
					Token(LEFT_PAREN, 0),
					Token(VALUE, a),
					Token(VALUE, b),
					Token(RIGHT_PAREN, 0),
				};
				
				it = tokens.insert(it, std::begin(new_tokens), std::end(new_tokens));

				return true;
			}
		}
	}

	return false;
}

auto& reduce(TokenList& tokens)
{
	while (explode(tokens) || split(tokens));
	return tokens;
}

auto read(const std::string& line)
{
	TokenList tokens;

	std::stringstream ss(line);

	char peek;
	while (peek = ss.peek(), !ss.eof())
	{
		switch (peek)
		{
		case '[':
			tokens.emplace_back(LEFT_PAREN, 0);
			ss.ignore(1);
			break;

		case ']':
			tokens.emplace_back(RIGHT_PAREN, 0);
			ss.ignore(1);
			break;

		case ',':
			ss.ignore(1);
			break;

		default:
			int value;
			ss >> value;
			tokens.emplace_back(VALUE, value);
			break;
		}
	}

	return tokens;
}

auto& add(TokenList& sum_tokens, const TokenList& tokens)
{
	sum_tokens.emplace(sum_tokens.begin(), LEFT_PAREN, 0);
	sum_tokens.insert(sum_tokens.end(), tokens.begin(), tokens.end());
	sum_tokens.emplace(sum_tokens.end(), RIGHT_PAREN, 0);
	return reduce(sum_tokens);
}

int magnitude(TokenList tokens)
{
	for (auto it = tokens.begin(); it != tokens.end(); ++it)
	{
		if (it->first == RIGHT_PAREN)
		{
			const auto b_it = it - 1;
			const auto a_it = it - 2;
			const auto left_paren_it = it - 3;

			it->first = VALUE;
			it->second = 3 * a_it->second + 2 * b_it->second;

			it = tokens.erase(left_paren_it, it);
		}
	}

	return tokens.front().second;
}

int main(int argc, const char* argv[])
{
	std::string line;
	std::getline(std::cin, line);
	
	auto sum_tokens = read(line);
	while (std::getline(std::cin, line))
		add(sum_tokens, read(line));

	std::cout << magnitude(sum_tokens);

	return 0;
}