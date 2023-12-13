#include <iostream>
#include <string> // std::getline
#include <vector>
#include <charconv> // std::from_chars
#include <string_view>
#include <ranges> // std::views::split
#include <numeric> // std::accumulate
#include <span>

std::size_t or_end(const std::string_view& s, const std::size_t i)
{
	return (i != std::string_view::npos) ? i : s.size();
}

int arrangments(const std::string_view s, const std::span<int> groups, const int min_length)
{
	if (groups.empty())
		return (s.empty() || s.find('#') == std::string_view::npos) ? 1 : 0;

	int total = 0;

	for (std::size_t i = 0; i + min_length <= s.size(); i++)
	{
		if (s[i] != '.')
		{
			const std::size_t required = or_end(s, s.find_first_not_of('#', i)) - i;
			const std::size_t available = or_end(s, s.find('.', i)) - i;
			const std::size_t next_i = i + groups.front();

			if (required <= groups.front() && groups.front() <= available && (next_i == s.size() || s[next_i] != '#'))
			{
				total += arrangments(s.substr(next_i + (next_i != s.size())), groups.subspan(1), min_length - groups.front() - 1);
			}

			if (s[i] == '#')
				break;
		}
	}

	return total;
}

int main(int _, const char*[])
{
	int count = 0;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
	{
		const std::size_t index = line.find(' ');
		const auto springs = std::string_view{ line }.substr(0, index);
		const auto groups_str = std::string_view{ line }.substr(index + 1);

		std::vector<int> groups;

		for (auto && r : groups_str | std::views::split(','))
		{
			if (int group; std::from_chars(r.data(), r.data() + r.size(), group).ec == std::errc{})
				groups.push_back(group);
		}

		const int min_length = std::accumulate(groups.begin(), groups.end(), 0) + groups.size() - 1;

		count += arrangments(springs, groups, min_length);
	}

	std::cout << count;
}