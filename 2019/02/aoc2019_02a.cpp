#include <cstdio>
#include <vector>

int main(int argc, const char* argv[])
{
	std::vector<int> intcode;

	int value;
	while (scanf_s("%d,", &value) == 1)
		intcode.push_back(value);

	intcode[1] = 12;
	intcode[2] = 2;

	int position = 0;
	while (position < intcode.size())
	{
		const int op_code = intcode[position];

		if (op_code == 99)
			break;

		const int a = intcode[position + 1];
		const int b = intcode[position + 2];
		const int dst = intcode[position + 3];

		if (op_code == 1)
		{
			intcode[dst] = intcode[a] + intcode[b];
		}
		else if (op_code == 2)
		{
			intcode[dst] = intcode[a] * intcode[b];
		}
		else
		{
			// invalid op
		}

		position += 4;
	}

	printf("%d", intcode[0]);

	return 0;
}