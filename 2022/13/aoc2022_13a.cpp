#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stack>

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

using iterator = std::vector<token_t>::const_iterator;

std::vector<token_t> parse_tokens(const std::string& text)
{
	std::vector<token_t> tokens;
	std::stack<int> ranges;

	int n = 0;
	for (const char* ptr = text.c_str(); *ptr != '\0'; n++)
	{
		if (isdigit(*ptr))
		{
			char* end;
			const int value = std::strtol(ptr, &end, 10);
			ptr = end;
			tokens.push_back({token_e::number, value, 1});
		}
		else if (*ptr == '[')
		{
			ranges.push(n);
			tokens.push_back({token_e::list_start, 0, 1});
			ptr++;
		}
		else if (*ptr == ']')
		{
			tokens[ranges.top()].range = n - ranges.top() + 1;
			ranges.pop();
			tokens.push_back({token_e::list_end, 0, 1});
			ptr++;
		}

		if (*ptr == ',')
			ptr++;
	}

	return tokens;	
}

void print_tokens(const std::vector<token_t>& tokens)
{
	token_e last = token_e::list_start;
	for (const auto& token : tokens)
	{
		switch (token.type)
		{
		case token_e::list_start:
			std::cout << '[';
			break;
		case token_e::list_end:
			std::cout << ']';
			break;
		case token_e::number:
			if (last == token_e::number)
				std::cout << ' ';
			std::cout << token.number;
			break;
		}
		last = token.type;
	}
	std::cout << '\n';
}

int compare(iterator left, iterator right)
{
	if (left->type == token_e::number &&
		right->type == token_e::number)
	{
		return compare(left->number, right->number);
	}
	
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
	
	if (left->type == token_e::number &&
		right->type == token_e::list_start)
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
	
	if (left->type == token_e::list_start &&
		right->type == token_e::list_start)
	{
		for (auto l2 = left + 1, r2 = right + 1;
			 l2->type != token_e::list_end || r2->type != token_e::list_end;
			 l2 += l2->range, r2 += r2->range)
		{
			if (l2->type == token_e::list_end)
			{
				return 1;
			}

			if (r2->type == token_e::list_end)
			{
				return -1;
			}

			const int result = compare(l2, r2);
			if (result != 0)
			{
				return result;
			}
		}

		return 0;
	}

	return 0; // ??
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
