#include <cstdio>
#include <vector>

int execute(std::vector<int> intcode, int noun, int verb)
{
	intcode[1] = noun;
	intcode[2] = verb;

	int position = 0;
	while (position < intcode.size())
	{
		const int op_code = intcode[position];

		if (op_code == 99)
			break;

		const int a = intcode[position + 1];
		const int b = intcode[position + 2];
		const int c = intcode[position + 3];

		if (op_code == 1)
		{
			intcode[c] = intcode[a] + intcode[b];
		}
		else if (op_code == 2)
		{
			intcode[c] = intcode[a] * intcode[b];
		}
		else
		{
			// invalid op
		}

		position += 4;
	}

	return intcode[0];
}

int main(int argc, const char* argv[])
{
	std::vector<int> intcode;

	int value;
	while (scanf_s("%d,", &value) == 1)
		intcode.push_back(value);

	for (int noun = 0; noun < 100; noun++)
	{
		for (int verb = 0; verb < 100; verb++)
		{
			const int output = execute(intcode, noun, verb);
			if (output == 19690720)
			{
				printf("%02d%02d", noun, verb);
				return 0;
			}
		}
	}

	return 1;
}