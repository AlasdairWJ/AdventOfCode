#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <map>

const std::string alpha = "abcdefg";

int to_digit(const std::string& letters)
{
	unsigned x = 0;
	for (const char letter : letters)
		x |= (1 << (letter - 'a'));

	switch (x)
	{
	case 0b1110111: return 0;
	case 0b0100100: return 1;
	case 0b1011101: return 2;
	case 0b1101101: return 3;
	case 0b0101110: return 4;
	case 0b1101011: return 5;
	case 0b1111011: return 6;
	case 0b0100101: return 7;
	case 0b1111111: return 8;
	case 0b1101111: return 9;
	default: return -1;
	}
}

int main(int argc, const char* argv[])
{
	int count = 0;

	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		std::stringstream ss(line);

		int maps_1, maps_4, maps_7;

		std::array<std::string, 10> letters;
		for (int i = 0; i < 10; i++)
		{
			ss >> letters[i];

			switch (letters[i].size())
			{
			case 2:
				maps_1 = i;
				break;
			case 3:
				maps_7 = i;
				break;
			case 4:
				maps_4 = i;
				break;
			default:
				break;
			}
		}

		std::map<char, char> remap;

		const char maps_to_a = letters[maps_7][letters[maps_7].find_first_not_of(letters[maps_1])];
		remap[maps_to_a] = 'a';

		char cf_candidate_1 = '\0', cf_candidate_2;

		for (const char l : letters[maps_7])
			if (l != maps_to_a)
				(cf_candidate_1 == '\0' ? cf_candidate_1 : cf_candidate_2) = l;

		char maps_to_c, maps_to_f;
		for (const auto& s : letters)
		{
			if (s.size() == 6)
			{
				if (s.find_first_of(cf_candidate_1) == std::string::npos)
				{
					remap[maps_to_c = cf_candidate_1] = 'c';
					remap[maps_to_f = cf_candidate_2] = 'f';
					break;
				}

				if (s.find_first_of(cf_candidate_2) == std::string::npos)
				{
					remap[maps_to_c = cf_candidate_2] = 'c';
					remap[maps_to_f = cf_candidate_1] = 'f';
					break;
				}
			}
		}

		char de_candidate_1 = '\0', de_candidate_2;
		for (const auto& s : letters)
		{
			if (s.size() == 6)
			{
				const char missing = alpha[alpha.find_first_not_of(s)];
				if (missing == maps_to_c)
					continue;

				(de_candidate_1 == '\0' ? de_candidate_1 : de_candidate_2) = missing;					 
			}
		}

		char maps_to_d;
		for (const auto& s : letters)
		{
			if (s.size() == 5)
			{
				if (s.find_first_of(de_candidate_1) == std::string::npos)
				{
					remap[maps_to_d = de_candidate_2] = 'd';
					remap[de_candidate_1] = 'e';
					break;
				}

				if (s.find_first_of(de_candidate_2) == std::string::npos)
				{
					remap[maps_to_d = de_candidate_1] = 'd';
					remap[de_candidate_2] = 'e';
					break;
				}
			}
		}

		for (const char l : letters[maps_4])
		{
			if (l != maps_to_c && l != maps_to_d && l != maps_to_f)
			{
				remap[l] = 'b';
				break;
			}
		}

		for (const char l : alpha)
		{
			if (remap.find(l) == remap.end())
			{
				remap[l] = 'g';
				break;
			}
		}

		std::string s;
		ss >> s; // ignore |

		int digits[4];
		for (int i = 0; i < 4; i++)
		{
			ss >> s;

			for (char& letter : s)
				letter = remap[letter];

			digits[i] = to_digit(s);
		}

		count += digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
	}

	std::cout << count;

	return 0;
}