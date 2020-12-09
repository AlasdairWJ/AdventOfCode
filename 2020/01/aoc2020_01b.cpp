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
			for (int k = j + 1; k < entries.size(); k++)
				if (entries[i] + entries[j] + entries[k] == 2020)
				{
					printf("%d", entries[i] * entries[j] * entries[k]);
					return 0;
				}

	return 1;
}