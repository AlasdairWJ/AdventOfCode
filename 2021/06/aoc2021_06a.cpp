#include <iostream>
#include <numeric> // std::accumulate

constexpr int days = 80;
constexpr int spawn_timer = 6;
constexpr int reset_timer = 8;
constexpr int size = reset_timer + 1;

int main(int argc, const char* agv[])
{
	__int64 count[size] = {};

	int value;
	while (std::cin >> value, std::cin.ignore(1))
		count[value]++;

	for (int day = 0; day < days; day++)
		count[(day + spawn_timer + 1) % size] += count[day % size];

	std::cout << std::accumulate(std::begin(count), std::end(count), 0ll);

	return 0;
}