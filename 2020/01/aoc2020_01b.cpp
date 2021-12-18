#include <iostream>
#include <set>

constexpr int target = 2020;

int main(int argc, const char* argv[])
{
	std::set<int> entries;

	int value;
	while (std::cin >> value)
		entries.insert(value);

	for (auto a = entries.begin(); a != entries.end(); ++a)
	{
		for (auto b = std::next(a); b != entries.end(); ++b)
		{
			const int sum = *a + *b;

			if (sum > target)
				continue;

			if (const auto c = entries.find(target - sum); c != entries.end())
			{
				std::cout << *a * *b * *c;
				break;
			}
		}
	}
	return 0;
}