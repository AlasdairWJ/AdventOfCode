#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <ranges>

#include "../../util/separate.hpp"
#include "../util/charconv.hpp"

bool are_valid_pages(const auto& pages, const auto& dependencies)
{
	for (auto it = pages.begin(); it != pages.end(); ++it)
	{
		if (auto dep_it = dependencies.find(*it); dep_it != dependencies.end())
		{
			for (const int dependent_page : dep_it->second)
			{
				if (auto other_it = std::find(it + 1, pages.end(), dependent_page); other_it != pages.end())
				{
					return false;
				}
			}
		}
	}

	return true;
}

int main(int _, const char*[])
{
	std::map<int, std::set<int>> dependencies;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
	{
		const auto [left_str, right_str] = util::separate(line, "|");
		
		const int left = util::from_chars(left_str);
		const int right = util::from_chars(right_str);

		dependencies[right].insert(left);
	}

	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto pages = line 
			| std::views::split(',')
			| std::views::transform(util::from_chars_t{})
			| std::ranges::to<std::vector>();

		if (are_valid_pages(pages, dependencies))
			total += pages[pages.size() / 2];
	}

	std::cout << total;
}