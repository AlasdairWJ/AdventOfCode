#include <cstdio>
#include <map>

#define N 2020

int main(int argc, char const *argv[])
{
	std::map<int, int> last_indices;

	int n = 0;

	int value;
	while (scanf_s("%d,", &value) == 1)
		last_indices[value] = n++;

	for (; n < N; n++)
	{
		auto it = last_indices.find(value);
		if (it == last_indices.end())
		{
			last_indices[value] = n - 1;
			value = 0;
		}
		else
		{
			value = n - it->second - 1;
			it->second = n - 1;
		}
	}
	
	printf("%d", value);

	return 0;
}