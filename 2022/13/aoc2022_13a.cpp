#include <iostream>
#include <string> // std::getline
#include <vector>
#include <regex> // std::sregex_token_iterator
#include <compare>
#include <span>

#include "../../util/charconv.hpp" // util::from_chars

const std::regex tokens_re{ "\\[|\\]|\\d+" };

struct Token
{
	enum class Type { ListStart, ListEnd, Number } type;
	int number;
	int range;
};

using TokenList = std::vector<Token>;
using TokenIt = TokenList::const_iterator;

TokenList parse_tokens(const std::string& text)
{
	TokenList tokens;
	std::vector<int> ranges;

	const auto begin = std::sregex_token_iterator(text.begin(), text.end(), tokens_re);
	const auto end = std::sregex_token_iterator();

	int n = 0;
	for (auto it = begin; it != end; ++it, n++)
	{
		if (const auto token_str = it->str(); token_str == "[")
		{
			ranges.push_back(n);
			tokens.emplace_back(Token::Type::ListStart, 0, 1);
		}
		else if (token_str == "]")
		{
			tokens[ranges.back()].range = n - ranges.back() + 1;
			ranges.pop_back();

			tokens.emplace_back(Token::Type::ListEnd, 0, 1);
		}
		else
		{
			auto& token = tokens.emplace_back(Token::Type::Number, 0, 1);
			util::from_chars(token_str, token.number);
		}
	}

	return tokens;
}

using ordering = std::strong_ordering;

ordering compare(TokenIt left, TokenIt right)
{
	if (left->type == Token::Type::Number && right->type == Token::Type::Number)
		return left->number <=> right->number;

	if (left->type == Token::Type::ListStart && right->type == Token::Type::Number)
	{
		int nest_count = 0;

		do
		{
			++left;
			nest_count++;
		}
		while (left->type == Token::Type::ListStart);

		if (left->type == Token::Type::ListEnd)
			return ordering::less;

		if (const auto result = left->number <=> right->number; result != 0)
			return result;

		for (; nest_count > 0; nest_count--)
		{
			++left;

			if (left->type != Token::Type::ListEnd)
				return ordering::greater;
		}

		return ordering::equal;
	}

	if (left->type == Token::Type::Number && right->type == Token::Type::ListStart)
	{
		int nest_count = 0;

		do
		{
			++right;
			nest_count++;
		}
		while (right->type == Token::Type::ListStart);

		if (right->type == Token::Type::ListEnd)
			return ordering::greater;

		if (const auto result = left->number <=> right->number; result != 0)
			return result;

		for (; nest_count > 0; nest_count--)
		{
			++right;

			if (right->type != Token::Type::ListEnd)
				return ordering::less;
		}

		return ordering::equal;
	}

	if (left->type == Token::Type::ListStart && right->type == Token::Type::ListStart)
	{
		++left;
		++right;

		while (left->type != Token::Type::ListEnd || right->type != Token::Type::ListEnd)
		{
			if (left->type == Token::Type::ListEnd)
				return ordering::less;

			if (right->type == Token::Type::ListEnd)
				return ordering::greater;

			if (const auto result = compare(left, right); result != 0)
				return result;

			left += left->range, right += right->range;
		}
		
		return ordering::equal;
	}
	
	return ordering::equal; // should never reach
}

int main(int _, const char*[])
{
	int sum = 0;
	int index = 1;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto left = parse_tokens(line);

		std::getline(std::cin, line);
		const auto right = parse_tokens(line);

		if (compare(left.begin(), right.begin()) < 0)
			sum += index;

		index++;

		std::getline(std::cin, line);
	}

	std::cout << sum;
}