#include <iostream>
#include <string>
#include <sstream>

int main(int argc, const char* argv[])
{
	int count = 0;

	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		std::stringstream ss(line);
		std::string s;

		for (int i = 0; i < 10; i++)
			ss >> s;

		ss >> s; // ignore |

		for (int i = 0; i < 4; i++)
		{
			ss >> s;

			switch (s.size())
			{
			case 2:
			case 4:
			case 3:
			case 7:
				count++;
				break;
			default:
				break;
			}
		}
	}

	std::cout << count;

	return 0;
}