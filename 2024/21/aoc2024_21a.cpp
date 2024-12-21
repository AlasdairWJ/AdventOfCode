#include <iostream>
#include <string>
#include <string_view>
#include <map>

#include "../util/charconv.hpp"
#include "../../util/Point.hpp"

using util::Point;

constexpr char NumericPad[][3]{
	{ '7', '8', '9' },
	{ '4', '5', '6' },
	{ '1', '2', '3' },
	{ ' ', '0', 'A' },
};

constexpr char DirectionalPad[][3]{
	{ ' ', '^', 'A' },
	{ '<', 'v', '>' },
};

enum class Priority
{
	Horizontal,
	Vertical
};

constexpr Priority Priorities[] { Priority::Horizontal, Priority::Vertical };

std::map<std::pair<char, char>, Priority> priorities{

	// Generated from separate code
	// Any pair not explicitly listed is equal in length regardless of priority
	{{ '1', '0' }, Priority::Horizontal },
	{{ '1', 'A' }, Priority::Horizontal },
	{{ '2', '4' }, Priority::Horizontal },
	{{ '2', '7' }, Priority::Vertical },
	{{ '2', 'A' }, Priority::Vertical },
	{{ '3', '0' }, Priority::Vertical },
	{{ '3', '4' }, Priority::Horizontal },
	{{ '3', '5' }, Priority::Horizontal },
	{{ '3', '7' }, Priority::Horizontal },
	{{ '3', '8' }, Priority::Horizontal },
	{{ '4', '0' }, Priority::Horizontal },
	{{ '4', '2' }, Priority::Horizontal },
	{{ '4', '3' }, Priority::Horizontal },
	{{ '4', 'A' }, Priority::Vertical },
	{{ '5', '1' }, Priority::Vertical },
	{{ '5', '3' }, Priority::Vertical },
	{{ '5', '7' }, Priority::Vertical },
	{{ '5', 'A' }, Priority::Vertical },
	{{ '6', '0' }, Priority::Horizontal },
	{{ '6', '1' }, Priority::Vertical },
	{{ '6', '2' }, Priority::Horizontal },
	{{ '6', '7' }, Priority::Horizontal },
	{{ '6', '8' }, Priority::Horizontal },
	{{ '7', '0' }, Priority::Horizontal },
	{{ '7', '2' }, Priority::Horizontal },
	{{ '7', '3' }, Priority::Horizontal },
	{{ '7', '5' }, Priority::Vertical },
	{{ '7', '6' }, Priority::Vertical },
	{{ '7', 'A' }, Priority::Vertical },
	{{ '8', '1' }, Priority::Vertical },
	{{ '8', '3' }, Priority::Vertical },
	{{ '8', '4' }, Priority::Vertical },
	{{ '8', '6' }, Priority::Vertical },
	{{ '8', 'A' }, Priority::Horizontal },
	{{ '9', '0' }, Priority::Vertical },
	{{ '9', '1' }, Priority::Horizontal },
	{{ '9', '2' }, Priority::Vertical },
	{{ '9', '4' }, Priority::Horizontal },
	{{ '9', '5' }, Priority::Horizontal },
	{{ 'A', '2' }, Priority::Horizontal },
	{{ 'A', '5' }, Priority::Horizontal },
	{{ 'A', '8' }, Priority::Horizontal },

	// trivial combinations to avoid empty locations
	{{ 'A', '1' }, Priority::Vertical },
	{{ 'A', '4' }, Priority::Vertical },
	{{ 'A', '7' }, Priority::Vertical },
	{{ '1', 'A' }, Priority::Horizontal },
	{{ '4', 'A' }, Priority::Horizontal },
	{{ '7', 'A' }, Priority::Horizontal },

	{{ '0', '1' }, Priority::Vertical },
	{{ '0', '4' }, Priority::Vertical },
	{{ '0', '7' }, Priority::Vertical },
	{{ '1', '0' }, Priority::Horizontal },
	{{ '4', '0' }, Priority::Horizontal },
	{{ '7', '0' }, Priority::Horizontal }
};


struct Pad
{
	Pad(const auto& grid)
	{
		Point p{};
		for (const auto& row : grid)
		{
			p.x = 0;

			for (const auto& c : row)
			{
				const auto it = _buttons.emplace(c, p);

				p.x++;
			}

			p.y++;
		}

		_blank = _buttons.find(' ')->second;
	}

	std::string enter(char current, const std::string_view keys)
	{
		std::string sequence;
		Point position = _buttons.find(current)->second;

		for (const char key : keys)
		{
			press(current, key, position, sequence);
			current = key;
		}

		return sequence;
	}

	std::string enter(const std::string_view keys)
	{
		return enter('A', keys);
	}

private:
	void move_x(const util::Point& destination, util::Point& position, std::string& sequence)
	{
		while (position.x < destination.x)
		{
			sequence.push_back('>');
			position.x++;
		}

		while (position.x > destination.x)
		{
			sequence.push_back('<');
			position.x--;
		}
	}

	void move_y(const util::Point& destination, util::Point& position, std::string& sequence)
	{
		while (position.y < destination.y)
		{
			sequence.push_back('v');
			position.y++;
		}

		while (position.y > destination.y)
		{
			sequence.push_back('^');
			position.y--;
		}
	}

	void press(const char current, const char key, util::Point& position, std::string& sequence)
	{
		const auto destination = _buttons.find(key)->second;

		const auto it = priorities.find(std::make_pair(current, key));
		const Priority priority = it != priorities.end() ? it->second : Priority::Horizontal;

		if (priority == Priority::Horizontal)
		{
			move_x(destination, position, sequence);
			move_y(destination, position, sequence);
		}
		else
		{
			move_y(destination, position, sequence);
			move_x(destination, position, sequence);
		}

		sequence.push_back('A');
	}

	Point _blank;
	std::map<char, Point> _buttons;	
};

int main(int _, const char*[])
{
	Pad numericPad(NumericPad);
	Pad directionalPad(DirectionalPad);

	int total = 0;

	for (std::string seq; std::getline(std::cin, seq) && !seq.empty(); )
	{
		const auto seq1 = numericPad.enter(seq);
		const auto seq2 = directionalPad.enter(seq1);
		const auto seq3 = directionalPad.enter(seq2);

		total += util::from_chars(seq.substr(0, 3)) * seq3.size();
	}
	
	std::cout << total;

}