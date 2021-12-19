#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::min_element
#include <numeric> // std::accumulate
#include <functional> // std::multiplies

using uint64 = unsigned long long;

unsigned decode_xdigit(const char c)
{
	return isxdigit(c) ? (isdigit(c) ? c - '0' : (c - 'A') + 10) : 0u;
}

struct BitBuffer
{
	BitBuffer(const std::string& input) : input(input), buffer(0u), bit_count(0u), offset(0), bits_read(0u) {}

	unsigned read(const unsigned count)
	{
		while (bit_count < count)
		{
			(buffer <<= 4) |= decode_xdigit(input[offset++]);
			bit_count += 4;
		}

		bits_read += count;
		bit_count -= count;
		return (buffer & ((1 << count) - 1) << bit_count) >> bit_count;
	}

	unsigned get_bits_read() const
	{
		return bits_read;
	}

private:
	unsigned bits_read;
	unsigned bit_count, buffer;
	unsigned offset;
	std::string input;
};

uint64 process_packet(BitBuffer& bitBuffer)
{
	const unsigned version = bitBuffer.read(3);
	const unsigned type_id = bitBuffer.read(3);

	uint64 value = 0;

	if (type_id == 4)
	{
		unsigned more;

		do
		{
			more = bitBuffer.read(1);
			(value <<= 4) |= bitBuffer.read(4);
		}
		while (more == 1);
	}
	else
	{
		const unsigned length_type_id = bitBuffer.read(1);

		std::vector<uint64> operands;

		if (length_type_id == 0)
		{
			const unsigned total_length = bitBuffer.read(15);

			const unsigned start_bits_read = bitBuffer.get_bits_read();

			do operands.push_back(process_packet(bitBuffer));
			while ((bitBuffer.get_bits_read() - start_bits_read) < total_length);
		}
		else
		{
			const unsigned number_of_subpackets = bitBuffer.read(11);

			for (unsigned i = 0; i < number_of_subpackets; i++)
				operands.push_back(process_packet(bitBuffer));
		}

		switch (type_id)
		{
		case 0:
			value = std::accumulate(operands.begin(), operands.end(), 0llu);
			break;
		case 1:
			value = std::accumulate(operands.begin(), operands.end(), 1llu,  std::multiplies<uint64>());
			break;
		case 2:
			value = *std::min_element(operands.begin(), operands.end());
			break;
		case 3:
			value = *std::max_element(operands.begin(), operands.end());
			break;
		case 5:
			value = operands[0] > operands[1];
			break;
		case 6:
			value = operands[0] < operands[1];
			break;
		case 7:
			value = operands[0] == operands[1];
			break;
		}
	}

	return value;
}

int main(int argc, const char* argv[])
{
	bool first = true;
	std::string input;
	while (std::getline(std::cin, input) && !input.empty())
	{
		if (!first) std::cout << std::endl;
		else first = false;

		BitBuffer bitBuffer(input);
		std::cout << process_packet(bitBuffer);
	}

	return 0;
}