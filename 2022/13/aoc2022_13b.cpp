#include <iostream>
#include <string> // std::getline
#include <vector>
#include <regex> // std::sregex_token_iterator
#include <compare>
#include <set>

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
	const auto sort_packets = [](const TokenList& left, const TokenList& right)
	{
		return compare(left.begin(), right.begin()) < 0;
	};

	std::set<TokenList, decltype(sort_packets)> all_packets;

	for (std::string line; std::getline(std::cin, line); )
	{
		all_packets.insert(parse_tokens(line));

		std::getline(std::cin, line);
		all_packets.insert(parse_tokens(line));

		// ignore nl
		std::getline(std::cin, line);
	}

	const auto packet2 = parse_tokens("[[2]]");
	all_packets.insert(packet2);

	const auto packet6 = parse_tokens("[[6]]");
	all_packets.insert(packet6);

	const auto packet2_n = std::distance(all_packets.begin(), all_packets.find(packet2)) + 1;
	const auto packet6_n = std::distance(all_packets.begin(), all_packets.find(packet6)) + 1; // currently off by 1

	std::cout << packet2_n * packet6_n;
}
