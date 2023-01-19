#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> //std::vector
#include <stack> // std::stack
#include <regex> // std::regex, std::sregex_token_iterator
#include <set> // std::set

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

	if (left->type == token_e::list_start && right->type == token_e::number)
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
	const auto sort_packets = [](const auto& left, const auto& right)
	{
		return compare(left.begin(), right.begin()) > 0;
	};

	std::set<std::vector<token_t>, decltype(sort_packets)> all_packets;

	const auto packet2 = parse_tokens("[[2]]");
	all_packets.insert(packet2);

	const auto packet6 = parse_tokens("[[6]]");
	all_packets.insert(packet6);

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		all_packets.insert(parse_tokens(buffer));

		std::getline(std::cin, buffer);
		all_packets.insert(parse_tokens(buffer));

		// ignore nl
		std::getline(std::cin, buffer);
	}

	std::cout << (std::distance(all_packets.begin(), all_packets.find(packet2)) + 1) *
				 (std::distance(all_packets.begin(), all_packets.find(packet6)) + 1);

	return 0;
}
