#include <iostream>
#include <string> // std::getline
#include <string_view>
#include <algorithm> // std::begin, std::distance, std::ranges::min_element, std::ranges::max_element

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

std::size_t first_index_of(const std::string_view source, const std::string_view sequence)
{
	const std::size_t ix = source.find(sequence);
	return ix != std::string::npos ? ix : source.size();
}

std::size_t last_index_of(const std::string_view source, const std::string_view sequence)
{
	const std::size_t ix = source.rfind(sequence);
	return ix != std::string::npos ? ix + 1 : 0;
}

int main(int _, const char*[])
{
	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::size_t first_indices[10]{};
		first_indices[0] = line.find_first_of(digits);

		for (int d = 1; d < 10; d++)
			first_indices[d] = first_index_of(line, digit_names[d]);

		const std::size_t first_digit_ix = std::distance(std::begin(first_indices), std::ranges::min_element(first_indices));

		const int first_digit = first_digit_ix == 0 ? int{ line[first_indices[0]] - '0' } : first_digit_ix;

		std::size_t last_indices[10]{};
		last_indices[0] = line.find_last_of(digits) + 1;

		for (int d = 1; d < 10; d++)
			last_indices[d] = last_index_of(line, digit_names[d]);

		const std::size_t last_digit_ix = std::distance(std::begin(last_indices), std::ranges::max_element(last_indices));

		const int last_digit = last_digit_ix == 0 ? int{ line[last_indices[0] - 1] - '0' } : last_digit_ix;

		total += 10 * first_digit + last_digit;
	}

	std::cout << total;
}