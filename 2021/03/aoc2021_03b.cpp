#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::count_if, std::remove_if, 

int parse(const std::string& binary)
{
	int total = 0;
	for (int i = binary.size() - 1, p = 1; i >= 0; i--, p <<= 1)
	{
		if (binary[i] == '1')
			total += p;
	}
	return total;
}

int main(int argc, const char* argv[])
{
	std::vector<std::string> oxygen_candidates;
	std::vector<std::string> co2_candidates;

	std::string binary;
	while (std::cin >> binary)
	{
		oxygen_candidates.push_back(binary);
		co2_candidates.push_back(binary);
	}

	const int size = binary.size();

	for (int i = 0; i < size; i++)
	{
		if (oxygen_candidates.size() > 1)
		{
			int tally = std::count_if(oxygen_candidates.begin(), oxygen_candidates.end(),
				[&](const auto& binary) { return binary[i] == '1'; });

			const char most_common_bit = (2 * tally >= oxygen_candidates.size()) ? '1' : '0';

			oxygen_candidates.erase(
				std::remove_if(
					oxygen_candidates.begin(), oxygen_candidates.end(),
					[&](const auto& binary) { return binary[i] != most_common_bit; }),
				oxygen_candidates.end());
		}

		if (co2_candidates.size() > 1)
		{
			int tally = std::count_if(co2_candidates.begin(), co2_candidates.end(),
				[&](const auto& binary) { return binary[i] == '1'; });

			const char least_common_bit = (2 * tally < co2_candidates.size()) ? '1' : '0';

			co2_candidates.erase(
				std::remove_if(co2_candidates.begin(), co2_candidates.end(),
					[&](const auto& binary) { return binary[i] != least_common_bit; }),
				co2_candidates.end());
		}
	}
	
	std::cout << parse(oxygen_candidates.front()) * parse(co2_candidates.front());

	return 0;
}