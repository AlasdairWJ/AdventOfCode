#include <iostream>
#include <set>
#include <algorithm> // std::ranges::find_if

constexpr int target = 2020;

int main(int _, const char*[])
{
	std::set<int> entries;

	for (int value; std::cin >> value; )
		entries.insert(value);

	for (auto it_a = entries.begin(); it_a != entries.end(); ++it_a)
	{
		auto it_c = std::find_if(std::next(it_a), entries.end(), [&](int b){ return entries.find(target - *it_a - b) != entries.end(); });
		if (it_c != entries.end())
		{
			std::cout << (*it_a) * (target - *it_a - *it_c) * (*it_c);
			break;
		}
	}
}