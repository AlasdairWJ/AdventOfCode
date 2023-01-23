#include <iostream> // std::cout
#include <string> // std::string, std::getline

int main(int argc, const char* argv[])
{
	int count = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		int lower1, upper1, lower2, upper2;
		sscanf_s(line.c_str(), "%d-%d,%d-%d", &lower1, &upper1, &lower2, &upper2);
		count += (lower1 <= upper2 && lower2 <= upper1) ||
				 (lower2 <= upper1 && lower1 <= upper2);
	}

	std::cout << count;

	return 0;
}