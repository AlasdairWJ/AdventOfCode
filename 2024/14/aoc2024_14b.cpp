#include <iostream>
#include <string>
#include <regex>
#include <numeric>
#include <algorithm>

#include "../../util/point.hpp"
#include "../util/charconv.hpp"

using util::Point;

constexpr int Width = 101;
constexpr int Height = 103;

struct Particle
{
	Point pos;
	Point vel;

	void move()
	{
		pos += vel;

		pos.x %= Width;
		
		if (pos.x < 0)
			pos.x += Width;

		pos.y %= Height;
		
		if (pos.y < 0)
			pos.y += Height;
	}
};

bool row_contains_line(const std::string& line)
{
	return line.find("OOOOOOOO") != std::string::npos;
}

bool contains_xmas_tree(const auto& particles)
{
	std::vector lines(Height, std::string(Width, ' '));

	for (const auto& p : particles)
		lines[p.pos.y][p.pos.x] = 'O';

	return std::ranges::any_of(lines, row_contains_line);
}

int main(const int argc, const char* argv[])
{
	const std::regex velocity_pattern{ "^p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)$" };

	std::vector<Particle> particles;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::smatch match;
		std::regex_match(line, match, velocity_pattern);

		Particle& particle = particles.emplace_back();

		util::from_chars(match[1], particle.pos.x);
		util::from_chars(match[2], particle.pos.y);

		util::from_chars(match[3], particle.vel.x);
		util::from_chars(match[4], particle.vel.y);
	}

	const int limit = Width * Height;

	for (int seconds = 1; seconds <= limit; seconds++)
	{
		for (auto& p : particles)
			p.move();

		if (contains_xmas_tree(particles))
		{
			std::cout << seconds;
			break;
		}
	}
}
