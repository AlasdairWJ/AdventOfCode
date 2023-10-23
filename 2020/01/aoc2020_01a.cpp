#include <iostream>
#include <set>
#include <algorithm> // std::ranges::find_if

constexpr int target = 2020;

int main(int _, const char*[])
{
	std::set<int> entries;

	for (int value; std::cin >> value; )
		entries.insert(value);

	const int a = *std::ranges::find_if(entries, [&](int x){ return entries.find(target - x) != entries.end(); });
	std::cout << a * (target - a);
}