#include <iostream>
#include <vector>
#include <map>

int main(int _, const char*[])
{
	std::vector<int> left;
	std::map<int, int> right;

	for (int a, b; std::cin >> a >> b; )
	{
		left.push_back(a);
		right[b]++;
	}

	int total = 0;

	for (const int a : left)
	{
		if (const auto it = right.find(a); it != right.end())
			total += a * it->second;
	}

	std::cout << total;
}
