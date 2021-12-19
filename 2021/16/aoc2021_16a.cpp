#include <iostream>
#include <string>
#include <vector>

unsigned decode_xdigit(const char c)
{
	return isxdigit(c) ? (isdigit(c) ? c - '0' : (c - 'A') + 10) : 0;
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

void process_packet(BitBuffer& bitBuffer, unsigned& version_sum)
{
	const unsigned version = bitBuffer.read(3);
	const unsigned type_id = bitBuffer.read(3);

	version_sum += version;

	if (type_id == 4)
	{
		unsigned more;

		do
		{
			more = bitBuffer.read(1);
			bitBuffer.read(4);
		}
		while (more == 1);
	}
	else
	{
		const unsigned length_type_id = bitBuffer.read(1);

		if (length_type_id == 0)
		{
			const unsigned total_length = bitBuffer.read(15);

			const unsigned start_bits_read = bitBuffer.get_bits_read();

			do process_packet(bitBuffer, version_sum);
			while ((bitBuffer.get_bits_read() - start_bits_read) < total_length);

		}
		else
		{
			const unsigned number_of_subpackets = bitBuffer.read(11);

			for (unsigned i = 0; i < number_of_subpackets; i++)
				process_packet(bitBuffer, version_sum);
		}
	}
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

		unsigned version_sum = 0;
		process_packet(bitBuffer, version_sum);

		std::cout << version_sum;
	}

	return 0;
}