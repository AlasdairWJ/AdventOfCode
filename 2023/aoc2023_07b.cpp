#include <iostream>
#include <string>
#include <charconv> // std::from_chars
#include <ranges> // std::views::enumerate (sorry non-c++23 people)
#include <array>
#include <vector>
#include <algorithm> // std::ranges::max, std::ranges::contains, std::ranges::count

constexpr int joker_score = 1;

int score_card(const char c)
{
	switch (c)
	{
	case 'A': return 14;
	case 'K': return 13;
	case 'Q': return 12;
	case 'T': return 10;
	case 'J': return joker_score;
	default: return int{ c - '0' };
	}
}

struct Score
{
	int type;
	std::array<int, 5> hand;

	auto operator<=>(const Score&) const = default;
};

struct Play
{
	std::array<char, 5> cards;
	int bid;

	Score score;

	void calculate_score()
	{
		int distribution[15]{};
		for (int i = 0; i < 5; i++)
		{
			const int s = score_card(cards[i]);
			score.hand[i] = s;
			distribution[s]++;
		}

		const int jokers = distribution[joker_score];
		distribution[joker_score] = 0;

		int* pMax = std::ranges::max_element(distribution);
		const int highest_combo = *pMax + jokers;
		*pMax = 0;

		switch (highest_combo)
		{
		case 5:
			score.type = 7;
			break;
		case 4:
			score.type = 6;
			break;
		case 3:
			score.type = std::ranges::contains(distribution, 2) ? 5 : 4;
			break;
		case 2:
			score.type = std::ranges::contains(distribution, 2) ? 3 : 2;
			break;
		case 1:
			score.type = 1;
			break;
		default:
			break;
		}
	}
};

int main(int _, const char*[])
{
	std::vector<Play> plays;

	for (std::string line; std::getline(std::cin, line); )
	{
		auto& play = plays.emplace_back();
		for (int i = 0; i < 5; i++)
			play.cards[i] = line[i];

		std::from_chars(&line[6], &line[6] + (line.size() - 6), play.bid);

		play.calculate_score();
	}

	std::ranges::sort(plays, [](auto p1, auto p2) { return p1.score < p2.score; });

	int total_winnings = 0;

	for (const auto [index, play] : plays | std::views::enumerate)
		total_winnings += play.bid * (index + 1);

	std::cout << total_winnings;
}