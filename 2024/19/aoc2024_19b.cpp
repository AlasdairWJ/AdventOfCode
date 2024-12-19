#include <iostream>
#include <string>
#include <string_view>
#include <set>
#include <map>
#include <ranges>

long long formation_count(const std::string_view towel, const auto& towels)
{
	std::map<std::string_view, long long> current;
	current.emplace(towel, 1);

	long long solutions = 0;

	while (!current.empty())
	{
		decltype(current) next;

		for (const auto [str, count] : current)
		{
			const auto begin = towels.lower_bound(str.substr(0, 1));
			const auto end = towels.upper_bound(str);

			for (auto it = begin; it != end; ++it)
			{
				if (str.starts_with(*it))
				{
					const auto next_str = str.substr(it->size());

					if (next_str.empty())
					{
						solutions += count;
					}
					else
					{
						next[next_str] += count;
					}
				}
			}
		}

		current.swap(next);
	}

	return solutions;
}

const std::string Delim = ", ";

int main(int _, const char*[])
{
	std::string towels_str;
	std::getline(std::cin, towels_str);

	std::set<std::string_view> towels;

	for (auto && r : towels_str | std::views::split(Delim))
		towels.emplace(r.begin(), r.end());

	std::string towel;
	std::getline(std::cin, towel); // skip

	long long count = 0;

	while (std::getline(std::cin, towel))
		count += formation_count(towel, towels);

	std::cout << count;
}
