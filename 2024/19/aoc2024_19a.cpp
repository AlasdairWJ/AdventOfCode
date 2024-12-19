#include <iostream>
#include <string>
#include <string_view>
#include <set>
#include <ranges>

const std::string Delim = ", ";

bool can_form(const std::string_view towel, const auto& towels)
{
	std::set<std::string_view> current;
	current.emplace(towel);

	while (!current.empty())
	{
		decltype(current) next;

		for (const auto str : current)
		{
			std::string_view lower = str.substr(0, 1);

			const auto begin = towels.lower_bound(lower);
			const auto end = towels.upper_bound(str);

			for (auto it = begin; it != end; ++it)
			{
				if (str.starts_with(*it))
				{
					const auto next_str = str.substr(it->size());

					if (next_str.empty())
						return true;

					next.insert(next_str);
				}
			}
		}

		current.swap(next);
	}

	return false;
}

int main(int _, const char*[])
{
	std::string towels_str;
	std::getline(std::cin, towels_str);

	std::set<std::string_view> towels;

	for (auto && r : towels_str | std::views::split(Delim))
		towels.emplace(r.begin(), r.end());

	std::string towel;
	std::getline(std::cin, towel); // skip

	int count = 0;

	while (std::getline(std::cin, towel))
		count += can_form(towel, towels);

	std::cout << count;
}
