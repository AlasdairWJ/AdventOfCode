#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> //std::vector
#include <stack> // std::stack
#include <regex> // std::regex, std::sregex_token_iterator

int compare(const int a, const int b) { return (a < b) - (a > b); }

enum class token_e
{
	number,
	list_start,
	list_end
};

struct token_t
{
	token_e type;
	int number;
	int range;
};

std::vector<token_t> parse_tokens(const std::string& text)
{
	std::vector<token_t> tokens;
	std::stack<int> ranges;

	const std::regex tokens_pattern{ "\\[|\\]|\\d+" };

	const auto begin = std::sregex_token_iterator(text.begin(), text.end(), tokens_pattern);
	const auto end = std::sregex_token_iterator();

	int n = 0;
	for (auto it = begin; it != end; ++it, n++)
	{
		if (const std::string token = it->str(); token == "[")
		{
			ranges.push(n);
			tokens.push_back({ token_e::list_start, 0, 1 });
		}
		else if (token == "]")
		{
			tokens[ranges.top()].range = n - ranges.top() + 1;
			ranges.pop();
			tokens.push_back({ token_e::list_end, 0, 1 });
		}
		else
		{
			tokens.push_back({ token_e::number, std::stoi(token), 1 });
		}
	}

	return tokens;
}

using iterator = std::vector<token_t>::const_iterator;

int compare(iterator left, iterator right)
{
	if (left->type == token_e::number && right->type == token_e::number)
		return compare(left->number, right->number);

	if (left->type == token_e::list_start &&
		right->type == token_e::number)
	{
		do left++;
		while (left->type == token_e::list_start);

		if (left->type == token_e::list_end)
			return 1;

		const int result = compare(left->number, right->number);

		if (result != 0)
			return result;

		left++;

		return left->type == token_e::list_end ? 0 : -1;
	}

	if (left->type == token_e::number && right->type == token_e::list_start)
	{
		do right++;
		while (right->type == token_e::list_start);

		if (right->type == token_e::list_end)
			return -1;

		const int result = compare(left->number, right->number);

		if (result != 0)
			return result;

		right++;

		return right->type == token_e::list_end ? 0 : 1;
	}

	if (left->type == token_e::list_start && right->type == token_e::list_start)
	{
		for (auto l2 = left + 1, r2 = right + 1;
			l2->type != token_e::list_end || r2->type != token_e::list_end;
			l2 += l2->range, r2 += r2->range)
		{
			if (l2->type == token_e::list_end)
				return 1;

			if (r2->type == token_e::list_end)
				return -1;

			const int result = compare(l2, r2);
			if (result != 0)
				return result;
		}

		return 0;
	}

	throw "??";
}

int main(int argc, const char* argv[])
{
	int sum = 0;
	int index = 1;

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		const auto left = parse_tokens(buffer);
		std::getline(std::cin, buffer);
		const auto right = parse_tokens(buffer);

		const int result = compare(left.begin(), right.begin());

		if (result > 0)
			sum += index;

		index++;

		// ignore nl
		std::getline(std::cin, buffer);
	}

	std::cout << sum;

	return 0;
}