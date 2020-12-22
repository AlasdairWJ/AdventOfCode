#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
#include <array>

using decks_t = std::array<std::queue<int>, 2>;

int play(decks_t& decks)
{
	while (!decks[0].empty() && !decks[1].empty())
	{
		int top_cards[2];
		for (int p=0; p<2; p++)
		{
			top_cards[p] = decks[p].front();
			decks[p].pop();
		}

		const int winning_p = top_cards[0] > top_cards[1] ? 0 : 1;

		decks[winning_p].push(top_cards[winning_p]);
		decks[winning_p].push(top_cards[!winning_p]);
	}

	return decks[0].empty() ? 1 : 0;
}

int main(int argc, const char* argv[])
{
	decks_t decks;

	std::string line;
	for (int p = 0; p < 2; p++)
	{
		std::getline(std::cin, line); // Player #

		while (std::getline(std::cin, line) && !line.empty())
			decks[p].push(std::stoi(line));
	}

	const int winning_p = play(decks);

	int score = 0;
	int position = decks[winning_p].size();

	while (!decks[winning_p].empty())
	{
		const int card = decks[winning_p].front();
		score += card * position;
		decks[winning_p].pop();
		position--;
	}

	printf("%d", score);

	return 0;
}

/*
p1 | p2
---+---
 6 |  1
25 | 18
 8 | 31
24 | 39
30 | 16
46 | 10
42 | 35
32 | 29
27 | 26
48 | 44
 5 | 21
 2 |  7
14 | 45
28 |  4
37 | 20
17 | 38
 9 | 15
22 | 11
40 | 34
33 | 36
 3 | 49
50 | 13
47 | 23
19 | 43
41 | 12
*/