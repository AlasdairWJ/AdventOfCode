#ifndef __INTCPU_HPP
#define __INTCPU_HPP

#include <vector>
#include <iostream>

enum class Operation : int
{
	Invalid = 0,
	Add,
	Multiply,
	Input,
	Output,
	JumpIfTrue,
	JumpIfFalse,
	LessThan,
	Equals,

	Quit = 99
};

using Program = std::vector<int>;

struct IntCPU
{
	IntCPU() = default;
	IntCPU(const Program& program) : _memory{ program } {}

	template <typename R = std::initializer_list<int>>
	void input(R && r) { _input.assign(std::rbegin(r), std::rend(r)); }

	const auto& output() const { return _output; }

	bool run();

	int result() const { return _memory[0]; }

private:
	std::vector<int> _input;
	std::vector<int> _output;
	std::vector<int> _memory;
};

bool IntCPU::run()
{
	auto input = _input;

	for (std::size_t pc = 0; pc < _memory.size(); )
	{
		const int instruction = _memory[pc++];
		const Operation operation = static_cast<Operation>(instruction % 100);

		if (operation == Operation::Quit)
			break;

		const int modes[] {
			(instruction / 100) % 10,
			(instruction / 1000) % 10,
			(instruction / 10000) % 10
		};

		switch (operation)
		{
		case Operation::Add:
		{
			const int a = (modes[0] == 0) ? _memory[pc++] : pc++;
			const int b = (modes[1] == 0) ? _memory[pc++] : pc++;
			const int c = _memory[pc++];

			_memory[c] = _memory[a] + _memory[b];
			break;
		}
		case Operation::Multiply:
		{
			const int a = (modes[0] == 0) ? _memory[pc++] : pc++;
			const int b = (modes[1] == 0) ? _memory[pc++] : pc++;
			const int c = _memory[pc++];

			_memory[c] = _memory[a] * _memory[b];
			break;
		}
		case Operation::Input:
		{
			const int a = _memory[pc++];

			if (input.empty())
				return false;

			_memory[a] = input.back();
			input.pop_back();
			break;
		}
		case Operation::Output:
		{
			const int a = (modes[0] == 0) ? _memory[pc++] : pc++;

			_output.push_back(_memory[a]);
			break;
		}
		case Operation::JumpIfTrue:
		{
			const int a = (modes[0] == 0) ? _memory[pc++] : pc++;
			const int b = (modes[1] == 0) ? _memory[pc++] : pc++;

			if (_memory[a] != 0)
				pc = _memory[b];
			
			break;
		}
		case Operation::JumpIfFalse:
		{
			const int a = (modes[0] == 0) ? _memory[pc++] : pc++;
			const int b = (modes[1] == 0) ? _memory[pc++] : pc++;

			if (_memory[a] == 0)
				pc = _memory[b];
			
			break;
		}
		case Operation::LessThan:
		{
			const int a = (modes[0] == 0) ? _memory[pc++] : pc++;
			const int b = (modes[1] == 0) ? _memory[pc++] : pc++;
			const int c = _memory[pc++];

			_memory[c] = (_memory[a] < _memory[b]);
			break;
		}
		case Operation::Equals:
		{
			const int a = (modes[0] == 0) ? _memory[pc++] : pc++;
			const int b = (modes[1] == 0) ? _memory[pc++] : pc++;
			const int c = _memory[pc++];

			_memory[c] = (_memory[a] == _memory[b]);
			break;
		}
		default:
			return false;
		}
	}

	return true;
}

auto loadProgramFrom(std::istream& is)
{
	Program program;

	do
	{
		int value;
		is >> value;
		program.push_back(value);
	}
	while (std::cin.get() == ',');

	return program;
}

#endif // __INTCPU_HPP