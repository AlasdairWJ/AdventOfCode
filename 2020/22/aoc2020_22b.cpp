#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
#include <array>
#include <set>

using decks_t = std::array<std::queue<int>, 2>;

int play(decks_t& decks)
{
	std::set<decks_t> previous_decks;

	while (!decks[0].empty() && !decks[1].empty())
	{
		if (!previous_decks.emplace(decks).second)
			return 0;

		int top_cards[2];
		for (int p=0; p<2; p++)
		{
			top_cards[p] = decks[p].front();
			decks[p].pop();
		}
		const bool can_recurse = (top_cards[0] <= decks[0].size()) && (top_cards[1] <= decks[1].size());
		
		int winning_p;
		if (can_recurse)
		{
			decks_t new_decks, copy = decks; // have to copy as queues have no iterators (could use deque but eh)

			for (int p=0; p<2; p++)
				for (int i=0; i<top_cards[p]; i++)
				{
					new_decks[p].push(copy[p].front());
					copy[p].pop();
				}

			winning_p = play(new_decks);
		}
		else
		{
			winning_p = top_cards[0] > top_cards[1] ? 0 : 1;
		}

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