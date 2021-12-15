#pragma once

class Board
{
public:
	bool read()
	{
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				std::cin >> data[i][j];
		return std::cin.good();
	}

	bool mark(const int value)
	{
		bool any_marked = false;

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (data[i][j] == value)
				{
					data[i][j] = -1;
					any_marked = true;
				}

		return any_marked;
	}

	bool bingo() const
	{
		for (int i = 0; i < 5; i++)
		{
			bool is_match = true;

			for (int j=0; j < 5; j++)
				if (data[i][j] >= 0)
				{
					is_match = false;
					break;
				}

			if (is_match)
				return true;
		}

		for (int j = 0; j < 5; j++)
		{
			bool is_match = true;

			for (int i = 0; i < 5; i++)
				if (data[i][j] >= 0)
				{
					is_match = false;
					break;
				}

			if (is_match)
				return true;
		}

		return false;
	}

	int sum() const
	{
		int total = 0;

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (data[i][j] >= 0)
					total += data[i][j];

		return total; 
	}

private:
	int data[5][5];
};