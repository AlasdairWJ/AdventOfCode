#include <iostream>
#include <string> // std::getline
#include <ranges> // std::views::split, std::views::enumerate
#include <vector>
#include <map>
#include <algorithm> // std::ranges::find
#include <charconv> // std::from_chars

int hash(const std::string_view s)
{
	int hash = 0;

	for (const char c : s)
	{
		hash += c;
		hash *= 17;
		hash %= 256;
	}

	return hash;
}

std::vector<std::string> boxes[256];

std::map<std::string, int> focal_lengths;

int main(int _, const char*[])
{
	std::string line;
	std::getline(std::cin, line);

	for (auto && r : line | std::views::split(','))
	{
		const std::string_view r_str{ r.begin(), r.end() };
		const std::size_t ix = r_str.find_first_of("-=");
		const std::string label = std::string{ r_str.substr(0, ix) };
		const char operation = r_str[ix];
		auto& box = boxes[hash(label)];

		auto it = std::ranges::find(box, label);

		if (operation == '-')
		{
			if (it != box.end())
			{
				box.erase(it);
			}
		}
		else if (operation == '=')
		{
			int focal_length;
			std::from_chars(r_str.data() + ix + 1, r_str.data() + r_str.size(), focal_length);

			focal_lengths[label] = focal_length;

			if (it != box.end())
			{
				*it = label;
			}
			else
			{
				box.push_back(label);
			}

		}
	}

	int total = 0;

	for (const auto& [box_id, box] : boxes | std::views::enumerate)
	{
		for (const auto& [slot, label] : box | std::views::enumerate)
		{
			total += (box_id + 1) * (slot + 1) *  focal_lengths[label];
		}
	}

	std::cout << total;
}