#pragma once

#include <vector>
#include <queue>

// ---------------------------------------------------------

enum execution_result_t { INVALID_OPERATOR, REQUIRES_INPUT, HALTED, END_OF_CODE };

struct intcode_machine_t
{
	intcode_machine_t() = default;

	intcode_machine_t(const std::vector<int>& code)
	{
		load_program(code);
	}

	void load_program(const std::vector<int>& code)
	{
		m_position = 0;
		m_code = code;
	}

	execution_result_t execute(std::queue<int> input, std::queue<int>& output);

private:
	int m_position;
	std::vector<int> m_code;
};

// ---------------------------------------------------------

execution_result_t intcode_machine_t::execute(std::queue<int> input, std::queue<int>& output)
{
	while (m_position < m_code.size())
	{
		const int op_code = m_code[m_position] % 100;

		int modes[3];
		for (int i = 0, m = m_code[m_position] / 100; i < 3; i++, m /= 10)
			modes[i] = m % 10;

		if (op_code == 99)
			return HALTED;

		switch (op_code)
		{
		case 1:
		{
			const int a = modes[0] == 0 ? m_code[m_position + 1] : m_position + 1;
			const int b = modes[1] == 0 ? m_code[m_position + 2] : m_position + 2;
			const int c = m_code[m_position + 3];

			m_code[c] = m_code[a] + m_code[b];
			m_position += 4;
			break;
		}
		case 2:
		{
			const int a = modes[0] == 0 ? m_code[m_position + 1] : m_position + 1;
			const int b = modes[1] == 0 ? m_code[m_position + 2] : m_position + 2;
			const int c = m_code[m_position + 3];

			m_code[c] = m_code[a] * m_code[b];
			m_position += 4;
			break;
		}
		case 3:
		{
			const int a = m_code[m_position + 1];

			if (input.empty())
				return REQUIRES_INPUT;

			m_code[a] = input.front();
			input.pop();

			m_position += 2;
			break;
		}
		case 4:
		{
			const int a = modes[0] == 0 ? m_code[m_position + 1] : m_position + 1;

			output.push(m_code[a]);
			m_position += 2;	
			break;
		}
		case 5:
		{
			const int a = modes[0] == 0 ? m_code[m_position + 1] : m_position + 1;
			const int b = modes[1] == 0 ? m_code[m_position + 2] : m_position + 2;

			if (m_code[a] != 0) m_position = m_code[b];
			else m_position += 3;
			
			break;
		}
		case 6:
		{
			const int a = modes[0] == 0 ? m_code[m_position + 1] : m_position + 1;
			const int b = modes[1] == 0 ? m_code[m_position + 2] : m_position + 2;

			if (m_code[a] == 0) m_position = m_code[b];
			else m_position += 3;
			
			break;
		}
		case 7:
		{
			const int a = modes[0] == 0 ? m_code[m_position + 1] : m_position + 1;
			const int b = modes[1] == 0 ? m_code[m_position + 2] : m_position + 2;
			const int c = m_code[m_position + 3];

			m_code[c] = m_code[a] < m_code[b] ? 1 : 0;
			m_position += 4;
			break;
		}
		case 8:
		{
			const int a = modes[0] == 0 ? m_code[m_position + 1] : m_position + 1;
			const int b = modes[1] == 0 ? m_code[m_position + 2] : m_position + 2;
			const int c = m_code[m_position + 3];

			m_code[c] = m_code[a] == m_code[b] ? 1 : 0;
			m_position += 4;
			break;
		}
		default:
			return INVALID_OPERATOR;
		}
	}

	return END_OF_CODE;
}