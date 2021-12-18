#include <iostream>
#include <set>

constexpr int target = 2020;

int main(int argc, const char* argv[])
{
	std::set<int> entries;

	int value;
	while (std::cin >> value)
		entries.insert(value);

	for (const int a : entries)
	{
		if (const auto b = entries.find(target - a); b != entries.end())
		{
			std::cout << a * *b;
			break;
		}
	}

	return 0;
}