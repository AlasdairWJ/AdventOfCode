#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <regex>
#include <utility>
#include <format>

#include "../../util/charconv.hpp" // util::from_chars
#include "../../util/tokenize.hpp" // util::tokenize

const std::regex instruction_re{ "\\d+|L|R" };

struct Instruction
{
	enum class Type { Move, Left, Right } type;
	int value;
};

std::vector<Instruction> parse_instructions(const std::string& line)
{
	std::vector<Instruction> instructions;

	for (const auto& sub_match : util::tokenize(line, instruction_re))
	{
		if (const char c = *sub_match.first; std::isdigit(c))
		{
			auto& token = instructions.emplace_back(Instruction::Type::Move, 0);
			util::from_chars(sub_match, token.value);
		}
		else if (c == 'L')
		{
			instructions.emplace_back(Instruction::Type::Left, 0);
		}
		else if (c == 'R')
		{
			instructions.emplace_back(Instruction::Type::Right, 0);
		}
	}

	return instructions;
}

int wrap(int value, const std::pair<int, int>& range)
{
	const auto& [lower, upper] = range;
	const auto size = upper - lower;
	while (value < lower) value += size;
	while (value >= upper) value -= size;
	return value;
}

int main(int _, const char*[])
{
	std::vector<std::string> lines;
	std::vector<std::pair<int, int>> horizontal_ranges;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
	{
		horizontal_ranges.emplace_back(
			static_cast<int>(line.find_first_not_of(' ')),
			static_cast<int>(line.size())
		);
		lines.push_back(line);
	}

	const int line_count = static_cast<int>(lines.size());

	const auto string_size = [](const auto& s) { return s.size(); };
	const auto line_lengths = lines | std::views::transform(string_size);
	const int max_width = static_cast<int>(*std::ranges::max_element(line_lengths));

	std::vector<std::pair<int, int>> vertical_ranges(max_width, std::make_pair(0, line_count));

	for (int y = 1; y < line_count - 1; y++)
	{
		const auto& line = lines[y];
		const auto& prev_line = lines[y - 1];
		const auto& next_line = lines[y + 1];

		for (int x = 0; x < line.size(); x++)
		{
			if (line[x] != ' ')
			{
				if (x >= prev_line.size() || prev_line[x] == ' ')
					vertical_ranges[x].first = y;

				if (x >= next_line.size() || next_line[x] == ' ')
					vertical_ranges[x].second = y + 1;
			}
		}
	}

	std::string instructions_line;
	std::getline(std::cin, instructions_line);

	std::vector<Instruction> instructions = parse_instructions(instructions_line);

	int x = static_cast<int>(lines[0].find_first_not_of(' ')), y = 0;
	int dx = 1, dy = 0;

	for (const auto& [type, move] : instructions)
	{
		switch (type)
		{
		case Instruction::Type::Left:
			std::swap(dx = -dx, dy);
			break;
		case Instruction::Type::Right:
			std::swap(dx, dy = -dy);
			break;
		case Instruction::Type::Move:
			for (int i = 0; i < move; i++)
			{
				const int next_x = wrap(x + dx, horizontal_ranges[y]);
				const int next_y = wrap(y + dy, vertical_ranges[x]);
				if (lines[next_y][next_x] == '#')
					break;
				x = next_x, y = next_y;
			}
			break;
		}
	}

	const int facing =
		(dy > 0 ? 1 : 0) + 
		(dx < 0 ? 2 : 0) + 
		(dy < 0 ? 3 : 0);

	std::cout << 1000 * (y + 1) + 4 * (x + 1) + facing;

}

// 37412 too low