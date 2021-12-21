#include <iostream>
#include <map>

constexpr int N = 30'000'000;

int main(int argc, const char* argv[])
{
	std::map<int, int> last_indices;

	int n = 0, value;
	do
	{
		std::cin >> value;
		last_indices[value] = n++;
	}
	while (std::cin.get() == ',');

	for (; n < N; n++)
	{
		const auto it = last_indices.find(value);
		if (it == last_indices.end())
		{
			last_indices.emplace(value, n - 1);
			value = 0;
		}
		else
		{
			value = n - it->second - 1;
			it->second = n - 1;
		}
	}
	
	std::cout << value;

	return 0;
}