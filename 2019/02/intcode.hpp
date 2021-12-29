#include <vector>

enum Op : int
{
	INVALID = 0,
	ADD,
	MUL,
	QUIT = 99
};

using Program = std::vector<int>;

int execute(Program program)
{
	for (auto counter = program.begin(); counter != program.end(); )
	{
		const Op op = static_cast<Op>(*(counter++));

		if (op == QUIT)
			break;

		const int a = *(counter++),
				  b = *(counter++),
				  c = *(counter++);

		switch (op)
		{
		case ADD:
			program[c] = program[a] + program[b];
			break;
		case MUL:
			program[c] = program[a] * program[b];
			break;
		default:
			break;
		}
	}

	return program.front();
}