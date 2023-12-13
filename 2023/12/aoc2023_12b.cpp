#include <iostream>
#include <string> // std::getline
#include <vector>
#include <map>
#include <charconv> // std::from_chars
#include <string_view>
#include <ranges> // std::views::split
#include <cstdint>

struct Arrangements
{
	Arrangements(const std::string_view source, const std::vector<int>& groups)
		: _source{ source }, _groups{ groups }
	{
	}

	int64_t operator()(std::size_t ix = 0, const std::size_t group_ix = 0)
	{
		if (group_ix == _groups.size())
			return _source.find('#', ix) == std::string_view::npos;

		int64_t total = 0;

		for (; ix < _source.size(); ix++) // min_length
		{
			if (_source[ix] != '.')
			{
				if (auto it = _map.find({ ix, group_ix }); it != _map.end())
				{
					total += it->second;
				}
				else
				{
					const std::size_t size = _groups[group_ix];

					const std::size_t required = or_end(_source.find_first_not_of('#', ix)) - ix;
					const std::size_t available = or_end(_source.find('.', ix)) - ix;
					const std::size_t next_ix = ix + size;

					if (required <= size && size <= available && (next_ix == _source.size() || _source[next_ix] != '#'))
					{
						const auto a = operator()(next_ix + (next_ix != _source.size()), group_ix + 1);
						total += a;

						_map[{ ix, group_ix }] = a;
					}
				}

				if (_source[ix] == '#')
				{
					break;
				}
			}
		}

		return total;
	}

private:
	std::size_t or_end(const std::size_t ix) const
	{
		return (ix != std::string_view::npos) ? ix : _source.size();
	}

	std::string_view _source;
	std::vector<int> _groups;
	std::map<std::pair<std::size_t, std::size_t>, int64_t> _map; // [{index, group index}] = count
}; 

int main(int _, const char*[])
{
	long long total = 0;

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

		std::string springs5x{ springs };
		std::vector<int> groups5x{ groups };

		for (int i = 1; i < 5; i++)
		{
			springs5x.push_back('?');
			springs5x.append(springs.begin(), springs.end());
			groups5x.insert(groups5x.end(), groups.begin(), groups.end());
		}

		total += Arrangements{ springs5x, groups5x }();
	}

	std::cout << total;
}