#include <cstdio>
#include <vector>

int main(int argc, const char* argv[])
{
	std::vector<int> entries;

	int value;
	while (scanf_s("%d", &value) == 1)
		entries.push_back(value);

	for (int i = 0; i < entries.size(); i++)
		for (int j = i + 1; j < entries.size(); j++)
			if (entries[i] + entries[j] == 2020)
			{
				printf("%d", entries[i] * entries[j]);
				return 0;
			}

	return 1;
}