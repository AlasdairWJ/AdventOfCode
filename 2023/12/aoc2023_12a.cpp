#include <iostream>
#include <string> // std::getline
#include <vector>
#include <charconv> // std::from_chars
#include <string_view>
#include <ranges> // std::views::split

struct Arrangements
{
	Arrangements(const std::string_view source, const std::vector<int>& groups)
		: _source{ source }, _groups{ groups }
	{
	}

	int operator()(std::size_t ix = 0, const std::size_t group_ix = 0)
	{
		if (group_ix == _groups.size())
			return _source.find('#', ix) == std::string_view::npos;

		int total = 0;

		for (; ix < _source.size(); ix++) // min_length
		{
			if (_source[ix] != '.')
			{
				const std::size_t size = _groups[group_ix];

				const std::size_t required = or_end(_source.find_first_not_of('#', ix)) - ix;
				const std::size_t available = or_end(_source.find('.', ix)) - ix;
				const std::size_t next_ix = ix + size;

				if (required <= size && size <= available && (next_ix == _source.size() || _source[next_ix] != '#'))
				{
					total += operator()(next_ix + (next_ix != _source.size()), group_ix + 1);
				}
			}

			if (_source[ix] == '#')
				break;
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
};

int main(int _, const char*[])
{
	int total = 0;

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

		total += Arrangements{ springs, groups }();
	}

	std::cout << total;
}