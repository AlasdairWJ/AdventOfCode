#include <vector>

enum Op : int
{
	INVALID = 0,
	ADD,
	MUL,
	INPUT,
	OUTPUT,
	JUMP_IF_TRUE,
	JUMP_IF_FALSE,
	LESS_THAN,
	EQUALS,	
	QUIT = 99
};

using Program = std::vector<int>;

template <typename InputIt, typename OutputIt>
bool execute(Program program, InputIt input_it, InputIt input_end, OutputIt output_it)
{
	for (size_t counter = 0; counter < program.size(); )
	{
		const int full_op = program[counter++];
		const Op op = static_cast<Op>(full_op % 100);

		const int modes[] = { (full_op / 100) % 10,
							  (full_op / 1000) % 10,
							  (full_op / 10000) % 10 };

		if (op == QUIT)
			break;

		switch (op)
		{
		case ADD:
		{
			const int a = modes[0] == 0 ? program[counter++] : counter++,
					  b = modes[1] == 0 ? program[counter++] : counter++,
					  c = program[counter++];

			program[c] = program[a] + program[b];
			break;
		}
		case MUL:
		{
			const int a = modes[0] == 0 ? program[counter++] : counter++,
					  b = modes[1] == 0 ? program[counter++] : counter++,
					  c = program[counter++];

			program[c] = program[a] * program[b];
			break;
		}
		case INPUT:
		{
			const int a = program[counter++];

			if (input_it == input_end)
				return false;

			program[a] = *(input_it++);

			break;
		}
		case OUTPUT:
		{
			const int a = modes[0] == 0 ? program[counter++] : counter++;

			*(output_it++) = program[a];
			break;
		}
		case JUMP_IF_TRUE:
		{
			const int a = modes[0] == 0 ? program[counter++] : counter++,
					  b = modes[1] == 0 ? program[counter++] : counter++;

			if (program[a] != 0)
				counter = program[b];
			
			break;
		}
		case JUMP_IF_FALSE:
		{
			const int a = modes[0] == 0 ? program[counter++] : counter++,
					  b = modes[1] == 0 ? program[counter++] : counter++;

			if (program[a] == 0)
				counter = program[b];
			
			break;
		}
		case LESS_THAN:
		{
			const int a = modes[0] == 0 ? program[counter++] : counter++,
					  b = modes[1] == 0 ? program[counter++] : counter++,
					  c = program[counter++];

			program[c] = program[a] < program[b];
			break;
		}
		case EQUALS:
		{
			const int a = modes[0] == 0 ? program[counter++] : counter++;
				  int b = modes[1] == 0 ? program[counter++] : counter++;
				  int c = program[counter++];

			program[c] = program[a] == program[b];
			break;
		}
		default:
			return false;
		}
	}

	return true;
}