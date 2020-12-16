#pragma once

#include <vector>
#include <map>
#include <queue>

// ---------------------------------------------------------

enum execution_result_t { INVALID_OPERATOR, REQUIRES_INPUT, HALTED };

struct intcode_machine_t
{
	intcode_machine_t() = default;

	intcode_machine_t(const std::vector<__int64>& code)
	{
		load_program(code);
	}

	void load_program(const std::vector<__int64>& code)
	{
		m_position = 0;
		m_relative_base = 0;
		m_code = code;
		m_extended_memory.clear();
	}

	execution_result_t execute(std::queue<__int64>& input, std::queue<__int64>& output);

private:
	__int64& fetch(__int64 position);
	__int64& fetch_parameter(int mode, __int64 position);

	__int64 m_position, m_relative_base;
	std::vector<__int64> m_code;
	std::map<__int64, __int64> m_extended_memory;
};

// ---------------------------------------------------------

__int64& intcode_machine_t::fetch(const __int64 position)
{
	return position < m_code.size() ? m_code[position] : m_extended_memory[position];
}

__int64& intcode_machine_t::fetch_parameter(const int mode, const __int64 position)
{
	switch (mode)
	{
	default:
	case 0: return fetch(fetch(position));
	case 1: return fetch(position);
	case 2: return fetch(m_relative_base + fetch(position));
	}
}

execution_result_t intcode_machine_t::execute(std::queue<__int64>& input, std::queue<__int64>& output)
{
	while (true)
	{
		__int64& full_op_code = fetch(m_position);

		const int op_code = full_op_code % 100;

		int modes[3];
		for (int i = 0, m = full_op_code / 100; i < 3; i++, m /= 10)
			modes[i] = m % 10;

		if (op_code == 99)
			return HALTED;

		switch (op_code)
		{
		case 1:
		{
			const __int64 a = fetch_parameter(modes[0], m_position + 1);
			const __int64 b = fetch_parameter(modes[1], m_position + 2);
			__int64& c = fetch_parameter(modes[2], m_position + 3);

			c = a + b;
			m_position += 4;
			break;
		}
		case 2:
		{
			const __int64 a = fetch_parameter(modes[0], m_position + 1);
			const __int64 b = fetch_parameter(modes[1], m_position + 2);
			__int64& c = fetch_parameter(modes[2], m_position + 3);

			c = a * b;
			m_position += 4;
			break;
		}
		case 3:
		{
			__int64& a = fetch_parameter(modes[0], m_position + 1);

			if (input.empty())
				return REQUIRES_INPUT;

			a = input.front();
			input.pop();

			m_position += 2;
			break;
		}
		case 4:
		{
			const __int64 a = fetch_parameter(modes[0], m_position + 1);

			output.push(a);
			m_position += 2;	
			break;
		}
		case 5:
		{
			const __int64 a = fetch_parameter(modes[0], m_position + 1);
			const __int64 b = fetch_parameter(modes[1], m_position + 2);

			if (a != 0) m_position = b;
			else m_position += 3;
			
			break;
		}
		case 6:
		{
			const __int64 a = fetch_parameter(modes[0], m_position + 1);
			const __int64 b = fetch_parameter(modes[1], m_position + 2);

			if (a == 0) m_position = b;
			else m_position += 3;
			
			break;
		}
		case 7:
		{
			const __int64 a = fetch_parameter(modes[0], m_position + 1);
			const __int64 b = fetch_parameter(modes[1], m_position + 2);
			__int64& c = fetch_parameter(modes[2], m_position + 3);

			c = a < b ? 1 : 0;
			m_position += 4;
			break;
		}
		case 8:
		{
			const __int64 a = fetch_parameter(modes[0], m_position + 1);
			const __int64 b = fetch_parameter(modes[1], m_position + 2);
			__int64& c = fetch_parameter(modes[2], m_position + 3);

			c = a == b ? 1 : 0;
			m_position += 4;
			break;
		}
		case 9:
		{
			const __int64 a = fetch_parameter(modes[0], m_position + 1);

			m_relative_base += a;
			m_position += 2;
			break;
		}
		default:
			return INVALID_OPERATOR;
		}
	}
}