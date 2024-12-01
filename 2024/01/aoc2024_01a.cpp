#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main(int _, const char*[])
{
	std::vector<int> left, right;

	for (int a, b; std::cin >> a >> b; )
	{
		left.push_back(a);
		right.push_back(b);
	}

	std::ranges::sort(left);
	std::ranges::sort(right);

	int total = 0;

	for (auto [a, b] : std::views::zip(left, right))
		total += std::abs(a - b);

	std::cout << total;
}