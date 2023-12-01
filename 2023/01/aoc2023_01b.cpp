#include <iostream>
#include <string> // std::getline
#include <string_view>
#include <algorithm>
#include <ranges>

constexpr char digits[]{ "0123456789" };
constexpr std::string_view digit_names[]{
	"",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

std::size_t first_index_of_sequence(const std::string_view source, const std::string_view sequence)
{
	const auto result = std::ranges::search(source, sequence);
	return std::distance(source.begin(), result.begin());
}

std::size_t last_index_of_sequence(const std::string_view source, const std::string_view sequence)
{
	if (sequence.size() > source.size())
		return 0;

	for (std::size_t i = source.size() - sequence.size() + 1; i > 0; i--)
	{
		if (source.substr(i - 1).starts_with(sequence))
			return i;
	}

	return 0;
}

int main(int _, const char*[])
{
	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::size_t first_indices[10]{};
		first_indices[0] = line.find_first_of(digits);

		for (int d = 1; d < 10; d++)
			first_indices[d] = first_index_of_sequence(line, digit_names[d]);

		const std::size_t first_digit_ix = std::distance(std::begin(first_indices), std::ranges::min_element(first_indices));

		const int first_digit = first_digit_ix == 0 ? int{ line[first_indices[0]] - '0' } : first_digit_ix;

		std::size_t last_indices[10]{};
		last_indices[0] = line.find_last_of(digits) + 1;

		for (int d = 1; d < 10; d++)
			last_indices[d] = last_index_of_sequence(line, digit_names[d]);

		const std::size_t last_digit_ix = std::distance(std::begin(last_indices), std::ranges::max_element(last_indices));

		const int last_digit = last_digit_ix == 0 ? int{ line[last_indices[0] - 1] - '0' } : last_digit_ix;

		total += 10 * first_digit + last_digit;
	}

	std::cout << total;
}