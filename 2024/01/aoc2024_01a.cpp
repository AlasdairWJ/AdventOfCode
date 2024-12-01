#include <iostream>
#include <vector>
#include <algorithm>

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

	for (int n = 0; n < left.size(); n++)
		total += std::abs(left[n] - right[n]);

	std::cout << total;
}