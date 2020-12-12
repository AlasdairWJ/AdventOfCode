#include <cstdio>
#include <vector>
#include <queue>

int execute(std::vector<int> intcode, std::queue<int> input)
{
	int position = 0;
	while (position < intcode.size())
	{
		const int op_code = intcode[position] % 100;

		int modes[3];
		for (int i = 0, m = intcode[position] / 100; i < 3; i++, m /= 10)
			modes[i] = m % 10;

		if (op_code == 99)
			break;

		switch (op_code)
		{
		case 1:
		{
			const int a = modes[0] == 0 ? intcode[position + 1] : position + 1;
			const int b = modes[1] == 0 ? intcode[position + 2] : position + 2;
			const int c = intcode[position + 3];

			intcode[c] = intcode[a] + intcode[b];
			position += 4;
			break;
		}
		case 2:
		{
			const int a = modes[0] == 0 ? intcode[position + 1] : position + 1;
			const int b = modes[1] == 0 ? intcode[position + 2] : position + 2;
			const int c = intcode[position + 3];

			intcode[c] = intcode[a] * intcode[b];
			position += 4;
			break;
		}
		case 3:
		{
			const int a = intcode[position + 1];

			if (input.empty())
				return false;

			intcode[a] = input.front();
			input.pop();

			printf("input: %d\n", intcode[a]);

			position += 2;
			break;
		}
		case 4:
		{
			const int a = modes[0] == 0 ? intcode[position + 1] : position + 1;

			printf("output: %d\n", intcode[a]); 
			position += 2;
			break;
		}
		default:
			return false;
		}
	}

	return true;
}

int main(int argc, const char* argv[])
{
	std::vector<int> intcode;

	int value;
	while (scanf_s("%d,", &value) == 1)
		intcode.push_back(value);

	if (! execute(intcode, std::queue<int>({ 1 })))
		puts("failed to execute");

	return 0;
}